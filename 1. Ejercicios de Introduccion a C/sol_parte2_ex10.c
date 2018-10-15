#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void checker(int a,int b);

int main(){

    int bandera=1;
    int num1;
    int num2;
    srand(time(NULL));
    printf("Generaremos 2 números aleatorios para que respondas \n");

    while(bandera==1){
        
        

        num1= rand()%10;
        num2= rand()%10;

        checker(num1,num2);

        printf("¿Quieres continuar? Ingresa 1 para continuar o cualquier otro número para terminar: \n");
        scanf("%d",&bandera);

    }

return 0;
}

void checker(int a, int b){

    int respuesta=0;
    int res;
    int s;
    int t;

    res=a*b;

    while(respuesta!=res){
        printf("¿Cuánto es %d veces %d ? \n",a,b);
        scanf("%d",&respuesta);
        
        if(respuesta==res){
            t= rand()%4 +1;
            switch(t){

                case 1:
                    printf("Muy bien!\n");
                break;
                case 2:
                    printf("Excelente!\n");
                break;
                case 3:
                    printf("Buen trabajo!\n");
                break;
                case 4: 
                    printf("Sigue haciéndolo bien!\n");
                break;
            }
            
            
        }else{
            s= rand()%4 +1;
            switch(s){

                case 1:
                    printf("No. Por favor trata de nuevo.\n");
                break;
                case 2:
                    printf("Incorrecto. Trata una vez más.\n");
                break;
                case 3:
                    printf("No te rindas!\n");
                break;
                case 4: 
                    printf("No. Trata de nuevo\n");
                break;
            }
        }
    }



    return;
}