# TD n°3 - parallélisation du Bucket Sort

*Ce TD peut être réalisé au choix, en C++ ou en Python*

Implémenter l'algorithme "bucket sort" tel que décrit sur les deux dernières planches du cours n°3 :

- le process 0 génère un tableau de nombres arbitraires,
- il les dispatch aux autres process,
- tous les process participent au tri en parallèle,
- le tableau trié est rassemblé sur le process 0.

# Étapes

Il faut : 
- Créer les tableaux random dans chaque processus
- Chaque processus calcule : [min, max, médiane] de ses données qu'il envoie à P0
- P0 concatène puis trie tous ces tableaux de min,max,mediane
- Il en tire le min, max et les quantiles associés au nombre de process
- Il envoie à chaque process les données qu'il doit trier càd

| $P_0$ | $P_1$ | ... | $P_{nbp-1}$ |
| --- | --- | --- | --- |
|\[min,quantile1\[ | \[quantile1, quantile2\[ | ... | \[quantile,max\] |