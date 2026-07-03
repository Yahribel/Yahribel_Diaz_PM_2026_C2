#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    long matricula;
    char nombre[20];
    long carrera;
    float promedio;
}alumno;

void escribe(FILE *);

void main(void)
{
    FILE *ar;
    if ((ar = fopen("ad1.dat", "w")) != NULL)
        escribe(ar);
    else
        printf("\nEl archivo no se puede abrir");
    fclose(ar);
}

void escribe(FILE *ap)
{
    alumno alu;
    int i = 0, r;
    printf("\n¿Desea ingresar informacion sobre alumnos? (Si-1 No-0): ");
    scanf("%d", &r);
    while (getchar() != '\n');

    while(r)
    {
        i++;
        printf("Matricula del alumno %d: ", i);
        scanf("%ld", &alu.matricula);
        while (getchar() != '\n');

        printf("Nombre del alumno %d: ", i);
        fgets(alu.nombre, sizeof(alu.nombre), stdin);
        alu.nombre[strcspn(alu.nombre, "\n")] = '\0';

        printf("Carrera del alumno %ld: ", i);
        scanf("%ld", &alu.carrera);
        while (getchar() != '\n');

        printf("Promedio del alumno %d: ", i);
        scanf("%f", &alu.promedio);
        while (getchar() != '\n');

        fwrite(&alu, sizeof(alumno), 1, ap);

        printf("\n¿Desea ingresar informacion sobre mas alumnos? (Si-1 No-0): ");
        scanf("%d", &r);
        while (getchar() != '\n');

    }
}
