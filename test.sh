#!/bin/bash

echo --------test.c--------
./build/compiler -S ./test.c -o ./test.S

#num=0
#i=0
#for file in $(ls ./functional)
#do
#    if((${i}==${num}))
#    then
#        echo --------${file}--------
#        ./build/compiler -e ./functional/${file}
#    fi
#    let "i++"
#done