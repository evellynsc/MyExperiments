#!/bin/bash

############## modelo 2
./run-cplex2.sh logs/modelo2/E3-T-60s-4CP 46 9876;
./run-cplex2.sh logs/modelo2/E2-T-60s-4CP 38 11632;
./run-cplex2.sh logs/modelo2/E1-T-60s-4CP 43 13578;
./run-cplex2.sh logs/modelo2/E0-T-60s-4CP 83 61896;


############## modelo 2 preprocessado

./run-cplex-pre2.sh logs/preprocess/modelo2/E3-T-60s-4CP-tau-40 46 9666 40;
./run-cplex-pre2.sh logs/preprocess/modelo2/E3-T-60s-4CP-tau-60 46 8015 60;


./run-cplex-pre2.sh logs/preprocess/modelo2/E2-T-60s-4CP-tau-40 38 11310 40;
./run-cplex-pre2.sh logs/preprocess/modelo2/E2-T-60s-4CP-tau-60 38 5528 60;


./run-cplex-pre2.sh logs/preprocess/modelo2/E1-T-60s-4CP-tau-40 43 13168 40;
./run-cplex-pre2.sh logs/preprocess/modelo2/E1-T-60s-4CP-tau-60 43 11568 60;


./run-cplex-pre2.sh logs/preprocess/modelo2/E0-T-60s-4CP-tau-40 83 61078 40;
./run-cplex-pre2.sh logs/preprocess/modelo2/E0-T-60s-4CP-tau-60 83 55316 60;

