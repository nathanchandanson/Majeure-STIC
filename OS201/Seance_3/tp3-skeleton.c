#include <signal.h>
#include <stddef.h>
#include <stdio.h>  // getchar
#include <stdlib.h> // exit
#include <sys/mman.h>

#include <fcntl.h>
#include <unistd.h>

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
    coroutine_t* contexte_coroutine;
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

/* Création des coroutines */
coroutine_t coroutine1;
coroutine_t coroutine2;
void test_function1()
{
    int compteur = 0;
    while(1){
        printf("Compteur thread1 : %d\n", compteur);
        compteur++;
        switch_coroutine(&coroutine1, coroutine2);
    }
}

void test_function2()
{
    int compteur = 0;
    while(1){
        printf("Compteur thread2 : %d\n", compteur);
        compteur++;
        switch_coroutine(&coroutine2, coroutine1);
    }
}

/* Code principal */
int main() 
{
    coroutine1 = init_coroutine(stack1, STACK_SIZE_FULL, &test_function1);
    coroutine2 = init_coroutine(stack2, STACK_SIZE_FULL, &test_function2);
    enter_coroutine(coroutine1);
    return 0; 
}
