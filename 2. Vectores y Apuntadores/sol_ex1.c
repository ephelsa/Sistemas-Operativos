#include <stdio.h>

// Methods
int contarCaracter(char *, char);


int main(int argc, char *argv[]) {
  // Code
  char string[1000];
  char ch;

  printf("Ingresar la cadena de caracteres: ");
  gets(string); // Para leer una linea

  printf("Ingresa el caracter: ");
  fflush(stdin);  // Limpia el buffer de la entrada estandar. Standard Input
  scanf("%c", &ch);

  printf("El numero de caracteres es: %d.\n", contarCaracter(string, ch));

  return 0;
}

/**
 *   @brief  Cuenta las veces que aparece un caracter determinado dentro de una cadena.
 *
 *   @param  array cadena de caracteres a ingresar
 *   @param  ch es el caracter a averiguar
 *   @return el numero de veces que aparece ch en array o -1 si no aparece.
 */
int contarCaracter(char *array, char ch) {
  // Coloque su codigo aqui...
  int counter = 0;

  for(int i = 0; array[i] != '\0'; i++) {
    if (array[i] == ch) {
      counter++;
    }
  }

  if (counter == 0) 
    counter = -1;

  return counter;
}