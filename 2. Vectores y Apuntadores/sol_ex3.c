#include <stdio.h>

// Methods
char *obtenerSubcadena(char*, int);


int main(int argc, char *argv[]) {
  // Code
  char str[1000];
  char *new_str;

  int index;

  printf("Ingrese la cadena: ");
  gets(str);

  printf("Indice: ");
  fflush(stdin);  // Limpiar el buffer de entrada de texto
  scanf("%d", &index);

  new_str = obtenerSubcadena(str, index);

  printf("%s\n", new_str);  // Imprimir la subcadena

  
  return 0;
}

/**
 *   @brief  Obtiene una subcadena a tomada a partir de un subindice asociado a una subcadena
 * 
 *   @param  array cadena de caracteres a ingresar
 *   @param  index indice
 *   @return un apuntador a la posicion inicial de la subcadena o NULL si el tamaño de index supera a la longitud de la cadena
 */
char *obtenerSubcadena(char *array, int index) {
  // Coloque su codigo aqui...
  char *sub_str = &array[index];

  return sub_str;
}