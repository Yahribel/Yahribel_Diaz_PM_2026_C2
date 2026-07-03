#include <stdio.h>
#include <stdlib.h>

typedef struct{
char nombre[50];
char apellido[50];
float promedio;
char materia[50];
}Alumno;

int main()
{
    Alumno listaAlumnos[10] = {
    {"Juan", "Perez", 8.5, "Matematicas"},
    {"Maria", "Gomez", 9.2, "Fisica"},
    {"Carlos", "Rodriguez", 7.8, "Quimica"},
    {"Ana", "Martinez", 9.6, "Historia"},
    {"Luis", "Sanchez", 6.4, "Biologia"},
    {"Laura", "Fernandez", 8.9, "Literatura"},
    {"Pedro", "Lopez", 7.2, "Arte"},
    {"Rosio", "Alcantara", 8.7, "Base de datos"},
    {"Yanna", "Diaz", 9.0, "Programcaion"},
    {"Sofia", "Torres", 8.5, "Ingles"}
};

FILE *archivo = fopen("alumnos.cvs", "w");
if (archivo == NULL){
    printf("Error al crear el archivo CVS\n");
    return 1;
}

fprintf(archivo, "Nombre,Apellido,Promedio,Materia\n");

for (int i = 0; i < 10; i++){
    fprintf(archivo, "%s,%s,%.1f,%s\n",
            listaAlumnos[i].nombre,
            listaAlumnos[i].apellido,
            listaAlumnos[i].promedio,
            listaAlumnos[i].materia);
}

fclose(archivo);
printf("Archivo 'alumnos.cvs' creado\n");

return 0;

}
