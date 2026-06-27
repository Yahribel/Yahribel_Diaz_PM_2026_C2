#include <stdio.h>
#include <stdlib.h>

void main(void)
{
   char c, cad[10];
   int i = 0;
   float sum = 0.0;

   printf("\nDesea ingresar una cadena de caracteres (S/N)? ");
   c = getchar();
   while (getchar() != '\n');

   while (c == 'S' || c == 's')
   {
       printf("\nIngresa la cadena de caracteres: ");
       gets(cad);

       i++;
       sum += atof(cad);

       printf("\nDesea ingresar otra cadena de caracteres (S/N)? ");
       c = getchar();
       while(getchar() != '\n');
   }
   printf("\nSuma: %.2f", sum);
   printf("\nPromedio: %.2f", sum / i);
}
