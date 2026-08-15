#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Para soporte UTF-8 en la consola de Windows

/* =========================================================================
 * 1. ESTRUCTURAS Y PROTOTIPOS
 * ========================================================================= */

typedef struct {
    int id;
    char nombre[64];
    char descripcion[128];

    // Fase 2: Criterios de Evaluación (Escala 1 a 5)
    int funcion;
    int sustitucion;
    int profundidad;
    int extension;
    int agresion;
    int vulnerabilidad;

    // Fase 3: Cálculos Mosler
    int importancia_impacto; // F * S
    int dimension_dano;      // P * E
    int caracter_riesgo;     // I + D
    int probabilidad_riesgo; // A * V
    int riesgo_estimado;     // C * Pb

    // Fase 4: Clasificación
    char clasificacion[16];
} Riesgo;

typedef struct {
    Riesgo *lista;
    size_t cantidad;
    size_t capacidad;
} SistemaRiesgos;

// Prototipos
SistemaRiesgos* crear_sistema(void);
void liberar_sistema(SistemaRiesgos *sys);
void agregar_riesgo(SistemaRiesgos *sys, Riesgo r);
void eliminar_riesgo(SistemaRiesgos *sys, size_t indice);
void calcular_mosler(Riesgo *r);

int guardar_json(const char *nombre_archivo, const SistemaRiesgos *sys);
int cargar_json(const char *nombre_archivo, SistemaRiesgos *sys);

void limpiar_buffer(void);
int leer_factor(const char *mensaje);
void mostrar_riesgos(const SistemaRiesgos *sys);
void solicitar_o_cambiar_archivo(char *archivo_actual, SistemaRiesgos *sys);


/* =========================================================================
 * 2. LÓGICA DEL MÉTODO MOSLER Y MEMORIA DINÁMICA
 * ========================================================================= */

SistemaRiesgos* crear_sistema(void) {
    SistemaRiesgos *sys = (SistemaRiesgos*) malloc(sizeof(SistemaRiesgos));
    if (!sys) return NULL;
    sys->capacidad = 4;
    sys->cantidad = 0;
    sys->lista = (Riesgo*) malloc(sys->capacidad * sizeof(Riesgo));
    return sys;
}

void liberar_sistema(SistemaRiesgos *sys) {
    if (sys) {
        if (sys->lista) free(sys->lista);
        free(sys);
    }
}

void calcular_mosler(Riesgo *r) {
    // Fase 3: Fórmulas matemáticas de Mosler
    r->importancia_impacto = r->funcion * r->sustitucion;
    r->dimension_dano = r->profundidad * r->extension;
    r->caracter_riesgo = r->importancia_impacto + r->dimension_dano;
    r->probabilidad_riesgo = r->agresion * r->vulnerabilidad;
    r->riesgo_estimado = r->caracter_riesgo * r->probabilidad_riesgo;

    // Fase 4: Clasificación del riesgo
    if (r->riesgo_estimado <= 250) {
        strcpy(r->clasificacion, "Muy bajo");
    } else if (r->riesgo_estimado <= 500) {
        strcpy(r->clasificacion, "Bajo");
    } else if (r->riesgo_estimado <= 750) {
        strcpy(r->clasificacion, "Normal");
    } else if (r->riesgo_estimado <= 1000) {
        strcpy(r->clasificacion, "Alto");
    } else {
        strcpy(r->clasificacion, "Muy alto");
    }
}

void agregar_riesgo(SistemaRiesgos *sys, Riesgo r) {
    if (sys->cantidad >= sys->capacidad) {
        sys->capacidad *= 2;
        Riesgo *temp = (Riesgo*) realloc(sys->lista, sys->capacidad * sizeof(Riesgo));
        if (!temp) return;
        sys->lista = temp;
    }
    calcular_mosler(&r);
    sys->lista[sys->cantidad++] = r;
}

void eliminar_riesgo(SistemaRiesgos *sys, size_t indice) {
    if (indice >= sys->cantidad) return;
    for (size_t i = indice; i < sys->cantidad - 1; i++) {
        sys->lista[i] = sys->lista[i + 1];
    }
    sys->cantidad--;
}


/* =========================================================================
 * 3. PERSISTENCIA Y CARGA DE ARCHIVOS JSON
 * ========================================================================= */

int guardar_json(const char *nombre_archivo, const SistemaRiesgos *sys) {
    FILE *f = fopen(nombre_archivo, "w");
    if (!f) return 0;

    fprintf(f, "{\n");
    fprintf(f, "  \"riesgos\": [\n");
    for (size_t i = 0; i < sys->cantidad; i++) {
        Riesgo *r = &sys->lista[i];
        fprintf(f, "    {\n");
        fprintf(f, "      \"id\": %d,\n", r->id);
        fprintf(f, "      \"nombre\": \"%s\",\n", r->nombre);
        fprintf(f, "      \"descripcion\": \"%s\",\n", r->descripcion);
        fprintf(f, "      \"funcion\": %d,\n", r->funcion);
        fprintf(f, "      \"sustitucion\": %d,\n", r->sustitucion);
        fprintf(f, "      \"profundidad\": %d,\n", r->profundidad);
        fprintf(f, "      \"extension\": %d,\n", r->extension);
        fprintf(f, "      \"agresion\": %d,\n", r->agresion);
        fprintf(f, "      \"vulnerabilidad\": %d,\n", r->vulnerabilidad);
        fprintf(f, "      \"importancia_impacto\": %d,\n", r->importancia_impacto);
        fprintf(f, "      \"dimension_dano\": %d,\n", r->dimension_dano);
        fprintf(f, "      \"caracter_riesgo\": %d,\n", r->caracter_riesgo);
        fprintf(f, "      \"probabilidad_riesgo\": %d,\n", r->probabilidad_riesgo);
        fprintf(f, "      \"riesgo_estimado\": %d,\n", r->riesgo_estimado);
        fprintf(f, "      \"clasificacion\": \"%s\"\n", r->clasificacion);
        fprintf(f, "    }%s\n", (i == sys->cantidad - 1) ? "" : ",");
    }
    fprintf(f, "  ]\n");
    fprintf(f, "}\n");

    fclose(f);
    return 1;
}

int cargar_json(const char *nombre_archivo, SistemaRiesgos *sys) {
    FILE *f = fopen(nombre_archivo, "r");
    if (!f) return 0;

    sys->cantidad = 0;

    char linea[256];
    Riesgo r_temp;
    memset(&r_temp, 0, sizeof(Riesgo));
    int en_objeto = 0;

    while (fgets(linea, sizeof(linea), f)) {
        if (strchr(linea, '{') && !strstr(linea, "{\n") && !strstr(linea, "{")) {
            continue;
        }

        if (strchr(linea, '{')) {
            en_objeto = 1;
            memset(&r_temp, 0, sizeof(Riesgo));
        } else if (strchr(linea, '}')) {
            if (en_objeto) {
                if (r_temp.id > 0) {
                    agregar_riesgo(sys, r_temp);
                }
                en_objeto = 0;
            }
        } else if (en_objeto) {
            sscanf(linea, " \"id\": %d", &r_temp.id);
            sscanf(linea, " \"nombre\": \"%63[^\"]\"", r_temp.nombre);
            sscanf(linea, " \"descripcion\": \"%127[^\"]\"", r_temp.descripcion);
            sscanf(linea, " \"funcion\": %d", &r_temp.funcion);
            sscanf(linea, " \"sustitucion\": %d", &r_temp.sustitucion);
            sscanf(linea, " \"profundidad\": %d", &r_temp.profundidad);
            sscanf(linea, " \"extension\": %d", &r_temp.extension);
            sscanf(linea, " \"agresion\": %d", &r_temp.agresion);
            sscanf(linea, " \"vulnerabilidad\": %d", &r_temp.vulnerabilidad);
        }
    }

    fclose(f);
    return 1;
}


/* =========================================================================
 * 4. FUNCIONES DE AUXILIO E INTERFAZ DE USUARIO
 * ========================================================================= */

void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leer_factor(const char *mensaje) {
    int val;
    do {
        printf("%s (1-5): ", mensaje);
        if (scanf("%d", &val) != 1) {
            limpiar_buffer();
            val = 0;
        }
    } while (val < 1 || val > 5);
    return val;
}

void mostrar_riesgos(const SistemaRiesgos *sys) {
    printf("\n=========================================================================================\n");
    printf("%-4s | %-4s | %-15s | %-6s | %-7s | %-9s | %-10s\n",
           "No.", "ID", "Nombre", "C", "Pb", "Riesgo ER", "Clasificacion");
    printf("=========================================================================================\n");
    for (size_t i = 0; i < sys->cantidad; i++) {
        Riesgo *r = &sys->lista[i];
        printf("%-4zu | %-4d | %-15.15s | %-6d | %-7d | %-9d | %-10s\n",
               i + 1, r->id, r->nombre, r->caracter_riesgo, r->probabilidad_riesgo, r->riesgo_estimado, r->clasificacion);
    }
    printf("=========================================================================================\n");
}

void solicitar_o_cambiar_archivo(char *archivo_actual, SistemaRiesgos *sys) {
    printf("\nIngrese el nombre del archivo de la empresa (ej. empresa_a.json o prueba.json): ");
    fgets(archivo_actual, 128, stdin);
    archivo_actual[strcspn(archivo_actual, "\n")] = 0;

    // Asegurar extension .json si el usuario solo escribe el nombre
    if (!strstr(archivo_actual, ".json")) {
        strcat(archivo_actual, ".json");
    }

    // Intentar cargar datos si el archivo existe
    if (cargar_json(archivo_actual, sys)) {
        printf("--> Archivo existente detectado. Se cargaron %zu riesgo(s) previamente guardados.\n", sys->cantidad);
    } else {
        sys->cantidad = 0; // Iniciar lista limpia para el nuevo archivo
        printf("--> El archivo [%s] es nuevo. Se guardaran los datos en el al agregar riesgos.\n", archivo_actual);
        guardar_json(archivo_actual, sys); // Crea el archivo vacio en disco
    }
}


/* =========================================================================
 * 5. PROGRAMA PRINCIPAL (MAIN)
 * ========================================================================= */

int main(void) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    SistemaRiesgos *sys = crear_sistema();
    if (!sys) {
        printf("Error: No se pudo asignar memoria inicial.\n");
        return 1;
    }

    char archivo_actual[128] = "";

    printf("=========================================================\n");
    printf("   SISTEMA DE EVALUACIÓN DE RIESGOS (MÉTODO MOSLER)   \n");
    printf("=========================================================\n");

    // PASO INICIAL OBLIGATORIO: Seleccionar o crear el archivo de trabajo
    solicitar_o_cambiar_archivo(archivo_actual, sys);

    int opcion;
    do {
        printf("\n=========================================================\n");
        printf("Archivo Activo: [%s] | Riesgos Guardados: %zu\n", archivo_actual, sys->cantidad);
        printf("=========================================================\n");
        printf("1. Crear Riesgo (Fase 1 y 2)\n");
        printf("2. Modificar parametros de un riesgo\n");
        printf("3. Recalcular todos los riesgos (Fase 3 y 4)\n");
        printf("4. Imprimir tabla de riesgos completa\n");
        printf("5. Borrar un riesgo\n");
        printf("6. Cambiar / Seleccionar otro archivo de empresa\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            limpiar_buffer();
            continue;
        }
        limpiar_buffer();

        switch (opcion) {
            case 1: {
                Riesgo nuevo;
                printf("\n-- FASE 1: Definicion de Riesgo --\n");
                printf("ID del riesgo (numerico, ej. 1): ");
                scanf("%d", &nuevo.id);
                limpiar_buffer();

                printf("Nombre del riesgo: ");
                fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
                nuevo.nombre[strcspn(nuevo.nombre, "\n")] = 0;

                printf("Descripcion del riesgo: ");
                fgets(nuevo.descripcion, sizeof(nuevo.descripcion), stdin);
                nuevo.descripcion[strcspn(nuevo.descripcion, "\n")] = 0;

                printf("\n-- FASE 2: Valoracion de Criterios --\n");
                nuevo.funcion = leer_factor("Funcion");
                nuevo.sustitucion = leer_factor("Sustitucion");
                nuevo.profundidad = leer_factor("Profundidad");
                nuevo.extension = leer_factor("Extension");
                nuevo.agresion = leer_factor("Agresion");
                nuevo.vulnerabilidad = leer_factor("Vulnerabilidad");

                agregar_riesgo(sys, nuevo);
                guardar_json(archivo_actual, sys); // Guardado automatico
                printf("\n--> Riesgo creado, evaluado y guardado automaticamente en [%s].\n", archivo_actual);
                break;
            }
            case 2: {
                if (sys->cantidad == 0) {
                    printf("\nNo hay riesgos guardados para modificar.\n");
                    break;
                }
                mostrar_riesgos(sys);
                size_t idx;
                printf("Ingrese el numero de registro a modificar (1-%zu): ", sys->cantidad);
                if (scanf("%zu", &idx) != 1) {
                    limpiar_buffer();
                    break;
                }
                limpiar_buffer();

                if (idx < 1 || idx > sys->cantidad) {
                    printf("Numero invalido.\n");
                    break;
                }

                Riesgo *r = &sys->lista[idx - 1];
                printf("\nNuevos factores para [ID: %d - %s]:\n", r->id, r->nombre);
                r->funcion = leer_factor("Funcion");
                r->sustitucion = leer_factor("Sustitucion");
                r->profundidad = leer_factor("Profundidad");
                r->extension = leer_factor("Extension");
                r->agresion = leer_factor("Agresion");
                r->vulnerabilidad = leer_factor("Vulnerabilidad");

                calcular_mosler(r);
                guardar_json(archivo_actual, sys); // Guardado automatico
                printf("\n--> Riesgo actualizado y guardado automaticamente en [%s].\n", archivo_actual);
                break;
            }
            case 3: {
                for (size_t i = 0; i < sys->cantidad; i++) {
                    calcular_mosler(&sys->lista[i]);
                }
                guardar_json(archivo_actual, sys); // Guardado automatico
                printf("\n--> Todos los riesgos han sido recalculados y guardados en [%s].\n", archivo_actual);
                break;
            }
            case 4:
                if (sys->cantidad == 0) {
                    printf("\nEl archivo [%s] no contiene riesgos guardados.\n", archivo_actual);
                } else {
                    mostrar_riesgos(sys);
                }
                break;
            case 5: {
                if (sys->cantidad == 0) {
                    printf("\nNo hay riesgos para borrar.\n");
                    break;
                }
                mostrar_riesgos(sys);
                size_t idx;
                printf("Ingrese el numero de registro a borrar (1-%zu): ", sys->cantidad);
                if (scanf("%zu", &idx) != 1) {
                    limpiar_buffer();
                    break;
                }
                limpiar_buffer();

                if (idx >= 1 && idx <= sys->cantidad) {
                    eliminar_riesgo(sys, idx - 1);
                    guardar_json(archivo_actual, sys); // Guardado automatico
                    printf("\n--> Riesgo eliminado y cambios guardados en [%s].\n", archivo_actual);
                } else {
                    printf("Numero invalido.\n");
                }
                break;
            }
            case 6:
                solicitar_o_cambiar_archivo(archivo_actual, sys);
                break;
            case 7:
                printf("\nSaliendo del programa...\n");
                break;
            default:
                printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 7);

    liberar_sistema(sys);
    return 0;
}
