#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Hanoi(int n, char origen, char destino, char auxiliar, FILE *archivo, int *contador);


int main()
{
    int discos;
    int total_movimientos;
    int contador_pasos = 0;

    do {
        printf("Digite el numero de discos: ");
        if (scanf("%d", &discos) != 1){
            printf("Digite un numero valido\n");
            while(getchar() != '\n');
            discos = 0;
            continue;
        }
        if (discos <= 0) {
            printf("El numero de discos debe ser mayor a 0\n\n");

        }
    }while (discos <= 0);

    FILE *archivo_txt = fopen("Movimientos_hanoi.txt", "w");
    if(archivo_txt == NULL){
        printf("No se puedo crear o abrir el archivo\n");
        return 1;
    }
    fprintf(archivo_txt,"REGISTRO DE MOVIMIENTOS - TORRES DE HANOI (%d discos)\n", discos);

    Hanoi(discos, 'A', 'C', 'B', archivo_txt, &contador_pasos);

    total_movimientos = (int)pow(2, discos) - 1;

    fprintf(archivo_txt, "Conclusion\n");
    fprintf(archivo_txt, "Total de movimientos calculados teoricamente: %d\n", total_movimientos);
    fprintf(archivo_txt, "Total de movimientos registrados en el archivo: %d\n", contador_pasos);

    fclose(archivo_txt);

    printf("Total de movimientos: %d\n", contador_pasos);

    return 0;
}

void Hanoi(int n, char origen, char destino, char auxiliar, FILE *archivo, int *contador){

if (n == 1){
    (*contador)++;

    fprintf(archivo, "Movimiento %d: mover disco 1 desde la torre %c hasta la torre %c\n", *contador, origen, destino);
    return;
}

Hanoi(n - 1, origen, auxiliar, destino, archivo, contador);

(*contador)++;
fprintf(archivo, "Movimiento %d: Mover disco %d desde la torre %c hasta la torre %c\n", *contador, n, origen, destino);

Hanoi(n - 1, auxiliar, destino, origen, archivo, contador);
}
