#!/bin/bash

############# modelo 1 preprocessado 2

./run-cplex-pre2.sh logs/preprocess2/modelo2/E3-T-60s-4CP-tau-20-p2 46 9876 20;

./run-cplex-pre2.sh logs/preprocess2/modelo2/E2-T-60s-4CP-tau-20-p2 38 11632 20;

./run-cplex-pre2.sh logs/preprocess2/modelo2/E1-T-60s-4CP-tau-40-p2 43 13578 40;
./run-cplex-pre2.sh logs/preprocess2/modelo2/E1-T-60s-4CP-tau-20-p2 43 13578 20;

./run-cplex-pre2.sh logs/preprocess2/modelo2/E0-T-60s-4CP-tau-20-p2 83 61896 20;
./run-cplex-pre2.sh logs/preprocess2/modelo2/E0-T-60s-4CP-tau-40-p2 83 61896 40;
./run-cplex-pre2.sh logs/preprocess2/modelo2/E0-T-60s-4CP-tau-60-p2 83 61896 60;
