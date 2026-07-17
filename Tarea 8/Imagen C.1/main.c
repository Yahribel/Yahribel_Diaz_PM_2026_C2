#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAX_ARCHIVOS 100
#define MAX_LONGITUD_NOMBRE 256

int es_valida(const char *nombre){
const char *ext = strrchr(nombre, '.');
if (!ext)return 0;

if (strcasecmp(ext, ".png") == 0 ||
    strcasecmp(ext, ".jpg") == 0 ||
    strcasecmp(ext, ".bmp") == 0){
        return 1;
    }
    return 0;
}

int main()
{
    DIR *dir;
    struct dirent *entrada;
    char lista_archivos[MAX_ARCHIVOS][MAX_LONGITUD_NOMBRE];
    int total_archivos = 0;

    dir = opendir(".");
    if (dir == NULL) {
        printf("No se puedo abrir la carpeta.\n");
        return 1;
    }

    printf("Escaneando archivos de imagen en la carpeta\n");
    while ((entrada = readdir(dir)) != NULL){
        if (es_valida(entrada->d_name)){
            strncpy(lista_archivos[total_archivos], entrada->d_name, MAX_LONGITUD_NOMBRE - 1);
            lista_archivos[total_archivos][MAX_LONGITUD_NOMBRE - 1] = '\0';
            total_archivos++;
            if (total_archivos >= MAX_ARCHIVOS) break;

        }
    }
    closedir(dir);

    if (total_archivos == 0) {
        printf("No se encontraron imagenes (.png, .jpg, .bmp) en esta carpeta\n");
        return 0;
    }

    printf("\nIMAGENES DISPONIBLES\n");
    for(int i = 0; i < total_archivos; i++){
        printf("%d, %s\n", i + 1, lista_archivos[i]);
    }

    int seleccion;
    printf("\nSelecciona el numero de la imagen a convertir (1-%d): ", total_archivos);
    if (scanf("%d", &seleccion) != 1 || seleccion < 1 || seleccion > total_archivos){
        printf("Seleccion invalida\n");
        return 1;
    }

    char *archivo_entrada = lista_archivos[seleccion - 1];
    printf("\nProcesando: %s...\n", archivo_entrada);

    int ancho, alto, canales;

    unsigned char *pixeles = stbi_load(archivo_entrada, &ancho, &alto, &canales, 3);
    if (pixeles == NULL) {
        printf("No se puedo cargar la imagen\n");
        return 1;
    }

    printf("Dimensiones: %d x %d pixeles | canales originales: %d\n", ancho, alto, canales);

    int total_pixeles = ancho * alto;
    for(int i = 0; i < total_pixeles; i++){

        int indice = i * 3;
        unsigned char r = pixeles[indice];
        unsigned char g = pixeles[indice + 1];
        unsigned char b = pixeles[indice + 2];

        unsigned char gris = (unsigned char)(0.299f * r + 0.587f * g + 0.114f * b);

        pixeles[indice]     = gris;
        pixeles[indice + 1] = gris;
        pixeles[indice + 2] = gris;
    }

    char archivo_salida[MAX_LONGITUD_NOMBRE + 10];
    snprintf(archivo_salida, sizeof(archivo_salida), "bn_%s", archivo_entrada);

    int resultado = stbi_write_png(archivo_salida, ancho, alto, 3, pixeles, ancho * 3);

    stbi_image_free(pixeles);

    if(resultado) {
        printf("\nSe guardo imagen en blanco y negro como: %s\n", archivo_salida);
    } else {
    printf("\nNo se pudo guardar a imagen\n");
    }

    return 0;
}
