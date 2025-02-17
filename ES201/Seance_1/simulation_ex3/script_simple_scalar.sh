#!/bin/bash

SIM_OUTORDER=/usr/ensta/pack/simplescalar-3v0d/simplesim-3.0/sim-outorder

PRG_SS="add_vec.ss"
REDIR_OUT_SIMU="-redir:sim simu.out"
OPTIONS="-issue:inorder true"

$SIM_OUTORDER $OPTIONS $REDIR_OUT_SIMU $PRG_SS


