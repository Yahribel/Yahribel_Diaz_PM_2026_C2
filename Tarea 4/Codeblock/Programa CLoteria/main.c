#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int NUM_MAX = 40;

void main(void)
{
    int opcion;
    int cant_jugadas = 1;
    int i;
    int numeros[100];
    int dinero[100];
    int ganador;

    srand(time(NULL));

    do {
        printf("\n LOTEKA TE TOCA");
        printf("\n1. Jugar (Cantidad de jugadas: %d)", cant_jugadas);
        printf("\n2. Elegir cantidad de jugadas");
        printf("\n3. Salir");
        printf("\nElija una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 2:
            printf("\nDigite la cantidad jugadas: ");
            scanf("%d", &cant_jugadas);

            if(cant_jugadas < 1){
                cant_jugadas = 1;
            }
            break;

        case 1:
            printf("\nLoteria\n");
            for(i = 0; i < cant_jugadas; i++)
            {
                printf("\nJugada %d\n", i + 1);

                do{
                    printf("Digite el numero: ");
                    scanf("%d", &numeros[i]);
                    if(numeros[i] < 1 || numeros[i] > NUM_MAX){
                        printf("No valido\n");
                    }
                } while(numeros[i] < 1|| numeros[i] > NUM_MAX);

                printf("Cantidad de dinero: ");
                scanf("%d", &dinero[i]);
            }
            printf("\nLoteria final\n");
            for(i = 0; i < cant_jugadas; i++)
            {
                ganador = (rand() % NUM_MAX) + 1;
                int premio = 0;

                if(numeros[i] == ganador){
                    premio = dinero[i] * 1000;
                }
                printf("Numero: %d\tDinero: %d\tPremio: %d\t(Tombola: %d)\n",
                       numeros[i], dinero[i], premio, ganador);
            }
            printf("\n");
            break;


        case 3:
            printf("\nLoteka");
            break;

        default:
            printf("\nIntente de nuevo");
        }
    }while(opcion != 3);

}

