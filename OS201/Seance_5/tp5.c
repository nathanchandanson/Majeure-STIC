#include <signal.h>
#include <stddef.h>
#include <stdio.h>  // getchar
#include <stdlib.h> // exit
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

// Pour compiler ce fichier et le linker avec les fonctions assembleur:
// $ gcc -static -Wall tp3-skeleton.c tp3-skeleton.s -o tp3

// Vous pouvez ensuite lancer le programme compilé:
// $ ./tp3

/* Définition des types */
// Coroutines
typedef void *coroutine_t;

// Statut du thread
enum statut_thread {Pret, Bloque};

// Thread
typedef struct {
    coroutine_t contexte_coroutine;
    enum statut_thread statut;
} thread;

// The size of our stacks
#define STACK_SIZE_FULL 4096

/* Question 2 : On fait aligner les stacks */
__attribute__((aligned(4096))) unsigned char stack1[STACK_SIZE_FULL];
__attribute__((aligned(4096))) unsigned char stack2[STACK_SIZE_FULL];
__attribute__((aligned(4096))) unsigned char stack3[STACK_SIZE_FULL];
__attribute__((aligned(4096))) unsigned char stack4[STACK_SIZE_FULL];

/* Quitte le contexte courant et charge les registres et la pile de CR. */
void enter_coroutine(coroutine_t cr);

/* Sauvegarde le contexte courant dans p_from, et entre dans TO. */
void switch_coroutine(coroutine_t *p_from, coroutine_t to);

/* Initialise la pile et renvoie une coroutine telle que, lorsqu’on entrera
dedans, elle commencera à s’exécuter à l’adresse initial_pc. */
/* Le but est juste de pouvoir utiliser enter_coroutine, donc de faire en sorte que 
quand on appelle enter_coroutine, le dépilement soit tel que l'on a bien pc au 
bon endroit */ 
coroutine_t init_coroutine(void *stack_begin, size_t stack_size,
                           void (*initial_pc)())
{
    char *stack_end = ((char *)stack_begin) + stack_size;
    void **ptr = (void**)stack_end;
    // On initialise le program counter comme le bas de la pile
    ptr--;
    *ptr = initial_pc;
    // On initialise alors les 6 registres au dessus de pc à 0
    for(int i = 0; i<6; i++){
        ptr--;
        *ptr = 0;
    }
    
    return ptr;
}

/* Création des threads */
thread thread1;
thread thread2;
thread thread3;

/* Coroutine d'ordonnancement */
coroutine_t* current_thread;
coroutine_t coroutine_ordonnancement;

void scheduling_fct()
{
    while(1)
    {
        if(thread1.statut == Pret){
            mprotect(stack2, STACK_SIZE_FULL, PROT_READ | PROT_WRITE);
            mprotect(stack3, STACK_SIZE_FULL, PROT_NONE);
            mprotect(stack4, STACK_SIZE_FULL, PROT_NONE);
            current_thread = &(thread1.contexte_coroutine);
            switch_coroutine(&coroutine_ordonnancement, thread1.contexte_coroutine);
        }
        if(thread2.statut == Pret){
            mprotect(stack2, STACK_SIZE_FULL, PROT_NONE);
            mprotect(stack3, STACK_SIZE_FULL, PROT_READ | PROT_WRITE);
            mprotect(stack4, STACK_SIZE_FULL, PROT_NONE);
            current_thread = &(thread2.contexte_coroutine);
            switch_coroutine(&coroutine_ordonnancement, thread2.contexte_coroutine);
        }
        if(thread3.statut == Pret){
            mprotect(stack2, STACK_SIZE_FULL, PROT_NONE);
            mprotect(stack3, STACK_SIZE_FULL, PROT_NONE);
            mprotect(stack4, STACK_SIZE_FULL, PROT_READ | PROT_WRITE);
            current_thread = &(thread3.contexte_coroutine);
            switch_coroutine(&coroutine_ordonnancement, thread3.contexte_coroutine);
        }
    }
}

/* Threads Functions */
void yield()
{
    switch_coroutine(current_thread, coroutine_ordonnancement);
}

thread thread_create(void *stack_begin, size_t stack_size,
                        void (*initial_pc)())
{
    thread created_thread;
    created_thread.contexte_coroutine = init_coroutine(stack_begin, stack_size, initial_pc);
    created_thread.statut = Pret;
    return created_thread;
}

// Valeurs globales
int buffer_value;
int buffer_state;

void producteur()
{
    while(1)
    {
        if(buffer_state == 1){      // Si le buffer est plein : on bloque le producteur pour ne plus l'éxecuter
            thread1.statut = Bloque;
            yield();
        }
        int read_val = getchar();
        if(read_val != -1 && read_val != '\n'){
            // Question 5 : ERREUR
            if(read_val == 'e'){
                stack3[100] = 'a';
            }
            printf("Value read\n");
            buffer_value = read_val;
            buffer_state = 1;
            thread2.statut = Pret;
            thread3.statut = Pret;
        }
        yield();
    }
}

void consommateurA()
{
    int num = 0;
    while(1)
    {
        if(buffer_state == 0){      // Si rien dans le buffer : on bloque le thread pour ne plus l'executer
            thread2.statut = Bloque;
            yield();
        }else{  // On a une donnée à lire
            if(num <= 0){
                num = buffer_value;
                buffer_state = 0;
                thread1.statut = Pret;
            }
            while(num > 0){
                printf("A");
                num--;
                yield();
            }
        }
    }
}

void consommateurB()
{
    int num = 0;
    while(1)
    {
        if(buffer_state == 0){      // Si rien dans le buffer : on bloque le thread pour ne plus l'executer
            thread3.statut = Bloque;
            yield();
        }else{  // On a une donnée à lire
            num = buffer_value;
            buffer_state = 0;
            thread1.statut = Pret;
            while(num > 0){
                printf("B");
                num--;
                yield();
            }
        }
    }
}

// Signal handler
void signal(int __sig, void action(int sig));

/* Code principal */
int main() 
{
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    // Question 1
    if((int)stack1%STACK_SIZE_FULL != 0 && (int)stack2%STACK_SIZE_FULL != 0 && (int)stack3%STACK_SIZE_FULL != 0 && (int)stack4%STACK_SIZE_FULL != 0){
        printf("Les stacks ne sont pas alignées sur 4096 octets\n");
        return -1;
    }

    coroutine_ordonnancement = init_coroutine(stack1, STACK_SIZE_FULL, &scheduling_fct);
    thread1 = thread_create(stack2, STACK_SIZE_FULL, &producteur);
    thread2 = thread_create(stack3, STACK_SIZE_FULL, &consommateurA);
    thread3 = thread_create(stack4, STACK_SIZE_FULL, &consommateurB);

    // Question 3
    mprotect(stack2, STACK_SIZE_FULL, PROT_NONE);
    mprotect(stack3, STACK_SIZE_FULL, PROT_NONE);
    mprotect(stack4, STACK_SIZE_FULL, PROT_NONE);
    
    buffer_state = 0;
    buffer_value = 0;

    enter_coroutine(coroutine_ordonnancement);
    return 0; 
}