#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Comm commGlob;
    int nbp, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_dup(MPI_COMM_WORLD, &commGlob);    // Copy the global communicator into my own communicator
    MPI_Comm_size(commGlob, &nbp);              // Retrieve the number of processes launched
    MPI_Comm_rank(commGlob, &rank);             // Retrieve my own rank

    int jeton;
    MPI_Status status;
    if(rank == 0){
        // On envoie le jeton à 0
        jeton = 0;
        MPI_Send(&jeton, 1, MPI_INT, 1, 100, commGlob);
        // On réceptionne le dernier jeton
        MPI_Recv(&jeton, 1, MPI_INT, nbp-1, MPI_ANY_TAG, commGlob, &status);
        // On affiche le dernier jeton
        std::cout << "Jeton reçu : " << jeton << std::endl;
    }else if(rank == nbp-1){
        // On réceptionne le jeton du process nbp-2
        MPI_Recv(&jeton, 1, MPI_INT, rank-1, MPI_ANY_TAG, commGlob, &status);
        // On renvoie le jeton au process 0
        jeton++;
        MPI_Send(&jeton, 1, MPI_INT, 0, 100, commGlob);
    }else{
        // On réceptionne le jeton du process nbp-2
        MPI_Recv(&jeton, 1, MPI_INT, rank-1, MPI_ANY_TAG, commGlob, &status);
        // On renvoie le jeton au process 0
        jeton++;
        MPI_Send(&jeton, 1, MPI_INT, rank+1, 100, commGlob);
    }

    MPI_Finalize();
    return 0;
}