#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    int i, j, n;
    long mat;
    float cal;
    FILE *ar;

    printf("\nIngrese el numero de alumnos: ");
    scanf("%d", &n);
    while (getchar() != '\n');

    if ((ar = fopen("arc8.txt", "w")) != NULL)
    {
        fprintf(ar, "%d\n", n);

        for (i=0; i<n; i++)
        {
            printf("\nIngrese la matricula del alumno %d: ", i+1);
            scanf("%ld", &mat);
            while (getchar() != '\n');

            fprintf(ar,"%ld ", mat);

            for (j=0; j<5; j++)
            {
                printf("\nCalificacion %d: ", j+1);
                scanf("%f", &cal);
                while (getchar() != '\n');
                fprintf(ar, "%.2f ", cal);
            }
            fprintf(ar, "\n");
        }
        fclose(ar);
    }
    else
        printf("No se puede abrir el archivo");
}
