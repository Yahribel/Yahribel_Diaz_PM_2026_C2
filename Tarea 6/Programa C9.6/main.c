#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    int i, j, n;
    long mat;
    float cal, pro;
    FILE *ar;
    if ((ar = fopen("arc8.txt", "r")) != NULL)
    {
        fscanf(ar, "%d", &n);
        for (i=0; i<n; i++)
        {
            fscanf(ar, "%ld", &mat);
            pro = 0;
            for (j=0; j<5; j++)
            {
                fscanf(ar, "%f", &cal);
                pro += cal;
            }
            printf("Alumno Matricula %ld  Promedio: %.2f\n", mat, pro / 5);
            printf("\n");
        }
        fclose(ar);
    }
    else
        printf("No se puede abrir el archivo");
}
