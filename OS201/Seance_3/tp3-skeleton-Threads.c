#include <signal.h>
#include <stddef.h>
#include <stdio.h>  // getchar
#include <stdlib.h> // exit
#include <sys/mman.h>

#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>

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

/* Question 1 : Allocation statique de 4 piles */
unsigned char stack1[STACK_SIZE_FULL];
unsigned char stack2[STACK_SIZE_FULL];
unsigned char stack3[STACK_SIZE_FULL];
unsigned char stack4[STACK_SIZE_FULL];

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
thread* current_thread;
coroutine_t coroutine_ordonnancement;

void scheduling_fct()
{
    while(1)
    {
        if(thread1.statut == Pret){
            current_thread = &thread1;
            switch_coroutine(&coroutine_ordonnancement, thread1.contexte_coroutine);
        }
        if(thread2.statut == Pret){
            current_thread = &thread2;
            switch_coroutine(&coroutine_ordonnancement, thread2.contexte_coroutine);
        }
        if(thread3.statut == Pret){
            current_thread = &thread3;
            switch_coroutine(&coroutine_ordonnancement, thread3.contexte_coroutine);
        }
        printf("\n\n");
    }
}

/* Threads Functions */
void yield()
{
    switch_coroutine(&current_thread->contexte_coroutine, coroutine_ordonnancement);
}

thread thread_create(void *stack_begin, size_t stack_size,
                        void (*initial_pc)())
{
    thread created_thread;
    created_thread.contexte_coroutine = init_coroutine(stack_begin, stack_size, initial_pc);
    created_thread.statut = Pret;
    return created_thread;
}

/* Fonctions executées par les threads */
void test_function1()
{
    int compteur = 0;
    int read_val;
    while(1){
        printf("Compteur thread1 : %d\n", compteur);
        compteur++;
        read_val = getchar();
        printf("%d\n", read_val);
        if(read_val != -1){
            compteur = 0;
        }
        yield();
    }
}

void test_function2()
{
    int compteur = 0;
    while(1){
        printf("Compteur thread2 : %d\n", compteur);
        compteur++;
        yield();
    }
}

void test_function3()
{
    int compteur = 0;
    while(1){
        printf("Compteur thread3 : %d\n", compteur);
        compteur++;
        yield();
    }
}

/* Partie 4 */
// Valeurs globales
int buffer_value;
int buffer_state;

void producteur()
{
    if(buffer_state == 1){      // Si le buffer est plein : on bloque le producteur pour ne plus l'éxecuter
        thread1.statut = Bloque;
        yield();
    }
    int read_val = getchar();
    if(read_val != -1){
        buffer_value = read_val;
        buffer_state = 1;
    }
    yield();
}

void consommateurA()
{
    if(buffer_state == 0){      // Si rien dans le buffer : on bloque le thread pour ne plus l'executer
        thread2.statut = Bloque;
    }else{  // On a une donnée à lire

    }
    // Si on écrit sur l'écran : on vide le buffer et on débloque le producteur
}

void consommateurB()
{
    if(buffer_state == 0){
        thread3.statut = Bloque;
    }
}

/* Code principal */
int main() 
{
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    coroutine_ordonnancement = init_coroutine(stack1, STACK_SIZE_FULL, &scheduling_fct);
    thread1 = thread_create(stack2, STACK_SIZE_FULL, &test_function1);
    thread2 = thread_create(stack3, STACK_SIZE_FULL, &test_function2);
    thread3 = thread_create(stack4, STACK_SIZE_FULL, &test_function3);

    enter_coroutine(coroutine_ordonnancement);
    return 0; 
}


// Question 9 : Pb car on veut continuer à executer les threads quand pas d'appui