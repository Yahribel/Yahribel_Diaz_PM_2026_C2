#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 256

typedef struct {
char nombre[50];
char apellido[50];
float promedio;
char materia[50];
}Alumno;

void extraer_valor(char *linea, char *etiqueta_apertura, char *etiqueta_cierre, char *destino)
{
    char *inicio = strstr(linea, etiqueta_apertura);
    char *fin = strstr(linea, etiqueta_cierre);

    if (inicio && fin) {
        inicio += strlen(etiqueta_apertura);
        int longitud = fin - inicio;
        strncpy(destino, inicio, longitud);
        destino[longitud] = '\0';
    }
}
int main()
{
    FILE *archivo = fopen("alumnos.xml", "r");
    if (archivo == NULL){
        printf("Error: No se pudo abrir el archivo  'alumnos.xml'\n");
        return 1;
    }
    char linea[MAX_LINEA];
    int n = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        if (strstr(linea, "<Alumno>")) {
            n++;
        }
    }

    printf("Se encontraros %d alumnos en el archivo XML\n", n);

    if (n == 0){
        printf("No hay elementos para cargar\n");
        fclose(archivo);
        return 0;
    }

    Alumno *listaAlumnos = (Alumno *) malloc(n * sizeof(Alumno));
    if (listaAlumnos == NULL) {
        printf("Error: No se pudo asignar memoria ram\n");
        fclose(archivo);
        return 1;
    }

    rewind(archivo);

    int i = -1;
    char temp_promedio[20];

    while (fgets(linea, sizeof(linea), archivo)) {
        if (strstr(linea, "<Alumno>")) {
            i++;
            continue;
        }

        if (i >= 0 && i < n) {
            if (strstr(linea, "<Nombre>")) {
                extraer_valor(linea, "<Nombre>", "</Nombre>", listaAlumnos[i].nombre);
            }
            else if (strstr(linea, "<Apellido>")) {
                extraer_valor(linea, "<Apellido>", "</Apellido>", listaAlumnos[i].apellido);
            }
            else if (strstr(linea, "<Materia>")){
                extraer_valor(linea, "<Materia>", "</Materia>", listaAlumnos[i].materia);

            }
            else if (strstr(linea, "<Promedio>")) {
                extraer_valor(linea, "<Promedio>", "</Promedio>", temp_promedio);
                listaAlumnos[i].promedio = atof(temp_promedio);

            }
        }
    }

    fclose(archivo);

    printf("\nALUMNOS CARGADOS EN MEMORIA DINAMICA\n");
    for (int j = 0; j < n; j++) {
        printf("Alumno [%d]: %s %s | Materia: %s | Promedio: %.1f\n",
               j + 1,
               listaAlumnos[j].nombre,
               listaAlumnos[j].apellido,
               listaAlumnos[j].materia,
               listaAlumnos[j].promedio);
    }

    free(listaAlumnos);
    printf("\nMemoria dinamica liberada correctamente\n");
    return 0;
}
