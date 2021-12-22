#!/bin/bash

num=28
i=0
echo --------test.c--------
./build/compiler -e test.c
for file in $(ls ./functional)
do
    if((${i}==${num}))
    then
        echo --------${file}--------
        ./build/compiler -e ./functional/${file}
    fi
    let "i++"
done