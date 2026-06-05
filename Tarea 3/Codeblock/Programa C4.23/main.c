#include <stdio.h>
#include <stdlib.h>

void trueque(int *x, int *y)
{
    int tem;
    tem = *x;
    *x = *y;
    *y = tem;
}

int suma(int x)
{
    return (x + x);
}
/*Determina cuales de las siguientes llamadas a las funciones son correctas si x, y y z son variables de tipo entero

1. trueque(suma (&x), &x);
2. trueque(3, 4);
3. suma(10);
4. y = suma(10);
5. z = trueque(&x, &y);
6. trueque(&x, &x);

Las llamada correctas son: 3, 4 y 6, porque respetan lo que cada funcion pide (suma) recibe un valor comun(y en la 4 se
guarda el resultado), mientras que trueque recibe direcciones de memoria(&).*/
