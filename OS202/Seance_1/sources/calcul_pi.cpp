# include <chrono>
# include <random>
# include <cstdlib>
// # include <sstream>
// # include <string>
// # include <fstream>
# include <iostream>
// # include <iomanip>
#include <vector>
#include <omp.h>
# include <mpi.h>

// Attention , ne marche qu'en C++ 11 ou supérieur :
double approximate_pi( unsigned long nbSamples ) 
{
    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();
    myclock::duration d = beginning.time_since_epoch();
    unsigned seed = d.count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution <double> distribution ( -1.0 ,1.0);
    unsigned long nbDarts = 0;
    // Throw nbSamples darts in the unit square [-1 :1] x [-1 :1]
	// #pragma omp parallel for ///////////////////////////////////////// OpenMP
    for ( unsigned sample = 0 ; sample < nbSamples ; ++ sample ) {
        double x = distribution(generator);
        double y = distribution(generator);
        // Test if the dart is in the unit disk
        if ( x*x+y*y<=1 ) nbDarts ++;
    }
    // Number of nbDarts throwed in the unit disk
    double ratio = double(nbDarts)/double(nbSamples);
    return 4*ratio;
}

int main( int argc, char* argv[] )
{
	/**** Mise en place de MPI ****/
	MPI_Comm commGlob;
    int nbp, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_dup(MPI_COMM_WORLD, &commGlob);    // Copy the global communicator into my own communicator
    MPI_Comm_size(commGlob, &nbp);              // Retrieve the number of processes launched
    MPI_Comm_rank(commGlob, &rank);             // Retrieve my own rank

	/**** Execution des différents processus ****/
	/* Processus 0 */
	/* Il va se charger de faire la comm avec les autres
	 * Pour cela, il va :
	 * - Décider du nombre de points à utiliser puis déterminer le nombre de points par processus
	 * - Envoyer le nombre de point par processus à chaque processus
	 * - Calculer l'approximation avec son nombre de points
	 * - Récupérer toutes les approximations
	 * - Calculer la valeur finale	
	*/
	if(rank == 0)
	{
		// Décider du nombre de points à utiliser puis déterminer le nombre de points par processus
		int N = 1000000;
		int N_perProcess = N / nbp;
		// Envoyer le nombre de point par processus à chaque processus
		MPI_Bcast (&N_perProcess, 1, MPI_INT, 0, commGlob);
	 	// Calculer l'approximation avec son nombre de points
		std::vector<float> results;
	 	// Récupérer toutes les approximations
		float temp;
		MPI_Status status;
		while(results.size() < nbp){
			MPI_Recv(&temp, 1, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, commGlob, &status);
		}
	 	// Calculer la valeur finale : moyenne de toutes les valeurs trouvées (car autant de points dans chaque processus)
		float res = std::accumulate(results.begin(), results.end(), 0);
		res = res/nbp;
	}
	/* Processus >0 */
	/* Il va simplement servir à calcule
	 * Pour cela, il va:
     * - Recevoir le nombre de points qu'il doit calculer
	 * - Calculer son approximation
	 * - Renvoyer son approximation au processus 0 
	*/
	else
	{

	}
	
	double approx_pi = approximate_pi(100000);
	std::cout << approx_pi << std::endl;


	// A la fin du programme, on doit synchroniser une dernière fois tous les processus
	// afin qu'aucun processus ne se termine pendant que d'autres processus continue à
	// tourner. Si on oublie cet instruction, on aura une plantage assuré des processus
	// qui ne seront pas encore terminés.
	MPI_Finalize();
	return EXIT_SUCCESS;
}

