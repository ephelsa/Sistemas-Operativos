#include <stdio.h>
#define N 1000
#define TRUE 1

/*********************************************************/
/*            Declaraciones de las funciones             */
/*********************************************************/

/* Funciones del programa */
int esLetra(char);
void volverMayuscula(char*);
void stringToMayuscula(char[]);
void limpiarCadena(char[], int);

/*********************************************************/
/*                     Funcion main                      */
/*********************************************************/

int main(void) {
  // Code
  while (TRUE) {
    char str[N];  // Declaracion de la cadena con un limite de N.
    int ch, n = 0;  // Define el caracter y el size de la cadena escrita

    printf("Entrada > ");

    // Lee caracter por caracter ingresado hasta que se presione enter o CTRL + D
    while ((ch = getchar()) != '\n' && n < N) {
      if (ch == EOF) {
        printf("\n");

        return 0;
      }

      str[n] = ch;
      ++n;
    }

    limpiarCadena(str, n);
    stringToMayuscula(str);
    printf("%s\n", str);
  }


  return 0;
}

/*********************************************************/
/*             Definiciones de las funciones             */
/*********************************************************/

/* Funciones del programa */

/**  
 *   @brief  Determina si un caracter alfabetico
 *  
 *   @param  ch es el caracter a verificar
 *   @return 1 si el caracter es una letra del alfabeto y 0 si es otro simbolo.
 */
int esLetra(char ch) {
  // Coloque el codigo solucion a continuacion...
  if ((ch >=65 && ch <= 90) || (ch >=97 && ch <= 122))
    return 1;
  else
    return 0;
}

/**  
 *   @brief  Convierte un caracter en mayuscula
 *  
 *   @param  ch es el caracter ingresado
 *   @return void
 */
void volverMayuscula(char *ch) {
  // Coloque el codigo solucion a continuacion...
  if (*ch >=97 && *ch <= 122)
    *ch -= 32;
}

/**  
 *   @brief  Convierte en mayusculas la cadena de caracteres ingresada.
 *  
 *   @param  s es una cadena de caracteres ingresada y la cual despues del proceso en la función tendra los caracteres en mayuscula.
 *   @return void
 */
void stringToMayuscula(char s[]) {
  // Coloque el codigo solucion a continuacion...  
  for (int i = 0; s[i] != '\0'; i++) {
    char *ch = &s[i]; 

    if (esLetra(*ch))
      volverMayuscula(ch);  
  }
}

/**
 *  @brief  Despues del primer ingreso de palabras, si el numero de char es mayor al ingreso siguiente, evita que sea
 *          salgan los nuevos y los viejos caracteres concatenados.
 * 
 *  @param  str[] es la cadena a limpiar.
 *  @param  int es a partir de un posicion.
 *  @return void
 */
void limpiarCadena(char str[], int index) {
  char *ch = &str[index];

  for (int i = index; *ch != '\0'; i++) {
    *ch = '\0';
    ch = &str[index];
  }
}