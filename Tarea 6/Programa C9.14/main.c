#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void minymay(FILE *);

void main(void)
{
    char p;
    FILE *ar;
    if ((ar = fopen("arc5.txt", "r")) != NULL)
    {
        minymay(ar);
        fclose(ar);
    }
    else printf("No se pudo abrir el archivo");
}

void minymay(FILE *arc)
{
    int min = 0, may = 0;
    char p;

    while ((p = fgetc(arc)) != EOF)
    {
        if (islower(p))
            min++;
        else if (isupper(p))
            may++;
    }
    printf("Resultados del Analisis\n");
    printf("Cantidad de letras minuculas: %d\n", min);
    printf("Cantidad de lestras mayusculas: %d\n", may);
}
