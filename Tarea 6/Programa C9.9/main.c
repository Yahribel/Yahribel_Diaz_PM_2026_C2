#include <stdio.h>
#include <stdlib.h>

typedef struct{
long matricula;
char nombre[20];
long carrera;
float promedio;
} alumno;

void lee(FILE *);

void main(void)
{
    FILE *ar;
    if((ar = fopen("ad1.dat", "r")) != NULL)
        {
            lee(ar);
        fclose(ar);
        }
    else
        printf("\nEl archivo no se puede abrir");
    fclose(ar);
}

void lee(FILE *ap)
{
    alumno alu;
    fread(&alu, sizeof(alumno), 1, ap);

    while (!feof(ap))
    {
        printf("\nMatricula: %ld", alu.matricula);
        printf("\tCarrera: %ld", alu.carrera);
        printf("\tPromedio: %f\t", alu.promedio);
        puts(alu.nombre);
        fread(&alu, sizeof(alumno), 1, ap);
    }
}
