#!/bin/bash

boards=( 'test/itech/libera-spe4' 'test/itech/libera-spe5' 'test/itech/libera-spe6' 'test/itech/libera-spe7' )

for brd in ${boards[@]}
do
echo ./test_data_consistency_Level_0_ireg.sh $brd
./test_data_consistency_Level_0_ireg.sh $brd

echo ./test_data_consistency_Level_1_ireg.sh $brd
./test_data_consistency_Level_1_ireg.sh $brd

echo ./test_data_consistency_Level_10_ireg.sh $brd
./test_data_consistency_Level_10_ireg.sh $brd

echo ./test_data_consistency_Level_20_ireg.sh $brd
./test_data_consistency_Level_20_ireg.sh $brd

echo ./test_data_consistency_Level_31_ireg.sh $brd
./test_data_consistency_Level_31_ireg.sh $brd

echo ./test_data_consistency_Level_32_ireg.sh $brd
./test_data_consistency_Level_32_ireg.sh $brd

echo ./test_data_consistency_Level_100_ireg.sh $brd
./test_data_consistency_Level_100_ireg.sh $brd

echo ./test_data_consistency_Level_invalid_ireg.sh $brd
./test_data_consistency_Level_invalid_ireg.sh $brd

echo ./test_data_consistency_Level_0_tango.sh $brd
./test_data_consistency_Level_0_tango.sh $brd

echo ./test_data_consistency_Level_1_tango.sh $brd
./test_data_consistency_Level_1_tango.sh $brd

echo ./test_data_consistency_Level_10_tango.sh $brd
./test_data_consistency_Level_10_tango.sh $brd

echo ./test_data_consistency_Level_20_tango.sh $brd
./test_data_consistency_Level_20_tango.sh $brd

echo ./test_data_consistency_Level_31_tango.sh $brd
./test_data_consistency_Level_31_tango.sh $brd

echo ./test_data_consistency_Level_32_tango.sh $brd
./test_data_consistency_Level_32_tango.sh $brd

echo ./test_data_consistency_Level_100_tango.sh $brd
./test_data_consistency_Level_100_tango.sh $brd

echo ./test_data_consistency_Level_invalid_tango.sh $brd
./test_data_consistency_Level_invalid_tango.sh $brd
done
