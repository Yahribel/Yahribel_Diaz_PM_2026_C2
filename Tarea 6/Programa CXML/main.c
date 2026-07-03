#include <stdio.h>
#include <stdlib.h>

typedef struct {
char nombre[50];
char apellido[50];
float promedio;
char materia[50];
} Alumno;

int main()
{
    Alumno listaAlumnos[10] = {
    {"Juan", "Perez", 8.5, "Matematicas"},
    {"Maria", "Gomez", 9.2, "Fisica"},
    {"Carlos", "Diaz", 7.8, "Quimica"},
    {"Ana", "Matinez", 9.6, "Historia"},
    {"Luis", "Sanchez", 6.4, "Biologia"},
    {"Pedro", "Lopez", 7.2, "Base de datos"},
    {"Laura", "Fernandez", 8.9, "Programacion"},
    {"Elena", "Hernandez", 8.1, "Arte"},
    {"Jorge", "Alvarez", 6.5, "Ingles"},
    {"Sofia", "Torres", 9.5, "Geografia"}
};

FILE *archivo = fopen("alumnos.xml", "w");
if (archivo == NULL) {
    printf("Error al crear el archivo XML\n");
    return 1;
}

fprintf(archivo, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
fprintf(archivo, "<Alumnos>\n");

for (int i = 0; i < 10; i++) {
    fprintf(archivo, "    <Alumno>\n");
    fprintf(archivo, "      <Nombre>%s</Nombre>\n", listaAlumnos[i].nombre);
    fprintf(archivo, "      <Apellido>%s</Apellido>\n", listaAlumnos[i].apellido);
    fprintf(archivo, "      <Promedio>%.1f</Promedio>\n", listaAlumnos[i].promedio);
    fprintf(archivo, "      <Materia>%s</Materia>\n", listaAlumnos[i].materia);
    fprintf(archivo, "    </Alumno>\n");
}

fprintf(archivo, "</Alumnos>\n");

fclose(archivo);
printf("Archivo 'alumnos.xml' creado\n");
return 0;
}
