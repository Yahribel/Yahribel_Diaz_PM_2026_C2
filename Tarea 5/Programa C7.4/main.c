#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    /*Este codigo va a dar error, ya que 'char *cad1 = ""; gets(cad1);' es correcto, pero Da error porque "" esta vacio
    en una memoria protegida de solo lectura y solo tiene espacio para un byte, al usar gets() intentas escribir en un lugar prohibido y sin espacio*/
    char *cad0;
    cad0 = "Argentina";
    puts(cad0);

    cad0 = "Brasil";
    puts(cad0);
    char *cad1;
    /*gets(*cad1);
    gets(cad1) generan un error ambas lecturas*/


    char *cad1 = "";
    gets(cad1);

    /*char cad1[];*/

    char cad2[20] = "Mexico";
    puts(cad2);
    gets(cad2);

    puts(cad2);
    cad2[10] = "Guatemala";
}
