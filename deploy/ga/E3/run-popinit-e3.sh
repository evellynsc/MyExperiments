#!/bin/bash

file=("E3-T-60s-4CP")

#./ga 10 40 5 ~/deploy/ga_parameters/e3-k5-t40.ga ~/deploy/dataset/$file logs/e3-k5-tau40.out >> e3-k5-t40.terminal &
#./ga 10 60 5 ~/deploy/ga_parameters/e3-k5-t60.ga ~/deploy/dataset/$file logs/e3-k5-t60.out >> e3-k5-t60.terminal &
#./ga 10 20 14 ~/deploy/ga_parameters/e3-k14-t20.ga ~/deploy/dataset/$file logs/e3-k14-t20.out >> e3-k14-t20.terminal &
#./ga 10 40 14 ~/deploy/ga_parameters/e3-k14-t40.ga ~/deploy/dataset/$file logs/e3-k14-t40.out >> e3-k14-t40.terminal &


./ga 10 40 23 ~/deploy/ga_parameters/e3-k23-t40.ga ~/deploy/dataset/$file logs/e3-k23-t40.out; >> e3-k23-t40.terminal &
./ga 10 60 23 ~/deploy/ga_parameters/e3-k23-t60.ga ~/deploy/dataset/$file logs/e3-k23-t60.out; >> e3-k23-t60.terminal &
