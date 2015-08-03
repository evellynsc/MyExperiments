#!/bin/bash

# command: ./create-ga-parameters-file.sh [id_pop] [id_mut] [id_cro]
# output: 8 ga parameters files 

id_pop=$1
id_mut=$2
id_cro=$3

ger=100

ind=(100 200)
prob_mut=(0.01 0.1)
prob_cro=(0.7 0.9)

nexp=1

for i in ${ind[@]}
do
	for m in ${prob_mut[@]}
	do
		for c in ${prob_cro[@]}
		do
			ofile="exp${nexp}.ga"
			echo $ger > $ofile
			echo "$id_pop $i" >> $ofile
			echo "$id_mut $m" >> $ofile
			echo "$id_cro $c" >> $ofile
			nexp=$((nexp+1))
		done
	done
done

