#!/bin/bash

DIR=$1
ID_XP=$2
N_ID=$3

Rscript ga_evolution.R $DIR 0 $ID_XP $N_ID
Rscript ga_evolution.R $DIR 1 $ID_XP $N_ID
Rscript ga_evolution.R $DIR 2 $ID_XP $N_ID
Rscript ga_evolution.R $DIR 3 $ID_XP $N_ID