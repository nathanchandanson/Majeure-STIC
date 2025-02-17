import numpy as np
from mpi4py import MPI

####### Récup infos sur le process #######
globCom = MPI.COMM_WORLD.Dup()
nbp     = globCom.size
rank    = globCom.rank
name    = MPI.Get_processor_name()

####### Données 
N = int(1E2)            # Nombre de données par processus
max_value = int(1E6)    # Données aléatoires comprises entre [-max_value, max_value]

####### Processus 0 #######
# Il doit :
# - Créer son propre tableau
# - Calculer son propre tableau [min,max,mediane]
# - Attendre les tableaux [min,max,mediane] des autres tableaux (gather)
# - Créer la répartition des tableaux
# - Envoyer cette répartition à tt le monde (all broadcast)
# - Envoyer toutes les données aux autres process correspondant à leur bucket
# - Réceptionner toutes les valeurs de son bucket
# - Trier son bucket

####### Processus >0 #######
# Il doit :
# - Créer son propre tableau
# - Trouver le tableau [min,max,mediane] de ses données
# - L'envoyer à P0
# - Attendre la répartition des données envoyée par P0
# - Envoyer toutes les données aux autres process correspondant à leur bucket
# - Réceptionner toutes les valeurs de son bucket
# - Trier le bucket

####### Création des values et du minMaxTable #######
# Création de son tableau propre
values = np.random.randint(-max_value, max_value, size=N)
# Calculer son propre tableau [min,max,mediane]
minMaxTable = np.array([min(values), max(values), np.median(values)]) ######################## Modifier pour donner tous les quantiles

####### Création du buffer #######
if(rank == 0):
    concatenated_minMaxTable = np.empty(nbp*3, dtype='float')
else:
    concatenated_minMaxTable = None

####### Gather des données #######
globCom.Gather(minMaxTable, concatenated_minMaxTable)

####### Calcul des quantiles et min/max #######
if(rank == 0):   
    # Créer la répartition des tableaux
    quantiles = np.quantile(concatenated_minMaxTable, [i/nbp for i in range(1,nbp)]).tolist()
    data_to_send = [min(concatenated_minMaxTable)] + quantiles + [max(concatenated_minMaxTable)]
    data_to_send = np.array(data_to_send * nbp)
else:
    data_to_send = None

# Réception des tables avec min/quantiles/max
glob_minMaxTable = np.empty(nbp+1)

# Envoyer cette répartition à tt le monde
globCom.Scatter(data_to_send, glob_minMaxTable, root=0)

####### Envoie des données aux autres bucket + Réception pour notre bucket #######
for val in values:
    # On vérifie si la valeur est pas déjà dans le bon bucket
    if(not (val >= glob_minMaxTable[rank] and val < glob_minMaxTable[rank+1])):
        for i in range(len(glob_minMaxTable)-1):
            if(val >= glob_minMaxTable[i] and val < glob_minMaxTable[i+1]):
                # Envoyer au process correspondant



####### Tri de notre bucket #######