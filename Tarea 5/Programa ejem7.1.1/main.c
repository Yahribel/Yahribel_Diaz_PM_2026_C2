#include <stdio.h>
#include <stdlib.h>

void lBufIn(void) {
int c;
while ((c = getchar()) != '\n' && c != EOF);
}

void main(void)
{
char p1;


//pedir una letra
printf("\nIngresa una letra del alfabeto: ");
p1 = getchar();

//determinar si es mayuscula o minuscula
if (p1 >= 'A' && p1 <= 'Z')
{
    printf("\n%c es mayuscula y %c es minuscula", p1,(p1+32));
}

if (p1 >= 'a' && p1 <= 'z')
{
    printf("\n%c es minuscula y %c es mayuscula", p1,(p1-32));
}
//convertir al contrario
}

