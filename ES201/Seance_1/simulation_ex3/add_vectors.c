/*
 * add_vecteur.c
 *
 * Effectue l'addition de deux vecteurs à coordonées entières
 * de taille N
 *
 * 22/12/2016
 * Joël Cathébras  [joel.cathebras@gmail.com]
 * CEA List
 * Copyright CEA LIST 2016
 */


 #include <time.h>
 #include <stdlib.h>

 #define N 50

int main(int argc, char **argv)
{
int i;
int v1[N];
int v2[N];
int v3[N];

//addition des vecteurs : v3 = v2 + v1;
for(i=0;i<N;i++){
	v3[i]=v2[i]+v1[i];
}

return 0;
}



















