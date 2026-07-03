#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void cambia(FILE *, FILE *);

void main(void)
{
    FILE *ar;
    FILE *ap;
    ar = fopen("C:\\Users\\user\\Documents\\Codeblock\\Programa C9.17\\arc.txt", "r");
    ap = fopen("C:\\Users\\user\\Documents\\Codeblock\\Programa C9.17\\arc1.txt", "w");

    if ((ar != NULL) && (ap != NULL))
    {
        cambia(ar, ap);
        fclose(ar);
        fclose(ap);
    }
    else
        printf("No se pueden abrir los archivos");
}

void cambia(FILE *ap1, FILE *ap2)
{

    char cad[200];
    char *cad2;

    while (fgets(cad, sizeof(cad), ap1) != NULL)
    {

        cad2 = strstr(cad, "mexico");

        while (cad2!=NULL)
        {
            cad2[0]= 'M';

            cad2 = strstr(cad2 + 1, "mexico");
        }
        fputs(cad, ap2);
    }
}
