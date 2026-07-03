#include <stdio.h>
#include <stdlib.h>

void promedio(FILE *);

void main(void)
{
    FILE *ar;
    if ((ar = fopen("arc8.txt", "r")) != NULL)
    {
        promedio(ar);
        fclose(ar);
    }
    else
        printf("No se puede abrir el archivo");
}

void promedio(FILE *ar1)
{
    int i, j, n;
    long mat;
    float pro, cal;
    fscanf(ar1, "%d", &n);

    for (i=0; i<n; i++)
    {
        fscanf(ar1, "%ld", &mat);
        printf("%ld\t", mat);
        pro = 0;

        for(j=0; j<5; j++)
        {
          fscanf(ar1, "%f", &cal);
          pro += cal;
        }
          printf("\t %.2f", pro / 5);
          printf("\n");
    }
}
