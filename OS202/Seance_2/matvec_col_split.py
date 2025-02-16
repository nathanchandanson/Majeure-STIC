# Produit matrice-vecteur v = A.u
import numpy as np
from mpi4py import MPI

################ Initialisation ################
# Récupération des données de MPI
globCom = MPI.COMM_WORLD.Dup()
nbp     = globCom.size
rank    = globCom.rank
name    = MPI.Get_processor_name()

################ Parallélisation ################
# Processus 0
# - Sépare les données
# - Envoie les données séparées
# - Fait son propre calcul
# - Récup toutes les données
# - Donne le résultat final
if(rank == 0):
    # Dimension du problème (peut-être changé)
    dim = 120
    # Initialisation de la matrice
    A = np.array([[(i+j) % dim+1. for i in range(dim)] for j in range(dim)])
    # print(f"A = {A}")
    # Initialisation du vecteur u
    u = np.array([i+1. for i in range(dim)])
    # print(f"u = {u}")

    # Size of the blocks
    size_block = dim//nbp
    size_info = np.array([dim, size_block], dtype = 'int32')
    # print(size_info)

    # Dispatching all the data
    for i in range(1, nbp):
        globCom.Send(size_info, dest = i, tag = 0)
        A_block = np.ascontiguousarray(A[:,i*size_block:(i+1)*size_block], dtype = 'float')
        # print(A_block.shape)
        globCom.Send(A_block, dest = i, tag = 1)
        u_block = u[i*size_block:(i+1)*size_block]
        # print(u_block.shape)
        globCom.Send(u_block, dest = i, tag = 2)
    
    # Calcul propre
    A_block = A[:,0:size_block]
    u_block = u[0:size_block]
    result = A_block.dot(u_block)

    # Récupération des autres données
    for i in range(1,nbp):
        temp = np.empty(dim, dtype = 'float')
        globCom.Recv(temp, source = i, tag = 3)
        result = result + temp

    # Affichage résultat
    print(f"v = {result}")

# Processus >0
# - Récupère ses données
# - Fait son calcul
# - Envoie ses résultats
else: 
    # Info sur la taille : [dim, size_block]
    size_info = np.empty(2, dtype='int32')
    globCom.Recv(size_info, source = 0, tag = 0)

    # Init des blocks
    A_block = np.empty((size_info[0], size_info[1]), dtype='float')
    u_block = np.empty(size_info[1], dtype='float')

    # Réception des blocs
    globCom.Recv(A_block, source = 0, tag = 1)
    globCom.Recv(u_block, source = 0, tag = 2)

    # Calcul 
    res = A_block.dot(u_block)

    # Renvoyer le résultat
    globCom.Send(res, dest = 0, tag = 3)

