# !/bin/bash

option=(-b -e -n -s -t)
files=(1.txt "1.txt")

for ((i = 0; i < ${#option[@]}; i++))

do 
    
    cat ${option[$i]} ${files[0]}> cat.txt
    ./s21_cat ${option[$i]} ${files[0]}> s21cat.txt
    result=$(diff cat.txt s21cat.txt)
    if [[ $result == "" ]]; then
        echo SUCCESS ${option[$i]} ${files[0]}
    else
        echo FAIL ${option[$i]} ${files[0]}
        exit 1
    fi
done