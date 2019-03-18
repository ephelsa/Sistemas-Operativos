#!/bin/bash

clear

echo Script: GCC
gcc -fopenmp main.c mfile/mfile.c merror/merror.c moperation/moperation.c -o multiplication_s.out -lpthread -Wall

echo Script: Executing 
echo ""

./multiplication_s.out "$1" files/a.txt files/b.txt