#!/bin/bash

boards=( 'a/b/c' 'b/c/d' 'c/d/e' 'e/f/g' )

for brd in ${boards[@]}
do
./test_data_consistency_Level_0_ireg.sh $brd
./test_data_consistency_Level_1_ireg.sh $brd
./test_data_consistency_Level_10_ireg.sh $brd
./test_data_consistency_Level_20_ireg.sh $brd
./test_data_consistency_Level_31_ireg.sh $brd
./test_data_consistency_Level_32_ireg.sh $brd
./test_data_consistency_Level_100_ireg.sh $brd
./test_data_consistency_Level_invalid_ireg.sh $brd
./test_data_consistency_Level_0_tango.sh $brd
./test_data_consistency_Level_1_tango.sh $brd
./test_data_consistency_Level_10_tango.sh $brd
./test_data_consistency_Level_20_tango.sh $brd
./test_data_consistency_Level_31_tango.sh $brd
./test_data_consistency_Level_32_tango.sh $brd
./test_data_consistency_Level_100_tango.sh $brd
./test_data_consistency_Level_invalid_tango.sh $brd
done
