# But 

On veut paralléliser le jeu de la vie.

Pour cela, on veut séparer la partie calcul et la partie affichage. 
L'affichage est moins rapide que le calcul, de fait :
- La partie calcul fait en permanence les calcul de l'itération suivante
- La partie affichage demande la grille actuelle, l'affiche, puis redemande la nouvelle grille, ...

## Première partie

On prend une approche synchrone : la partie calcul calcule une frame, l'envoie à la partie affichage de manière bloquante, qui la reçoit de manière bloquante, puis l'affiche. De fait, comme on utilise que des communications bloquantes, on est sûr d'afficher toutes les frames, même si on sait que le calcul va attendre à chaque fois car sa tâche est plus rapide que l'affichage.

## Deuxième partie 

On prend une approche asynchrone : la partie calcul ne s'arrête jamais et envoie le plateau quand la partie affichage est prête. Comme l'affichage est plus lent, on sait qu'on ne va pas voir toutes les frames.

## Troisième partie

On prend une approche synchrone, sauf que on split le communicateur, pour avoir un communicateur qui contient les processus de calcul ensemble, qui se partagent le calcul.