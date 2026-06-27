#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void interpretar(char *);

void main(void)
{
    char cad[50];
    printf("\nIngrese la cadena de caracteres: ");
    gets(cad);
    interpretar(cad);
}

void interpretar(char *cadena)
{
    int i = 0, j, k;
    while (cadena[i] != '\0')
    {
        if (isalpha(cadena [i]))
        {
            k = cadena[i - 1] - 48;
            for (j = 0; j < k; j++)
                putchar(cadena[i]);
        }
        i++;
    }
}
