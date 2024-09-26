#include <stdio.h>

#define ALLOC_LISTE

/* Question 2 */
#ifdef ALLOC_TRIVIALE
// On met le tas dans les variables globales : choix arbitraire -> on pourrait le mettre autre part
typedef struct tas_{
    char donnee[16000];
    int nb_allocated;
}tas;

tas monTas;

void* memalloc(int size)
{
    // On retient jusqu'à où c'est déjà alloué 
    int old = monTas.nb_allocated;

    // On teste si ça rentre dans le tas
    if(old + size > 16000){
        printf("Heap is full\n");
        return NULL;
    }

    // On update le nombre d'octets alloués
    monTas.nb_allocated += size;

    // On retourne l'adresse voulue
    return &monTas.donnee[old];
}
#endif

/* Question 3+ */
#ifdef ALLOC_LISTE
// Définition du tas
char* tas[16000];

// Définition de la free_list
struct free_list_node{
    unsigned int size;
    struct free_list_node* next;
};
// Note : les free_list_node seront stockés dans les parties libres du tas car cela évite une allocation dynamique avec malloc

// Première adresse libre
struct free_list_node* head;

void meminit()
{
    // On met la première zone libre au début du tas
    head = (struct free_list_node*)&tas[0];

    // On dit qu'il y a 16000 octets de libre au début
    head->size = 16000;

    // Pour l'instant il n'y a pas de suivant
    head->next = NULL;
}

void* memalloc(int size)
{
    // Recherche du premier endroit où j'ai un espace libre
    struct free_list_node* current_free_list_node = head;
    // struct free_list_node* previous_free_list_node = head;  // Pas nécessaire pour la Méthode 2
    while(current_free_list_node->size < size+sizeof(struct free_list_node)+sizeof(int)){
        // Si on a pas assez de place et qu'on a rien après
        if(current_free_list_node->next == NULL){
            return NULL;
        }

        // On itère
        // previous_free_list_node = current_free_list_node;       // Pas nécessaire pour la Méthode 2
        current_free_list_node = current_free_list_node->next;
    }

    /* Méthode 1 : On utilise la première partie de la zone qui est suffisamment grande */
    // // Maintenant, current_free_list_node contient la première zone mémoire qui a suffisamment d'espace libre
    // // Il faut alors updater la zone libre qu'on a choisi
    // // On met à jour le pointeur next du node d'avant
    // previous_free_list_node->next = current_free_list_node+size;
    
    // // On créé une nouvelle zone 
    // struct free_list_node* new_free_list_node;
    // new_free_list_node->next = current_free_list_node->next;        // Le next est le même que celui de current_node
    // new_free_list_node->size = current_free_list_node->size - size; // Il reste la taille d'avant moins les données qu'on a rajouté

    // // On retourne l'adresse de la première zone capable de contenir les données
    // return current_free_list_node;

    /* Méthode 2 : On utilise la deuxième partie de la zone qui est suffisamment grande : cela permet de ne pas changer le next de current_free_list_node mais seulement sa taille */
    /* En utilisant cette méthode, previous_free_list_node n'est pas utile */
    // On update la taille qu'il reste dans le noeud actuel en tenant compte des métadonnées (taille de données allouées)
    current_free_list_node->size -= (size+sizeof(int));

    // On met la taille des données stockées au début de l'endroit alloué pour les métadonnées
    *(int*)((char*)current_free_list_node + current_free_list_node->size) = size;   // valeur de (int*)(adresse de début des métadonnées)
    
    // On retourne l'adresse de la deuxième partie de la mémoire libre : c'est l'adresse + la taille libre restante après allocation + les métadonnées qui ne doivent pas être accessibles par le programmeur
    return (char*)current_free_list_node + current_free_list_node->size + sizeof(int);    
    // On met (char*) car en arithmétique des pointeurs, le type* + int fait, en terme d'adresse sizeof(type) + int : il est nécessaire de convertir en pointeur sur un octet
}

void memfree(void* ptr)
{
    // On retourne au début des métadonnées
    int* start_ptr = (int*)((char*)ptr - sizeof(int));

    // On note la longueur de la zone à free
    int size = *start_ptr;

    // On recherche la fin de la liste chainée
    struct free_list_node* current_free_list_node = head;
    struct free_list_node* previous_free_list_node = head;
    while(current_free_list_node->next != NULL){
        // Si zone free à côté
        // Si après
        if((char*)current_free_list_node + current_free_list_node->size == ptr){    // On regarde si à la fin du node actuel  on a le pointeur à free
            // On rallonge juste la taille du noeud actuel
            current_free_list_node->size += size;
            return;
        }
        // Si avant
        if((char*)ptr + size == (char*)current_free_list_node){    // On regarde si à la fin de ptr on a le current node
            // Si oui on créé un nouveau node
            struct free_list_node* new_free_list_node;
            // On fait pointer le previous vers celui là
            previous_free_list_node->next = new_free_list_node;
            // On lui donne la taille des deux zones 
            new_free_list_node->size = size + current_free_list_node->size;
            return;
        }
        previous_free_list_node = current_free_list_node;
        current_free_list_node = current_free_list_node->next;
    }

    // Maintenant, current_free_list_node contient le dernier node de la liste chainée

    // On créé le nouveau node
    struct free_list_node* new_free_list_node;
    new_free_list_node->size = size + sizeof(int);
    new_free_list_node->next = NULL;

    // On fait pointer le dernier de la liste vers le nouveau node
    current_free_list_node->next = new_free_list_node;
}

#endif


int main()
{
    #ifdef ALLOC_TRIVIALE
    char* tableau1 = memalloc(150);
    char* tableau2 = memalloc(600);
    printf("%p, %p, %p, %p\n", &monTas.donnee[0], tableau1, tableau2, &monTas.donnee[0]+monTas.nb_allocated);
    printf("%d, %d\n", (int)(tableau2-tableau1), (int)(&monTas.donnee[0]+monTas.nb_allocated - tableau2));
    #endif

    #ifdef ALLOC_LISTE
    meminit();
    int* tableau1 = memalloc(sizeof(int)*5);
    for(int i = 0; i<5; i++){
        tableau1[i] = i;
    }
    for(int i = 0; i<5; i++){
        printf("%d\n", tableau1[i]);
    }
    memfree(tableau1);
    #endif

    return 0;
}

// Question 8 : Cela fait qu'on a pas nécessairement la place pour accueillir une autre chose même si au total, la place est suffisante.