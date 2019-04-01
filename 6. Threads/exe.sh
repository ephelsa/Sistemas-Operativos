 #!/bin/bash

#clear

echo Script: GCC
gcc-8 -fopenmp main.c mfile/mfile.c merror/merror.c moperation/moperation.c -o dot_product.out -lpthread -Wall

echo "Script: Executing."
echo ""

# Unique
./dot_product.out "$2" ../../benchmark/vec_10_"$1"_a.txt ../../benchmark/vec_10_"$1"_b.txt "$3"


#mkdir resultados/
#
#N_EX=100
#
#Sequential
#echo "Sequential."
#echo ""
#for file in 1 3 6 8
#do
#    OUT_FILE=resultado_"$file"_s.txt
#
#    for ((j = 0; j < $N_EX; j++))
#    do
#        ./dot_product.out s ../../benchmark/vec_10_"$file"_a.txt ../../benchmark/vec_10_"$file"_b.txt >> $OUT_FILE
#    done
#
#    mv "$OUT_FILE" resultados/
#done
#
#Parallel
#echo "Parallel."
#echo ""
#for file in 1 3 6 8
#do
#    for threads in 2 4 8 16
#    do
#        OUT_FILE=resultado_"$file"_"$threads".txt
#
#        for ((j = 0; j < $N_EX; j++))
#        do
#            ./dot_product.out p ../../benchmark/vec_10_"$file"_a.txt ../../benchmark/vec_10_"$file"_b.txt "$threads" >> $OUT_FILE
#        done
#
#        mv "$OUT_FILE" resultados/
#    done
#done