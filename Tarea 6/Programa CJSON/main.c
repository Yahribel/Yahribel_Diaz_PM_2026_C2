#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char nombre[50];
  char apellido[50];
  float promedio;
  char materia[50];
}Alumno;

int main()
{
    Alumno listaAlumnos[10] = {
    {"Yahribel", "Diaz", 10, "Matematicas"},
    {"Arianny", "Montero", 9.2, "Fisica"},
    {"Yelianny", "Hernandez", 9.6, "Quimica"},
    {"Neurianny", "Morillo", 8.5, "Historia"},
    {"Santa", "Fabian", 7.5, "Biologia"},
    {"Luis", "Encarnacion", 7.2, "Literatura"},
    {"Aneudy", "Lopez", 8.1, "Geografia"},
    {"Yaimely", "Reinoso", 9.4, "Ingles"},
    {"Rina", "Alvarez", 6.4, "Programacion"},
    {"Vanesa", "Rosario", 9.0, "Base de datos"}

    };

    FILE *archivo = fopen("alumnos.json", "w");
    if (archivo == NULL) {
        printf("Error al crear el archivo JSON.\n");
        return 1;
    }

    fprintf(archivo, "{}\n \"Alumno\":[\n");

    for (int i = 0; i < 10; i++) {
        fprintf(archivo, "    {\n");
        fprintf(archivo, "    \"Nombre\": \"%s\",\n", listaAlumnos[i].nombre);
        fprintf(archivo, "    \"Apellido\": \"%s\",\n", listaAlumnos[i].apellido);
        fprintf(archivo, "    \"Promedio\": %.1f,\n", listaAlumnos[i].promedio);
        fprintf(archivo, "    \"Materia\": \"%s\"\n", listaAlumnos[i].materia);

        if (i < 9) {
            fprintf(archivo, "    },\n");
        } else {
        fprintf(archivo, "    }\n");
        }
    }

    fprintf(archivo, "   ]\n}");

    fclose(archivo);
    printf("Archivo 'alumnos.json' creado\n");

    return 0;
}
