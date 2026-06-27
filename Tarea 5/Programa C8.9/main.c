#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char zona[20];
    char calle[20];
    char colo[20];
} ubicacion;

typedef struct
{
    char clave[5];
    float scu;
    float ste;
    char car[50];
    ubicacion ubi;
    float precio;
    char dispo;
} propiedades;

void Lectura(propiedades A[], int T);
void F1(propiedades A[], int T);
void F2(propiedades A[], int T);


void main(void)
{
   propiedades PROPIE[100];
   int TAM;

   do
   {
       printf("Ingrese el numero de propiedades: ");
       scanf("%d", &TAM);


   }
   while (TAM > 100 || TAM < 1);

   Lectura(PROPIE, TAM);
   F1(PROPIE, TAM);
   F2(PROPIE, TAM);

}

void Lectura(propiedades A[], int T)
{
    int I;
    for (I = 0; I < T; I++)
    {
        printf("\n\tIngrese datos dela propiedad %d", I + 1);
        while (getchar() != '\n');

        printf("\nClave: ");
        gets(A[I].clave);

        printf("Superficie cubierta: ");
        scanf("%f", &A[I].scu);
        while (getchar() != '\n');

        printf("Superficie terreno: ");
        scanf("%f", &A[I].ste);
        while (getchar() != '\n');

        printf("Caracteristicas: ");
        gets(A[I].car);

        printf("\tZona: ");
        gets(A[I].ubi.zona);

        printf("\tCalle: ");
        gets(A[I].ubi.calle);

        printf("\tColonia: ");
        gets(A[I].ubi.colo);

        printf("Precio: ");
        scanf("%f",&A[I].precio);
        while (getchar() != '\n');

        printf("Disponibilidad (Venta-V Renta-R): ");
        scanf("%c", &A[I].dispo);


    }
}

void F1(propiedades A[], int T)
{
    int I;
    printf("\n\t\tListado de Propiedades para Ventas en Miraflores");
    for (I = 0; I < T; I++)
    {
       if ((strcmp(A[I].ubi.zona, "Miraflores") == 0 || strcmp(A[I].ubi.zona, "miraflores") == 0) &&
            (A[I].dispo == 'V' || A[I].dispo == 'v')&&
            (A[I].precio >= 450000) && (A[I].precio <= 650000))
       {
printf("\nClave de la proedad: ");
puts(A[I].clave);
printf("Superficie cubierta: %.2f", A[I].scu);
printf("Superficie terreno: %.2f", A[I].ste);
printf("Caracteristicas: ");
puts(A[I].car);
printf("Calle: ");
puts(A[I].ubi.calle);
printf("Colonia: ");
puts(A[I].ubi.colo);
printf("Precio: %.2f\n", A[I].precio);
       }
    }
}

void F2(propiedades A[], int T)
{
    int I;
    float li, ls;
    char zon[20];

    printf("\n\n\t\tListado de  propiedades para renta");
    while (getchar() != '\n');

    printf("\nIngrese zona geografica: ");
    gets(zon);

    printf("Ingrese el limite inferior del precio: ");
    scanf("%f", &li);

    printf("Ingrese el limite superior del precio: ");
    scanf("%f", &ls);

    printf("\nResultado encontrado para Renta en %s:", zon);

    for (I = 0; I < T; I++)
    {
        if ((strcmp(A[I].ubi.zona, zon) == 0) &&
            (A[I].dispo == 'R' || A[I].dispo== 'r')&&
            (A[I].precio >= li)&& (A[I].precio <= ls))
        {
            printf("\nClave de la propiedad: ");
            puts (A[I].clave);
            printf("Superficie cubierta: %.2f", A[I].scu);
            printf("Superficie terreno: %.2f", A[I].ste);
            printf("Caracteristicas: ");
            puts(A[I].car);
            printf("calle: ");
            puts(A[I].ubi.calle);
            printf("Colonia: ");
            puts(A[I].ubi.colo);
            printf("Precio: %.2f\n", A[I].precio);
        }
    }
}
