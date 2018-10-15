#include <stdio.h>

// Methods
int obtenerIndice(char*, char);


int main(int argc, char *argv[]) {
  // Code
  char string[1000];
  char ch;

  printf("Ingresar la cadena de caracteres: ");
  gets(string); // Para leer una linea

  printf("Ingresa el caracter: ");
  fflush(stdin);  // Limpia el buffer de la entrada estandar. Standard Input
  scanf("%c", &ch);

  printf("El indice del primer caracter es: %d.\n", obtenerIndice(string, ch));

  return 0;
}

/**
 *   @brief  Obtiene el indice de la primera aparicion de un caracter en un array
 *
 *   @param  array cadena de caracteres a ingresar
 *   @param  ch es el caracter a ingresa
 *   @return el indice del primer ch en la cadena array
 */
int obtenerIndice(char *array, char ch) {
  // Coloque su codigo aqui...
  int pos = -1;

  for(int i = 0; array[i] != '\0'; i++) {
    if (array[i] == ch) {
      pos = i;
      break;
    }
  }

  return pos;
}