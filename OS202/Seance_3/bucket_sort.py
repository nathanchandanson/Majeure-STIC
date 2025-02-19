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
# - Calculer son propre tableau [min,max,quantiles]
# - Attendre les tableaux [min,max,quantiles] des autres tableaux (gather)
# - Créer la répartition des tableaux
# - Envoyer cette répartition à tt le monde (all broadcast)
# - Envoyer toutes les données aux autres process correspondant à leur bucket
# - Réceptionner toutes les valeurs de son bucket
# - Trier son bucket

####### Processus >0 #######
# Il doit :
# - Créer son propre tableau
# - Trouver le tableau [min,max,quantiles] de ses données
# - L'envoyer à P0
# - Attendre la répartition des données envoyée par P0
# - Envoyer toutes les données aux autres process correspondant à leur bucket
# - Réceptionner toutes les valeurs de son bucket
# - Trier le bucket

####### Création des values et du minMaxTable #######
# Création de son tableau propre
values = np.random.randint(-max_value, max_value, size=N)
# Calculer son propre tableau [min,max,mediane]
quantiles = np.quantile(values, [i/nbp for i in range(1,nbp)]).tolist()
minMaxTable = np.array([min(values), max(values)] + quantiles) ######################## Modifier pour donner tous les quantiles

####### Création du buffer #######
if(rank == 0):
    concatenated_minMaxTable = np.empty(nbp*(nbp+1), dtype='float')
else:
    concatenated_minMaxTable = None

####### Gather des données #######
globCom.Gather(minMaxTable, concatenated_minMaxTable)

####### Calcul des quantiles et min/max #######
if(rank == 0):   
    # Créer la répartition des tableaux
    glob_quantiles = np.quantile(concatenated_minMaxTable, [i/nbp for i in range(1,nbp)]).tolist()
    glob_minMaxTable = np.array([min(concatenated_minMaxTable)] + glob_quantiles + [max(concatenated_minMaxTable)])
else:
    glob_minMaxTable = np.empty(nbp+1, dtype='float')

# Envoyer cette répartition à tt le monde
globCom.Bcast(glob_minMaxTable, root=0)

####### Envoie des données aux autres bucket + Réception pour notre bucket #######
# Données propres
values_to_sort = np.array([])
# Buffer d'envoi
buffer_size = (MPI.BSEND_OVERHEAD + np.dtype('float').itemsize) * N     # On fait un buffer de taille N, pour être sûr qu'on peut envoyer toutes les données
buffer = np.empty(buffer_size, dtype='float')

# Envoi des données
for val in values:
    for i in range(len(glob_minMaxTable)-1):
        if(val >= glob_minMaxTable[i] and val < glob_minMaxTable[i+1]):
            if(i == rank):
                # Cette valeur est dans le bucket propre 
                values_to_sort = np.append(values_to_sort, val)
            else:
                # Cette valeur doit être dans un autre bucket : on l'envoie
                globCom.Ibsend(np.array([val], dtype='float'), dest=i, tag=0)

# Réception des données
status = MPI.Status()
while globCom.Iprobe(source=MPI.ANY_SOURCE, tag=MPI.ANY_TAG, status=status):
    temp = np.empty(1, dtype='float')
    globCom.Recv(temp, source=MPI.ANY_SOURCE, tag=MPI.ANY_TAG)
    values_to_sort = np.append(values_to_sort, temp)
                


####### Tri de notre bucket #######
values_sorted = np.sort(values_to_sort)
print("Processus n°", rank, " : Valeurs Min/Max : ",values_sorted[0],",",values_sorted[-1])