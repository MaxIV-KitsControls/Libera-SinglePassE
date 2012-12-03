#!/bin/bash

boards=( 'a/b/c' 'b/c/d' 'c/d/e' 'e/f/g' )

for brd in ${boards[@]}
do
./test_buffer_size_1.sh $brd
./test_buffer_size_10.sh $brd
./test_buffer_size_13.sh $brd
./test_buffer_size_100.sh $brd
./test_buffer_size_256.sh $brd
./test_buffer_size_8192.sh $brd
./test_buffer_size_8193.sh $brd
./test_buffer_size_1000000.sh $brd
done

