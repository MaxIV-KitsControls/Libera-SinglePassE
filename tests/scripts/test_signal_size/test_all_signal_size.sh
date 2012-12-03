#!/bin/bash

boards=( 'a/b/c' 'b/c/d' 'c/d/e' 'e/f/g' )

for brd in ${boards[@]}
do
./test_signal_size1.sh $brd
./test_signal_size10.sh $brd
./test_signal_size55.sh $brd
./test_signal_size100.sh $brd
./test_signal_size5400.sh $brd
./test_signal_size7300.sh $brd
./test_signal_size8192.sh $brd
./test_signal_size8193.sh $brd
done
