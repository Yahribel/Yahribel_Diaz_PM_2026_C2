#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 256

typedef struct{
char nombre[50];
char apellido[50];
float promedio;
char materia[50];
}Alumno;

int main()
{
    FILE *archivo = fopen("alumnos.cvs", "r");
    if (archivo == NULL) {
        printf("Error: No se puedo abrir el archivo 'alumnos.cvs\n");
        return 1;
    }

    char linea[MAX_LINEA];
    int n = 0;

    if (fgets(linea, sizeof(linea), archivo) == NULL){
        printf("El archivo esta vacio\n");
        fclose(archivo);
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo)){
        if (strlen(linea) > 5){
            n++;
        }
    }

    printf("Se encontraros %d alumnos en el archivo CVS\n", n);

    if (n == 0){
        printf("No hay elementos para cargar\n");
        fclose(archivo);
        return 0;
    }
Alumno *listaAlumnos = (Alumno *)malloc(n * sizeof(Alumno));
if (listaAlumnos == NULL){
    printf("Error: No se pudo asignar mamoria RAM\n");
    fclose(archivo);
    return 1;
}

rewind(archivo);

fgets(linea, sizeof(linea), archivo);

int i = 0;
while (fgets(linea, sizeof(linea), archivo) && i < n){
    if (strlen(linea) <= 5) continue;

    scanf(linea, "%[^,],%[^,],%f,%[^,\n\r]",
          listaAlumnos[i].nombre,
          listaAlumnos[i].apellido,
          &listaAlumnos[i].promedio,
          listaAlumnos[i].materia);

          i++;
}

fclose(archivo);

printf("\nALUMNOS CARGADOS EN MEMORIA DINAMICA DESDE CVS\n");
for(int j = 0; j < n; j++){
    printf("Alumno [%d]: %s %s | Materia: %s | Promedio: %.1f\n",
           j + 1,
           listaAlumnos[j].nombre,
           listaAlumnos[j].apellido,
           listaAlumnos[j].materia,
           listaAlumnos[j].promedio);
}

free(listaAlumnos);
printf("\nMemoria dinamina liberada\n");

return 0;

}

