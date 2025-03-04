#!/bin/bash

SIM_PROFILE=../../simplesim-3.0/sim-profile

PRG_SS1="conv2D.ss"
PRG_SS2="conv2D_int.ss"
PRG_SS3="conv2D_unroll.ss"

REDIR_OUT_SIMU1="-redir:sim conv2D.out"
REDIR_OUT_SIMU2="-redir:sim conv2D_int.out"
REDIR_OUT_SIMU3="-redir:sim conv2D_unroll.out"

OPTIONS="-iclass -iprof"

$SIM_PROFILE $OPTIONS $REDIR_OUT_SIMU1 $PRG_SS1
$SIM_PROFILE $OPTIONS $REDIR_OUT_SIMU2 $PRG_SS2
$SIM_PROFILE $OPTIONS $REDIR_OUT_SIMU3 $PRG_SS3