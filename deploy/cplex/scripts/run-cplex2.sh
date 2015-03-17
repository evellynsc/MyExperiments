#!/bin/bash

#   This file is used to run experiments of vehicles coverage with access points.
#   The experiments will be run with 
#   5, 10, 15, 20, 25, 30, 35, 40, 45 and 50% coverage of intersections, i.e.,
#   you will deploy this percentagens at the dataset. Moreover, this also 
#   consider that the times tau needed to receive the information are 
#   10, 20, 30, 40, 50 and 60s.
#   To run this file you must give in this order
#       1. the file name
#       2. the number of intersections (lines)
#       3. the number of vehicles (columns)


tau=(20 40 60)
ap=(0 0 0)
file="$1"
lines="$2"
columns="$3"
index=0

#   construct vector of access points according percentage of access points
#   and lines (intersections) number
for k in $(seq 10 20 50)
do
#    aux=$(echo "scale=1; $lines*$k/100" |bc)
#    aux=`echo $aux | awk '{print int($1+0.5)}'`
    aux=$(printf '%i %i' $k $lines | awk '{ pc=$1*$2/100; i=int(pc); print (pc-i<0.5)?i:i+1 }')
    ap[$index]=$aux
    index=$(($index+1))
done

#   construct command with run configurations and execute it
for i in ${ap[@]}
do
    for j in ${tau[@]} 
    do
        timefile="$file-k$i-tau$j-time"
        resultfile="$file-k$i-tau$j-result"
        command="(time ./evlex2 $i $j $lines $columns $file) > $resultfile 2> $timefile;"
        eval $command
#	    echo $command
    done
done
