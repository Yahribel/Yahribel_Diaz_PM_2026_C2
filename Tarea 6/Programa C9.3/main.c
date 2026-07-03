#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
    char cad[50];
    int res;
    FILE *ar;
    if ((ar = fopen("arc.txt", "w")) != NULL)
    {
        printf("\n¿Desea ingresar una cadena de caracteres? Si-1 No-0: ");
        scanf("%d", &res);
        while (getchar() != '\n');
        while (res)
        {
            printf("Ingrese la cadena: ");

            fgets(cad, sizeof(cad), stdin);
            cad[strcspn(cad, "\n")] = '\0';
            fputs(cad, ar);

            printf("\n¿Desea ingresar otra cadena de caracteres? Si-1 No-0: ");
            scanf("%d", &res);

            while (getchar() != '\n');

            if (res)
                fputs("\n", ar);
        }
        fclose(ar);
        printf("Se guardo :)\n");
    }
    else
        printf("No se puede abrir el archivo");
}
