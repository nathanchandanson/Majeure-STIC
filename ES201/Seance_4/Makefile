################# COMPILATION #################

# sslittle-na-sstrix-gcc : cannot install it locally -> need to connect to nom@salle.ensta.fr
SS_CC=/usr/ensta/pack/simplescalar-3v0d/bin/sslittle-na-sstrix-gcc
CC=${SS_CC}

all: dijkstra_small.ss dijkstra_large.ss

dijkstra_small.ss:
	$(CC) -O -o dijkstra_small.ss dijkstra_small.c

dijkstra_large.ss:
	$(CC) -O -o dijkstra_large.ss dijkstra_large.c

################# SIMULATION #################

# sim-profile
SIM_PROFILE=../simplesim-3.0/sim-profile

profiling_dijkstra_small:
	$(SIM_PROFILE) -iclass -iprof -redir:sim dijkstra_small.out dijkstra_small.ss input.dat

CACHE_CORTEX_A7   = "-cache:il1 config -cache:dl1 config" # Pour le cache L2 : mettre -cache:il2 ou -cache:dl2 : tester les 2 avec dl2 en premier
OPTIONS_CORTEX_A7 = "-fetch:ifqsize 4 -decode:width 2 -issue:width 4 -issue:inorder false -commit:width 2 -ruu:size 2 -lsq:size 8 -res:ialu 1 -res:imult 1 -res:fpalu 1 -res:fpmult 1"
# CACHE_CORTEX_A15  = 
# OPTIONS_CORTEX_A15= 

# sim-outorder  program.ss

.PHONY:all clean

clean:
	rm dijkstra_small.ss
	rm dijkstra_large.ss