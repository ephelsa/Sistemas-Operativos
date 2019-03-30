 #!/bin/bash

#clear

echo Script: GCC
gcc-8 -fopenmp main.c mfile/mfile.c merror/merror.c moperation/moperation.c -o multiplication_s.out -lpthread -Wall

echo Script: Executing 
echo ""

./multiplication_s.out "$1" ../../benchmark/vec_10_"$3"_a.txt ../../benchmark/vec_10_"$3"_b.txt "$2"
