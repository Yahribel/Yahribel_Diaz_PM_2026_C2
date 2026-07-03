#include <stdio.h>
#include <stdlib.h>

typedef struct {

int clave;
int departamente;
float salario;
float ventas[12];
} empleado;

void main(void){
FILE *ar = fopen("ad5.dat", "wb");
if (ar != NULL) {
    empleado emp1 = {101, 1, 50000.0, {100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000}};
    fwrite(&emp1, sizeof(empleado), 1, ar);
    fclose(ar);

}
}
