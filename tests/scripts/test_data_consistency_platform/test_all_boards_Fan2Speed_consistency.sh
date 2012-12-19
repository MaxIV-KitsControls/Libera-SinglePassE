#!/bin/bash

boards=( 'a/b/c' 'b/c/d' 'c/d/e' 'e/f/g' )

for brd in ${boards[@]}
do
./test_data_consistency_Fan2Speed.sh $brd
done
