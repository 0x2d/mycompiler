#!/bin/bash

num=23
i=0
echo --------test.c--------
./mycompiler -f test.c
for file in $(ls ./functional)
do
    if((${i}<=${num}))
    then
        let "i++"
        echo --------${file}--------
        ./mycompiler -f ./functional/${file}
    else
        break
    fi
done