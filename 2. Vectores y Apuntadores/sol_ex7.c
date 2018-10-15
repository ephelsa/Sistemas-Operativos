#include <stdio.h>

#define ASIG 5


/****************************/
/* Declaracion de funciones */
/****************************/
void shellSort(double[], int);
void llenarAsignaturas(double[], int);
void mediaEstudiante(double[], int, double[]);
void mediaAsignatura(double[], int, double[]);
double mediaTotal(double[], int);


/********************/
/* Metodo principal */
/********************/
int main(int argc, char *argv[]) {
  int total_estudiantes = 0;

  printf("Ingrese el numero de estudiantes: ");
  scanf("%d", &total_estudiantes);

  double asignaturas[total_estudiantes * ASIG];
  double mEstudiantes[total_estudiantes];
  double mAsignatura[ASIG];
  double mTotal;

  llenarAsignaturas(asignaturas, total_estudiantes);
  mediaEstudiante(asignaturas, total_estudiantes, mEstudiantes);
  mediaAsignatura(asignaturas, total_estudiantes, mAsignatura);  

  
  /* Printing section */

  for (int i = 0; i < total_estudiantes; i++) {
    printf("Media E%d = %1.2lf\n", (i + 1), mEstudiantes[i]);
  }
  printf(" - - - - - \n");

  for (int i = 0; i < ASIG; i++) {
    printf("Media A%d = %1.2lf\n", (i + 1), mAsignatura[i]);
  }
  printf(" - - - - - \n");

  mTotal = mediaTotal(mEstudiantes, total_estudiantes);
  printf("Media total = %1.2lf\n", mTotal);
  printf(" - - - - - \n");

  return 0;
}

/***************************/
/* Definicion de funciones */
/***************************/

/**
 *  @brief  Es para llenar las ASIG = 5 notas de los estudiantes. Se dice que era 5 por comodidad.
 *  @param  asignaturas[] El arreglo donde estan las asignaturas. Se ingresa para ser modificado.
 *  @param  total_estudiantes Es el total de estudiantes que se tienen.
 *  @return void
 */
void llenarAsignaturas(double asignaturas[], int total_estudiantes) {
  int index = 0;

  for (int i = 0; i < total_estudiantes; i++) {
    for (int j = 0; j < ASIG; j++) {
      double *nota = &asignaturas[index];

      printf("Asignatura %d - Estudiante %d > ", (j + 1), (i + 1));
      fflush(stdin);
      scanf("%lf", nota);
      index++;
    }

    printf(" - - - - - - - \n");
  }
}

/**
 *  @brief  Calcula la media de cada estudiante.
 *  @param  asignaturas[] El arreglo donde estan las asignaturas.
 *  @param  total_estudiantes Es el total de estudiantes que se tienen.
 *  @param  mediaEstudiante[] Es donde se ingresaran la media de cada estudiante.
 *  @return void
 */
void mediaEstudiante(double asignaturas[], int total_estudiantes, double mediaEstudiante[]) {
  int counter = 0;

  for (int i = 0; i < total_estudiantes; i++) {
    double *media = &mediaEstudiante[i];
    *media = 0;

    for (int j = 0; j < ASIG; j++) {
      *media += asignaturas[counter];

      counter++;
    }

    *media = *media / ASIG;
  }

  shellSort(mediaEstudiante, total_estudiantes);
}

/**
 *  @brief  Calcula la media de cada asignatura.
 *  @param  asignaturas[] El arreglo donde estan las asignaturas.
 *  @param  total_estudiantes Es el total de estudiantes que se tienen.
 *  @param  mediaEstudiante[] Es donde se ingresaran la media de cada asignatura.
 *  @return void
 */
void mediaAsignatura(double asignaturas[], int total_estudiantes, double mediaAsignatura[]) {
  int counter = 0;

  for (int i = 0; i < ASIG; i++) {
    double *media = &mediaAsignatura[i];
    *media = 0;

    for (int j = i; j < ASIG * total_estudiantes; j += 5) {
      *media += asignaturas[j];
    }

    *media = *media / total_estudiantes;
  }
}

/**
 *  @brief  Calcula la media total del curso.
 *  @param  mediaEstudiantes[] El arreglo donde estan las medias de los estudiantes
 *  @param  total_estudiantes Es el total de estudiantes que se tienen.
 *  @return double El valor de la media.
 */
double mediaTotal(double mediaEstudiantes[], int total_estudiantes) {
  double ans = 0;

  for (int i = 0; i < total_estudiantes; i++) {
    ans += mediaEstudiantes[i];
  }

  ans = ans / total_estudiantes;

  return ans;
}

/**
 *  @brief  Shell sort para ordenar los datos en el vector.
 *  @param  v[] Ingreso del vector
 *  @param  array_size Es la longitud del vector
 *  @return void
 */
void shellSort(double v[], int array_size) {
  int intervalo, i, j, k;
  intervalo = array_size / 2;

  while (intervalo > 0) {
    for (i = intervalo; i < array_size; i++) {
      j = i - intervalo;
      while (j >= 0) {
        k = j + intervalo;
        if (v[j] >= v[k])
          j = -1;
        else {
          double temp, *p1, *p2;
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