# Calcul pi par une méthode stochastique (convergence très lente !)
import time
import numpy as np
from mpi4py import MPI

# Nombre d'échantillons :
nb_samples = 40_000_000

def calcul_pi(nb_samples):
    beg = time.time()
    # Tirage des points (x,y) tirés dans un carré [-1;1] x [-1; 1]
    x = 2.*np.random.random_sample((nb_samples,))-1.
    y = 2.*np.random.random_sample((nb_samples,))-1.
    # Création masque pour les points dans le cercle unité
    filtre = np.array(x*x + y*y < 1.)
    # Compte le nombre de points dans le cercle unité
    sum = np.add.reduce(filtre, 0)

    approx_pi = 4.*sum/nb_samples
    end = time.time()

    # print(f"Temps pour calculer pi : {end - beg} secondes")
    # print(f"Pi vaut environ {approx_pi}")

    return approx_pi


############### Parallélisation MPI ###############
# Récupération des données de MPI
globCom = MPI.COMM_WORLD.Dup()
nbp     = globCom.size
rank    = globCom.rank
name    = MPI.Get_processor_name()

# Process 0
if(rank == 0):
    # Nbr de points par process
    N_perProcess = nb_samples // nbp
    # Envoyer ce nombre de points à tt le monde 
    for i in range(1, nbp):
        globCom.Send(N_perProcess, dest = i, tag = 0)
    
    # Résultats
    # Propre résultat 
    results = [calcul_pi(N_perProcess)]
    # Résultats des autres
    while(len(results) < nbp):
        temp = 0.0
        globCom.Recv(temp, source = MPI.ANY_SOURCE, tag = MPI.ANY_TAG)
    
    # Calcul de Pi
    res = sum(results)
    res = res / nbp

    print("Résultats : Pi = ", res)
# Autres process
else:
    n_points = 0
    globCom.Recv(n_points, source = 0, tag = MPI.ANY_TAG)

    globCom.Send(calcul_pi(n_points), dest = 0, tag = 0)
