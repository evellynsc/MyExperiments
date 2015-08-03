#!/bin/bash

# ./create-run-file.sh [number-replications] 
# 		[time-limit] [required-time] [total-rsu] [input-file]

number_replication=$1
time_limit=$2
required_time=$3
total_rsu=$4
input_file=$5


output_file="$input_file-tau$required_time-k$total_rsu"
run_file="$input_file-tunning.sh"

random_exp=( $(echo "1 2 3 4 5 6 7 8" | sed -r 's/(.[^ ]* )/ \1 /g' | tr " " "\n" | shuf | tr -d " " ) )

for i in ${random_exp[@]}
do
	echo "./deploy $number_replication $time_limit $required_time $total_rsu"\
		"../ga_parameters/exp$i.ga $input_file $output_file-exp$i.out" >> $run_file
done