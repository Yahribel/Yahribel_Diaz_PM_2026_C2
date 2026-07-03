#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    char p1;
    FILE *ar;
    ar = fopen("libro.txt", "a");
    if (ar != NULL)
    {
        printf("Escribe el texto que deseas anadir el archivo \n");
        while ((p1 = getchar()) != '\n')
        {
            fputc(p1, ar);
        }
        fclose(ar);
        printf("\nTexto agregado\n");
    }
    else
        printf("No se puede abrir el archivo");
}
