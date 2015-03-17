#!/bin/bash

file=("E0-T-60s-4CP")
lines=83
columns=61896
tau=(20 40 60)
ap=(0 0 0)
ga_file=("random-exp2.ga" "random-exp3.ga" "random-exp4.ga" "random-exp5.ga" "random-exp6.ga" "random-exp7.ga" "random-exp8.ga")
index=0
replications=10

#   construct vector of access points according percentage of access points
#   and lines (intersections) number
for k in $(seq 10 20 50)
do
    #aux=$(echo "scale=1; $lines*$k/100" |bc)
    #aux=`echo $aux | awk '{print int($1+0.5)}'`
    aux=$(printf '%i %i' $k $lines | awk '{ pc=$1*$2/100; i=int(pc); print (pc-i<0.5)?i:i+1 }')
    ap[$index]=$aux
    index=$(($index+1))
done

#   construct command with run configurations and execute it
for k in ${ga_file[@]}
do
    for i in ${ap[@]}
    do
        for j in ${tau[@]} 
        do
            outputfile="logs/$file-k$i-tau$j-$k.out"
            inputfile="~/deploy/dataset/$file"
            ga="~/deploy/ga_parameters/$k"
	    terminalout="$outputfile.terminal"
            command="./ga $replications $j $i $ga $inputfile $outputfile; >> $terminalout"
            eval $command
            #echo $command
        done
    done
done

# [number-replications] [required-time=tau] [total-rsu=ap] [param-genetic-file] [input-file] [output-file]
