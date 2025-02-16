# Calcul de l'ensemble de Mandelbrot en python
import numpy as np
from dataclasses import dataclass
from PIL import Image
from math import log
from time import time
import matplotlib.cm
from mpi4py import MPI

@dataclass
class MandelbrotSet:
    max_iterations: int
    escape_radius:  float = 2.0

    def __contains__(self, c: complex) -> bool:
        return self.stability(c) == 1

    def convergence(self, c: complex, smooth=False, clamp=True) -> float:
        value = self.count_iterations(c, smooth)/self.max_iterations
        return max(0.0, min(value, 1.0)) if clamp else value

    def count_iterations(self, c: complex,  smooth=False) -> int | float:
        z:    complex
        iter: int

        # On vérifie dans un premier temps si le complexe
        # n'appartient pas à une zone de convergence connue :
        #   1. Appartenance aux disques  C0{(0,0),1/4} et C1{(-1,0),1/4}
        if c.real*c.real+c.imag*c.imag < 0.0625:
            return self.max_iterations
        if (c.real+1)*(c.real+1)+c.imag*c.imag < 0.0625:
            return self.max_iterations
        #  2.  Appartenance à la cardioïde {(1/4,0),1/2(1-cos(theta))}
        if (c.real > -0.75) and (c.real < 0.5):
            ct = c.real-0.25 + 1.j * c.imag
            ctnrm2 = abs(ct)
            if ctnrm2 < 0.5*(1-ct.real/max(ctnrm2, 1.E-14)):
                return self.max_iterations
        # Sinon on itère
        z = 0
        for iter in range(self.max_iterations):
            z = z*z + c
            if abs(z) > self.escape_radius:
                if smooth:
                    return iter + 1 - log(log(abs(z)))/log(2)
                return iter
        return self.max_iterations


# On peut changer les paramètres des deux prochaines lignes
mandelbrot_set = MandelbrotSet(max_iterations=50, escape_radius=10)
width, height = 1024, 1024

scaleX = 3./width
scaleY = 2.25/height

# Résultats totaux
convergence = np.empty((width, height), dtype=np.double)

########## Principe ##########
# Processus 0 : Gère la comm et calcule aussi
# Processus >0 : calcule

# Récupération des données de MPI
globCom = MPI.COMM_WORLD.Dup()
nbp     = globCom.size
rank    = globCom.rank
name    = MPI.Get_processor_name()

########## Processus 0 ##########
# Il doit :
# - Choisir combien de colonnes fait chaque processus
# - Envoyer à chaque process sa colonne de début et de fin
# - Faire son calcul
# - Réceptionner toutes les données des autres processus
# - Les concaténer
# - afficher le résultat
if(rank == 0):
    # Choisir le nombre de colonnes par process
    nb_col_per_process = width//nbp

    deb = time()

    # Envoie des colonnes de début et de fin à chaque process
    for i in range(1, nbp):
        interval_to_send = np.array([i*nb_col_per_process, (i+1)*nb_col_per_process-1], dtype='int32')
        globCom.Send(interval_to_send, dest=i, tag=0)
    
    # Calcul des dernières colonnes
    result = np.empty((nb_col_per_process, height), dtype = np.double)
    for y in range(height):
        for x in range(nb_col_per_process):
            c = complex(-2. + scaleX*x, -1.125 + scaleY * y)
            result[x, y] = mandelbrot_set.convergence(c, smooth=True)

########## Processus >0 ##########
# Il doit :
# - Récupérer les colonnes qu'il doit faire
# - Faire son calcul
# - Envoyer son résultat
else:
    # Récup des colonnes
    interval_to_treat = np.empty(2, dtype='int32')
    globCom.Recv(interval_to_treat, source=0, tag=MPI.ANY_TAG)
    interval_width = interval_to_treat[1]-interval_to_treat[0]+1

    # Déf du résultat
    result = np.empty((interval_width, height), dtype = np.double)
    # Calcul des colonnes
    for y in range(height):
        for i in range(interval_width):
            x = interval_to_treat[0] + i
            c = complex(-2. + scaleX*x, -1.125 + scaleY * y)
            result[i, y] = mandelbrot_set.convergence(c, smooth=True)

########## Gather des données ##########
globCom.Gather(result, convergence, 0)

if(rank == 0):
    fin = time()
    print(f"Temps du calcul de l'ensemble de Mandelbrot : {fin-deb}")
    # Constitution de l'image résultante :
    deb = time()
    image = Image.fromarray(np.uint8(matplotlib.cm.plasma(convergence.T)*255))
    fin = time()
    print(f"Temps de constitution de l'image : {fin-deb}")
    image.save("result.png")
