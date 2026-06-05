#include <stdio.h>
#include <stdlib.h>

int mcd(int, int);

void main(void)
{
    int NU1, NU2, RES;
    printf("\nIngresa los dos numeros enteros: ");
    scanf("%d %d", &NU1, &NU2);
    RES = mcd (NU1, NU2);
    printf("\nEl maximo comun divisor de %d y %d es: %d", NU1, NU2, RES);
}

int mcd(int N1, int N2)
{
    while (N1 != N2)
    {
        if (N1 > N2)
            N1 = N1 - N2;
        else
            N2 = N2 - N1;
    }
}
