#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[3];
    int *p;//son numeros de 64bits sin signo
    // que representan una direccion en memoria (byte)
    // que a su ves es el primer elemento de un dato

    for(int index = 0; index < 3; index++)
    {
        printf("\nValor a[%i]:%i",index,a[index]);
    }

    p = &a[0];
    *p = 5;
    p++;
    *p = 10;
    p++;
    *p = 25;

    for(int i = 0; i < 3; i++)
    {
        printf("\nValor a[%i]:%i",i,a[i]);
    }

    p = &a[0];
    *p = 100;
    p = &a[2];
    a[2] = 200;
    p = &a[1];
    *p = 300;

    for(int i = 0; i < 3; i++)
    {
        printf("\nValor a[%i]:%i",i,a[i]);
    }
    printf("\n------------");
    p = &a[0];
    for(int i = 0; i < 3; i++,p++)
    {
        printf("\nValor a[%i]:%i",i,*p);
    }

    printf("\n------------");
    p = &a[0];
    for(int i = 0; i < 3;i++,p++)
    {
        printf("\nDireccion a[%i]:%p",i,p);
    }
    return 0;
}
