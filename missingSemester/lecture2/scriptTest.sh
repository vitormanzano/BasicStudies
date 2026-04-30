#!/bin/bash

chmod +x script.sh

times=0

output=0

while [ $output == 0 ]; do
    ((times++))
    ./script.sh 2> erro.txt
    output=$?

done
echo "$2"
echo "$output" 
echo "$times"
