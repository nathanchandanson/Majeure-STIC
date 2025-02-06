
# TD1

`pandoc -s --toc README.md --css=./github-pandoc.css -o README.html`

## lscpu

*lscpu donne des infos utiles sur le processeur : nb core, taille de cache :*

```
Architecture:             x86_64
  CPU op-mode(s):         32-bit, 64-bit
  Address sizes:          48 bits physical, 48 bits virtual
  Byte Order:             Little Endian
CPU(s):                   16
  On-line CPU(s) list:    0-15
Vendor ID:                AuthenticAMD
  Model name:             AMD Ryzen 7 5800HS with Radeon Graphics
    CPU family:           25
    Model:                80
    Thread(s) per core:   2
    Core(s) per socket:   8
    Socket(s):            1
    Stepping:             0
    BogoMIPS:             6387.82
```


## Produit matrice-matrice

### Effet de la taille de la matrice

  n            | MFlops
---------------|--------
      800      | 525.424
      1023     | 358.797
1024 (origine) | 80.307
      1025     | 361.581

Pour 1024, moins efficace : Histoire de stockage modulo dans le cache : si 1024 -> on tape dans la meme cellule de caache et donc on utilise pas tout le cache mais tout le temps la même.


### Permutation des boucles

*Expliquer comment est compilé le code (ligne de make ou de gcc) : on aura besoin de savoir l'optim, les paramètres, etc. Par exemple :*

`make TestProduct.exe && ./TestProduct.exe 1024`


  ordre           | time    | MFlops  | MFlops(n=2048)
------------------|---------|---------|----------------
i,j,k (origine)   | 12.0961 | 177.536 |
j,i,k             | 11.2669 | 190.601 |
i,k,j             | 27.4123 | 78.3402 |
k,i,j             | 30.5559 | 70.2805 |
j,k,i             | 1.64956 | 1301.85 |
k,j,i             | 0.44676 | 4806.76 |


*Discuter les résultats.*
Quand i en dernier : plus efficace 
On peut expliquer cela par le fait que i représente la ligne de la matrice C et A, or, les matrices sont représentées comme des vecteurs, qui sont stockés en ligne de manière contigue. 
De fait, Lorsque l'on fait i le plus imbriqué, on est sûr que lorsque l'on va charger les données de A, ce sont bien des données d'une même ligne, ce qui évitera les caches miss.
Pour j en deuxième imbriqué, c'est la même chose mais avec le chargement des données de B



### OMP sur la meilleure boucle

`make TestProduct.exe && OMP_NUM_THREADS=8 ./TestProduct.exe 1024`

On rajoute un pragma devant la première boucle pour signifier qu'on veut paralléliser le traitement de la boucle for.

  OMP_NUM         | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
------------------|---------|----------------|----------------|---------------
1                 | 4880.71 |    2462.57     |    4727.38     |    2210.98
2                 | 
3                 |
4                 |
5                 |
6                 |
7                 |
8                 |

*Tracer les courbes de speedup (pour chaque valeur de n), discuter les résultats.*



### Produit par blocs

`make TestProduct.exe && ./TestProduct.exe 1024`

  szBlock         | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
------------------|---------|----------------|----------------|---------------
origine (=max)    |
32                |
64                |
128               |
256               |
512               |
1024              |

*Discuter les résultats.*



### Bloc + OMP


  szBlock      | OMP_NUM | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)|
---------------|---------|---------|----------------|----------------|---------------|
1024           |  1      |         |                |                |               |
1024           |  8      |         |                |                |               |
512            |  1      |         |                |                |               |
512            |  8      |         |                |                |               |

*Discuter les résultats.*


### Comparaison avec BLAS, Eigen et numpy

*Comparer les performances avec un calcul similaire utilisant les bibliothèques d'algèbre linéaire BLAS, Eigen et/ou numpy.*


# Tips

```
	env
	OMP_NUM_THREADS=4 ./produitMatriceMatrice.exe
```

```
    $ for i in $(seq 1 4); do elap=$(OMP_NUM_THREADS=$i ./TestProductOmp.exe|grep "Temps CPU"|cut -d " " -f 7); echo -e "$i\t$elap"; done > timers.out
```
