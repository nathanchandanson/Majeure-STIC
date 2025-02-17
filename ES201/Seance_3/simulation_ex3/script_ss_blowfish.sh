#!/bin/bash

SIM_OUT_ORDER=/usr/ensta/pack/simplescalar-3v0d/simplesim-3.0/sim-outorder

mkdir -p simu

for SIZE in small medium large
do
	PRG_SS="bf.ss e input_${SIZE}.asc output_${SIZE}.enc 1234567890abcdeffedcba0987654321"
	for UF in 1 2 4 8
	do
	REDIR_OUT_SIMU="-redir:sim simu/sim_bf_enc_o3_${SIZE}_M${UF}"
	OPTIONS="-fetch:ifqsize 4 -decode:width 4 -issue:width 4 -issue:inorder false -commit:width 4 -ruu:size 16 -lsq:size 8 -res:memport 2"
	UNIT_FONCT="-res:ialu ${UF} -res:imult ${UF} -res:fpalu ${UF} -res:fpmult ${UF}"
	echo "o3 $SIZE $UF"
	$SIM_OUT_ORDER $OPTIONS $UNIT_FONCT $REDIR_OUT_SIMU $PRG_SS
	done
done

for SIZE in small medium large
do
	PRG_SS="bf.ss e input_${SIZE}.asc output_${SIZE}.enc 1234567890abcdeffedcba0987654321"
	for UF in 1 2 4 8
	do
	REDIR_OUT_SIMU="-redir:sim simu/sim_bf_enc_order_${SIZE}_M${UF}"
	OPTIONS="-fetch:ifqsize 4 -decode:width 4 -issue:width 4 -issue:inorder true -commit:width 4 -ruu:size 16 -lsq:size 8 -res:memport 2"
	UNIT_FONCT="-res:ialu ${UF} -res:imult ${UF} -res:fpalu ${UF} -res:fpmult ${UF}"
	echo "order $SIZE $UF"
	$SIM_OUT_ORDER $OPTIONS $UNIT_FONCT $REDIR_OUT_SIMU $PRG_SS
	done
done




