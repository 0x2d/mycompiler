#!/bin/bash

num=23
i=0
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