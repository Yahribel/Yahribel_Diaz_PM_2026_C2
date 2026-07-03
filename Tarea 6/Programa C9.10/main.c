#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    long matricula;
    char nombre[20];
    int carrera;
    float promedio;
} alumno;

void modifica(FILE *);

void main(void)
{
    FILE *ar;
    if((ar = fopen("ad1.dat", "r+b")) != NULL)
    {
        modifica(ar);
        fclose(ar);
    }
    else
    {
        printf("\nEl archivo no se puede abrir");
    }
}

void modifica(FILE *ap)
{
    int d;
    alumno alu;
    printf("\nIngrese el numero de registro que desea modificar: ");
    if (scanf("%d", &d) != 1) return;
    while (getchar() != '\n');

    fseek(ap, (d-1)*sizeof(alumno), 0);

    fread(&alu, sizeof(alumno), 1, ap);

    printf("\nIngrese el promedio correcto del alumno: ");
    if (scanf("%f", &alu.promedio) != 1) return;
    while (getchar() != '\n');

    fseek(ap, (d-1)*sizeof(alumno), 0);

    fwrite(&alu, sizeof(alumno), 1, ap);

    fflush(ap);
}
