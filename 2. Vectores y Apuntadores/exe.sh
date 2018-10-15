#!/bin/bash

if [ ${#1} -ne 0 ]; then
  clear
  gcc -o p$1.out sol_ex$1.c -Wall
  ./p$1.out
else 
  echo "Ingrese un numero para el ejercicio a compilar."
fi
