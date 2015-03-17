#!/bin/bash

file=("E3-T-60s-4CP")
lines=46
columns=9876
tau=(20 40 60)
ap=(0 0 0)
index=0
replications=10
pop_id=(3 4)


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
for k in ${pop_id[@]}
do
    for i in ${ap[@]}
    do
        for j in ${tau[@]} 
        do
            if [ "$i" = 14 ] && [ "$j" = 60 ]; then
                echo
            elif [ "$i" = 5 ] && [ "$j" = 20 ]; then
                echo
            elif [ "$i" = 23 ] && [ "$j" = 20 ]; then
                echo
            else
                outputfile="logs/$file-k$i-tau$j-pop$k.out"
                inputfile="~/deploy/dataset/$file"
                outputterminal="$outputfile.terminal"
                ga="~/deploy/ga_parameters/e3-k$i-t$j-pop$k.ga"
                command="./ga $replications $j $i $ga $inputfile $outputfile > $outputterminal;"
                eval $command
#                echo $command
            fi            
        done
    done
done


#     echo "Sorry, you are out of the age range."
# elif [ "$AGE" -ge 20 ] && [ "$AGE" -lt 30 ]; then
#     echo "You are in your 20s"
# elif [ "$AGE" -ge 30 ] && [ "$AGE" -lt 40 ]; then
#     echo "You are in your 30s"
# elif [ "$AGE" -ge 40 ] && [ "$AGE" -lt 50 ]; then
#     echo "You are in your 40s"
# fi

            


# [number-replications] [required-time=tau] [total-rsu=ap] [param-genetic-file] [input-file] [output-file]
