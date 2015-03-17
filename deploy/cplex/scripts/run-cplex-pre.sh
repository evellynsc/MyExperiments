#!/bin/bash

#   This file is used to run experiments of vehicles coverage with access points.
#   The experiments will be run with 
#   10, 30, 50% coverage of intersections, i.e.,
#   you will deploy this percentagens at the dataset.
#   To run this file you must give in this order
#       1. the file name
#       2. the number of intersections (lines)
#       3. the number of vehicles (columns)
#	4. tau


tau="$4"
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
   # echo $aux
    index=$(($index+1))
done

#   construct command with run configurations and execute it
for i in ${ap[@]}
do
    timefile="$file-k$i-tau$tau-time"
    resultfile="$file-k$i-tau$tau-result"
    command="(time ./evlex1 $i $tau $lines $columns $file) > $resultfile 2> $timefile;"
    eval $command
#	echo $command
done
