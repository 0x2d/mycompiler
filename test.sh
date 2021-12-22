#!/bin/bash

num=23
i=0
echo --------test.c--------
./build/compiler -e test.c
for file in $(ls ./functional)
do
    if((${i}<=${num}))
    then
        let "i++"
        echo --------${file}--------
        ./build/compiler -e ./functional/${file}
    else
        break
    fi
done