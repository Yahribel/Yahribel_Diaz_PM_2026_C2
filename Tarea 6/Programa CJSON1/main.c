#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 256

typedef struct {
char nombre[50];
char apellido[50];
float promedio;
char materia[50];
} Alumno;

void extraer_valor_json(char *linea, char *clave, char *destino) {
char *pos_clave = strstr(linea, clave);
if (!pos_clave) return;

char *inicio_valor = pos_clave + strlen(clave);

while (*inicio_valor == ' ' || *inicio_valor == ':') {
    inicio_valor++;
}

if (*inicio_valor == '"') {
    inicio_valor++;

    int i = 0;
    while (*inicio_valor != '"' && *inicio_valor != '\0') {
        destino[i++] = *inicio_valor++;
    }
    destino[i] = '\0';

} else {
int i = 0;
while (*inicio_valor != ',' && *inicio_valor != '\n' && *inicio_valor != '\r' && *inicio_valor != ' ' && *inicio_valor != '\0'){

       destino[i++] = *inicio_valor++;
    }
    destino[i] = '\0';
  }
}

int main(){

    FILE *archivo = fopen("alumnos.json", "r");
    if (archivo == NULL){
        printf("Error: No se pudo abrir el abrir el archivo 'alumnos.json'\n");
        return 1;
    }

    char linea[MAX_LINEA];
    int n = 0;

    while (fgets(linea, sizeof(linea), archivo)){
        if (strstr(linea, "\"Nombre\"")){
            n++;
        }
    }

    printf("Se encontraron %d alumnos en el archivo JSON\n", n);

    if (n == 0) {
        printf("No hay elementos para cargar\n");
        fclose(archivo);
        return 0;
    }

    Alumno *listaAlumnos = (Alumno *) malloc(n * sizeof(Alumno));
    if (listaAlumnos == NULL){
            printf("Error: No se pudo asignar memoria RAM\n");
    fclose(archivo);
    return 1;
}

rewind(archivo);

int i = -1;
char temp_promedio[20];
while (fgets(linea, sizeof(linea), archivo)) {
    if (strstr(linea, "\"Nombre\"")){
        i++;
        if (i < n){
            extraer_valor_json(linea, "\"Nombre\"", listaAlumnos[i].nombre);

        }
    }

    else if (i >= 0 && i < n){
        if (strstr(linea, "\"Apellido\"")){
            extraer_valor_json(linea, "\"Apellido\"", listaAlumnos[1].apellido);

        }
        else if (strstr(linea, "\"Materia\"")){
            extraer_valor_json(linea, "\"Materia\"", listaAlumnos[i].materia);
        }
        else if (strstr(linea, "\"Promedio\"")){
            extraer_valor_json(linea, "\"Promedio\"", temp_promedio);
            listaAlumnos[i].promedio = atof(temp_promedio);
        }
    }
}

fclose(archivo);

printf("\nALUMNOS CARGADOS EN MEMORIA DINAMICA DESDE JSON\n");
for(int j = 0; j < n; j++){
    printf("Alumno [%d]: %s %s | Materia: %s | Promedio: %.1f\n",
           j + 1,
           listaAlumnos[j].nombre,
           listaAlumnos[j].apellido,
           listaAlumnos[j].materia,
           listaAlumnos[j].promedio);
}

free(listaAlumnos);
printf("\nMemoria dinamica liberada\n");

return 0;

}
