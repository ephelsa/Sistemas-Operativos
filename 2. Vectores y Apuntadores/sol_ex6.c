#include <stdio.h>


/****************************/
/* Declaracion de funciones */
/****************************/
void shellSort(int[], int);
int calcularMediana(int[], int);


/*********************/
/* Funcion principal */
/*********************/
int main(int argc, char *argv[]) {
  int array_size = 0;
  
  printf("Ingrese el numero de datos: ");
  scanf("%d", &array_size);
  int array[array_size];

  for (int i = 0; i < array_size; i++) {
    printf("Valor (%d/%d) > ", (i + 1), array_size);
    fflush(stdin);
    scanf("%d", &array[i]);
  }

  shellSort(array, array_size);
  printf("La mediana del vector es: %d\n", calcularMediana(array, array_size));


  return 0;
}


/***************************/
/* Definicion de funciones */
/***************************/

/**
 *  @brief  Shell sort para ordenar los datos en el vector.
 *  @param  v[] Ingreso del vector
 *  @param  array_size Es la longitud del vector
 *  @return void
 */
void shellSort(int v[], int array_size) {
  int intervalo, i, j, k;
  intervalo = array_size / 2;

  while (intervalo > 0) {
    for (i = intervalo; i < array_size; i++) {
      j = i - intervalo;
      while (j >= 0) {
        k = j + intervalo;
        if (v[j] <= v[k])
          j = -1;
        else {
          int temp, *p1, *p2;
          p1 = &v[j];
          p2 = &v[k];
          temp = *p1;
          *p1 = *p2;
          *p2 = temp;
          j -= intervalo;
        }
      }
    }
    intervalo = intervalo / 2;
  }
}


/**
 *  @brief  Calcula la mediana de un arreglo impar.
 *  @param  v[] Vector a calcular.
 *  @param  arrray_size Longitud del vector
 *  @return Mediana del arreglo impar y en caso de ser par, retorna -1
 */
int calcularMediana(int v[], int array_size) {
  if ((array_size % 2) != 0)
    return v[array_size / 2];

  return -1;
}