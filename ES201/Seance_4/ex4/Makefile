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

sim-outorder_dijkstra_small_A7:
	./script_dijkstra_small_A7.sh

.PHONY:all clean
