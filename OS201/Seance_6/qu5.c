#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/seccomp.h>
#include <sys/prctl.h>
#include <sys/syscall.h>

int main()
{
    // Création des deux pipes
    int pipePereVersFils[2];
    int pipeFilsVersPere[2];
    if(pipe(pipeFilsVersPere) != 0 && pipe(pipePereVersFils != 0)){
        return -1;
    }

    // Création des processus
    int idProcessus = fork();

    if(idProcessus > 0){
        /* Processus père */
        // Fermeture des pipe 
        close(pipeFilsVersPere[1]);// Le père ferme l'écriture dans pipeFilsVersPere car il lit dans ce pipe
        close(pipePereVersFils[0]);// Le père ferme la lecture dans pipePereVersFils car il écrit dans ce pipe

    }else if(idProcessus == 0){
        /* Processus fils */ 
        // Fermeture des pipe
        close(pipePereVersFils[1]);// Le fils ferme l'écriture dans pipePereVersFils car il lit dans ce pipe
        close(pipeFilsVersPere[0]);// Le père ferme la lecture dans pipeFilsVersPere car il écrit dans ce pipe
        // Bloquage des droits des commandes du fils
        prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);
    }else{
        printf("Fork has failed\n");
        return -1;
    }



    #define MAX_SIZE 1000
    char buffer[MAX_SIZE];
    char out_buffer[MAX_SIZE];
    char *ptr = &buffer[0];

    int a, b;
    int nbr_bits_ecrits;

    // On lit l'entrée standard
    read(STDIN_FILENO, buffer, MAX_SIZE);
    // On regarde la commande voulue
    switch (*ptr++)
    {
        // Question 1
        case '+':
            a = strtol(ptr, &ptr, 10);  // Lecture du premier arg
            ptr++;                      // On saute la virgule
            b = strtol(ptr, &ptr, 10);  // Lecture du deuxième arg
            nbr_bits_ecrits = sprintf(out_buffer, "Result is %d\n", a + b); // Formatage du résultat
            write(STDOUT_FILENO, out_buffer, nbr_bits_ecrits);              // Ecriture du résultat dans la sortie standard
            ptr = buffer;
            break;
        case '-':
            a = strtol(ptr, &ptr, 10); // Lecture du premier arg
            ptr++;                     // On saute la virgule
            b = strtol(ptr, &ptr, 10); // Lecture du deuxième arg
            nbr_bits_ecrits = sprintf(out_buffer, "Result is %d\n", a - b);
            write(STDOUT_FILENO, out_buffer, nbr_bits_ecrits);
            ptr = buffer;
            break;
        case 'e':
            system(ptr);
            break;
        default:
            break;
    }

    syscall(SYS_exit, 0);
    return 0;
}