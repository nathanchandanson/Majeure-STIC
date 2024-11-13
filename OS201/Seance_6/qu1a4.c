#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/seccomp.h>
#include <sys/prctl.h>
#include <sys/syscall.h>

int main()
{
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);

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