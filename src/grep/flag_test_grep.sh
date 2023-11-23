#!/bin/bash

option=(e i v l n h s)
files=(1.txt 2.txt "1.txt 2.txt")
pattern=""


for ((i = 0; i < ${#option[@]}; i++))
do
    for ((j = 0; j < ${#option[@]}; j++))
    do
        if [ $i != $j ]
        then           
                grep -${option[$i]}${option[$j]} hey ${files[0]} ${files[1]} > grep.txt
                ./grep -${option[$i]}${option[$j]} hey ${files[0]} ${files[1]} > grep.txt
                result=$(diff grep.txt grep.txt)
                if [[ $result == "" ]]; then
                    echo SUCCESS -${option[$i]}${option[$j]} hey ${files[0]} ${files[1]}
                else
                    echo FAIL -${option[$i]}${option[$j]} hey ${files[0]} ${files[1]}
                    exit 1
                fi
        fi
    done
done