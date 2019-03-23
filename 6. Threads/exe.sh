 #!/bin/bash

#clear

echo Script: GCC
gcc-8 -fopenmp main.c mfile/mfile.c merror/merror.c moperation/moperation.c -o multiplication_s.out -lpthread -Wall

echo Script: Executing 
echo ""

./multiplication_s.out "$1" files/vec_10_6_a.txt files/vec_10_6_b.txt "$2"

#./multiplication_s.out "$1" ../../benchmark/vec_10_8_a.txt ../../benchmark/vec_10_8_b.txt "$2"