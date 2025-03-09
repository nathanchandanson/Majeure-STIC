SIM_OUT_ORDER="../simplesim-3.0/sim-outorder"

for SIZE in 1024 2048 4094 8192 16384
do
	REDIR_OUT_SIMU="-redir:sim simu/sim_dijkstra_small_A7_L1_${SIZE}Octets"
	OPTIONS="-fetch:ifqsize 4 -decode:width 2 -issue:width 4 -issue:inorder false -commit:width 2 -ruu:size 2 -lsq:size 8 -res:ialu 1 -res:imult 1 -res:fpalu 1 -res:fpmult 1"
    # Pour la config des caches : <name>:<nsets>:<bsize>:<assoc>:<repl>
    # sets : parties qui contiennent plusieurs blocs
    # blocs : plus petites unités d'échange entre les mémoires
    # associativité : façon de ranger le bloc dans un set : nb de blocs dans un set
    # Donc : block_size = size/nb_block et size = nb_sets * associativité * block_size = nb_sets * associativité * size/nb_block soit 1 = nb_sets * associativité /nb_block
    # On trouve donc que les cache L1 ont 16 sets et le cache L2 en a 4
    BSIZE=$(echo $(($SIZE/32)))
    CACHE="-cache:il1 il1:16:${BSIZE}:2:l -cache:il2 dl2 -cache:dl1 dl1:16:${BSIZE}:2:r -cache:dl2 ul2:4:16384:8:l"

	$SIM_OUT_ORDER $OPTIONS $CACHE $REDIR_OUT_SIMU dijkstra_small.ss input.dat

done

# OPTIONS="-fetch:ifqsize 4 -decode:width 2 -issue:width 4 -issue:inorder false -commit:width 2 -ruu:size 2 -lsq:size 8 -res:ialu 1 -res:imult 1 -res:fpalu 1 -res:fpmult 1"
# SIZE=1024
# # BSIZE=$(echo $((SIZE/32)))
# BSIZE=$(echo $(($SIZE/32)))
# echo $BSIZE
# CACHE="-cache:il1 il1:16:${BSIZE}:2:l -cache:il2 dl2 -cache:dl1 dl1:16:${BSIZE}:2:r -cache:dl2 ul2:4:16384:8:l"

# $SIM_OUT_ORDER $CACHE $OPTIONS -redir:sim simu/bidule dijkstra_small.ss input.dat