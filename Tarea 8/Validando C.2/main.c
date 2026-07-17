#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_ARCHIVOS 100
#define MAX_LONGITUD_NOMBRE 256

typedef enum {
FORMATO_DESCONOCIDO = 0,
FORMATO_PNG,
FORMATO_JPG,
FORMATO_BMP
}FormatoImagen;

FormatoImagen obtener_formato_por_extension(const char *nombre){
const char *ext = strrchr(nombre, '.');
if (!ext) return FORMATO_DESCONOCIDO;

if (strcasecmp(ext, ".png") == 0) return FORMATO_PNG;
if (strcasecmp(ext, ".jpg") == 0) return FORMATO_JPG;
if (strcasecmp(ext, ".bmp") == 0) return FORMATO_BMP;

return FORMATO_DESCONOCIDO;
}

int es_extension_soportada(const char *nombre) {
return obtener_formato_por_extension(nombre) != FORMATO_DESCONOCIDO;
}

int validar_contenido_archivo(const char *ruta_archivo, FormatoImagen formato_esperado){
FILE *archivo = fopen(ruta_archivo, "rb");
if (archivo == NULL){
    printf("No se puede abrir el archivo\n");
    return 0;
}

unsigned char encabezado[8];
size_t bytes_leidos = fread(encabezado, 1, 8, archivo);
fclose(archivo);

if (bytes_leidos < 2) {
    return 0;
}

switch (formato_esperado) {
case FORMATO_PNG:

    if (bytes_leidos >= 8 &&
        encabezado[0] == 0x89 && encabezado[1] == 0x50 &&
        encabezado[2] == 0x4E && encabezado[3] == 0x47 &&
        encabezado[4] == 0x0D && encabezado[5] == 0x0A &&
        encabezado[6] == 0x1A && encabezado[7] == 0x0A){
            return 1;
        }
        break;

        case FORMATO_JPG:

        if (bytes_leidos >= 3 &&
            encabezado[0] == 0xFF && encabezado[1] == 0xD8 && encabezado[2] == 0xFF){
              return 1;
            }
            break;

        case FORMATO_BMP:

        if (bytes_leidos >= 2 &&
        encabezado[0] == 0x42 && encabezado[1] == 0x4D){
        return 1;
        }
        break;

        default:
            break;
}
return 0;
}


int main()
{
DIR *dir;
struct dirent *entrada;
char lista_archivo[MAX_ARCHIVOS][MAX_LONGITUD_NOMBRE];
int total_archivos = 0;

dir = opendir(".");
if (dir == NULL) {
    printf("No se pudo abrir la carpeta\n");
    return 1;
}

while ((entrada = readdir(dir)) != NULL) {
    if (es_extension_soportada(entrada->d_name)) {
        strncpy(lista_archivo[total_archivos], entrada->d_name, MAX_LONGITUD_NOMBRE - 1);
        lista_archivo[total_archivos][MAX_LONGITUD_NOMBRE - 1] = '\0';
        total_archivos++;
        if (total_archivos >= MAX_ARCHIVOS) break;
    }
}

closedir(dir);

if (total_archivos == 0){
    printf("No se encuentarn archivos con extensiones de imagen (.png, .jpg, .bmp) en la carpeta\n");
    return 0;
}

printf("Validar el contenido de las imagenes\n");
for(int i = 0; i < total_archivos; i++){
    printf("%d. %s\n", i + 1, lista_archivo[i]);

}

int seleccion;
printf("\nSelecciona el archivo para verificar su contendio real (1-%d): ", total_archivos);
if (scanf("%d", &seleccion) != 1 || seleccion < 1 || seleccion > total_archivos){
    printf("Seleccion invalida\n");
    return 1;

}
char *archivo_seleccionado = lista_archivo[seleccion - 1];
FormatoImagen formato_esperado = obtener_formato_por_extension(archivo_seleccionado);

printf("\nArchivo seleccionado: %s\n", archivo_seleccionado);
printf("Extension detectada: ");
if (formato_esperado == FORMATO_PNG) printf("PNG\n");
else if(formato_esperado == FORMATO_JPG) printf("JPG\n");
else if(formato_esperado == FORMATO_BMP) printf("BMP\n");

    printf("Analizando estructura interna de bytes...\n");

    int es_valido = validar_contenido_archivo(archivo_seleccionado, formato_esperado);

    printf("\n RESULTADO \n");
    if (es_valido){
        printf("Valido\n");
        printf("El contenido del archivo coincide con su extension\n");
    } else {
    printf("Archivo falso\n");
    printf("El archivo tiene extension de imagen, pero sus bytes internos no corresponden a ese formato\n");
    }
    return 0;
}
