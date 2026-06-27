#include <stdio.h>
#include <stdlib.h>

void lBufIn(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void main(void)
{
    char p1, p2, p3 = '$'; // El tipo de dato mas pequeno es de 1 byte 8bytes
    printf("\nIngrese un caracter: ");
    p1 = getchar();
    putchar(p1);
    printf("\n");

    fflush(stdin);

    printf("\nEl caracter p3 es: ");
    putchar(p3);
    printf("\n");

    printf("\nIngrese otro caracter: ");
    lBufIn();

    scanf("%c", &p2);
    printf("%c", p2);
}

