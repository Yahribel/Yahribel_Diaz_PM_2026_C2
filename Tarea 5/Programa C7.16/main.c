#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
    char cad1[50], cad2[50], cad0[50];
    int i = 0;

    printf("\n Ingrese la primera cadena de caracteres: ");
    gets(cad1);

    printf("\n Ingrese la cadena a buscar: ");
    gets(cad2);

    strcpy(cad0, cad1);

    char *puntero = strstr(cad0, cad2);

    while (puntero != NULL)
    {
        i++;
        puntero = strstr (puntero + 1, cad2);
    }

    printf("\nEl numero de veces que aparece la segunda cadena es: %d", i);
}
