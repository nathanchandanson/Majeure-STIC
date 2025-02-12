import numpy as np
from mpi4py import MPI

####### Récup infos sur le process #######
globCom = MPI.COMM_WORLD.Dup()
nbp     = globCom.size
rank    = globCom.rank
name    = MPI.Get_processor_name()

####### Données 
N = int(1E4)            # Nombre de données par processus
max_value = int(1E6)    # Données aléatoires comprises entre [-max_value, max_value]

####### Processus 0 #######
# Il doit :
# - Créer son propre tableau
# - Calculer son propre tableau [min,max,mediane]
# - Attendre les tableaux [min,max,mediane] des autres tableaux (all gather ?)
# - Créer la répartition des tableaux
# - Envoyer cette répartition à tt le monde (all broadcast)
# - Envoyer toutes les données aux autres process correspondant à leur bucket
# - Réceptionner toutes les valeurs de son bucket
# - Trier son bucket
if(rank == 0):
    # Création de son tableau propre
    values = np.random.randint(-max_value, max_value, size=N)
    # Calculer son propre tableau [min,max,mediane]
    minMaxTable = np.array([min(values), max(values), np.median(values)])
    # Attendre les tableaux [min,max,mediane] des autres tableaux
    while(len(minMaxTable) < 3*nbp):
        temp = np.zeros(3)
        globCom.Recv()
    # Créer la répartition des tableaux

    # Envoyer cette répartition à tt le monde

    # Envoyer toutes les données aux autres process correspondant à leur bucket

    # Réceptionner toutes les valeurs de son bucket

    # Trier son bucket


####### Processus >0 #######
# Il doit :
# - Créer son propre tableau
# - Trouver le tableau [min,max,mediane] de ses données
# - L'envoyer à P0
# - Attendre la répartition des données envoyée par P0
# - Envoyer toutes les données aux autres process correspondant à leur bucket
# - Réceptionner toutes les valeurs de son bucket
# - Trier le bucket
else:
    # Création de son tableau propre
    values = np.random.randint(-max_value, max_value, size=N)
    # Trouver le tableau [min,max,mediane] de ses données
    minMaxTable = [min(values), max(values), np.median(values)]
    # L'envoyer à P0
    # globCom.
    # Attendre la répartition des données envoyée par P0

    # Envoyer toutes les données aux autres process correspondant à leur bucket

    # Réceptionner toutes les valeurs de son bucket

    # Trier le bucket