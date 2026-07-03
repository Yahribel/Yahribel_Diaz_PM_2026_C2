#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int matricula;
    char nombre[20];
    int carrera;
    float promedio;
}alumno;

void ordena(FILE *, FILE *);
void crearArchivoDePrueba(void);
void muestraArchivo6(void);

void main(void)
{
    crearArchivoDePrueba();

    FILE *ar1, *ar2;
    ar1 = fopen("ad5.dat", "rb");
    ar2 = fopen("ad6.dat", "wb");

    if ((ar1 != NULL) && (ar2 != NULL))
    {
        ordena(ar1, ar2);
        fclose(ar1);
        fclose(ar2);

        muestraArchivo6();
    }
    else
    {
        printf("\nEl o los archivps no se pudieron abrir");


    if(ar1 != NULL) fclose(ar1);
    if(ar2 != NULL) fclose(ar2);
    }
}

void crearArchivoDePrueba(void)
{
    FILE *f = fopen("ad5.dat", "wb");
    if (f != NULL)
    {
        alumno lista[3] = {
        {101, "Juan", 1, 8.5},
        {102, "Maria", 2, 9.2},
        {103, "Pedro", 1, 7.8}
    };
    fwrite(lista, sizeof(alumno), 3, f);
    fclose(f);
    }
}

void ordena(FILE *ap1, FILE *ap2)
{
    alumno alu;
    int t, n, i;
    t = sizeof(alumno);

    fseek(ap1, 0, 2);
    n = ftell(ap1) / t;


    for (i = (n-1); i>= 0; i--)
    {
        fseek(ap1, i * t, 0);
        fread(&alu, t, 1, ap1);
        fwrite(&alu, t, 1, ap2);
    }
}

void muestraArchivo6(void)
{
    FILE *f = fopen("ad6.dat", "rb");
    alumno alu;

    if (f != NULL)
    {
        printf("Contenido de archivo 6 invertido \n");

        while (fread(&alu, sizeof(alumno), 1, f) ==1)
        {
            printf("Matricula: %d | Nombre: %-20s | Carrera: %d | Promedio: %.2f\n",
                   alu.matricula, alu.nombre, alu.carrera, alu.promedio);
        }
        fclose(f);
    }
    else
    {
        printf("No se pudo leer");
    }
}
