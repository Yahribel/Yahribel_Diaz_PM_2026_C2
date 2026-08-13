#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO_DATOS "vehiculos.dat"

// Estructura para almacenar los datos del vehículo
typedef struct {
    int id;
    char nombre[50];
    double precio_compra;          // En RD$
    double vida_util_anos;         // En años
    double km_totales_vida_util;   // En km
    double rendimiento_ciudad;     // En km/galón
    double rendimiento_autopista;  // En km/galón
    double seguro_anual;           // En RD$
    double costo_mantenimiento;    // En RD$ (estimado vida útil)
    double costo_neumaticos;       // En RD$ (juego completo)
    double duracion_neumaticos;    // En km
} Vehiculo;

// Variables globales para la gestión dinámica
Vehiculo *lista_vehiculos = NULL;
int total_vehiculos = 0;
double precio_combustible_galon = 274.00; // Precio por galón en RD$

// Prototipos de funciones
void cargar_datos();
void guardar_datos();
void agregar_vehiculo();
void mostrar_vehiculos();
void modificar_vehiculo();
void eliminar_vehiculo();
void cambiar_precio_combustible();
void calcular_costo_viaje();

int main() {
    cargar_datos();
    int opcion;

    do {

        printf("==================================================\n");
        printf("   SISTEMA DE GESTION Y COSTOS DE VEHICULOS (C)   \n");
        printf("==================================================\n");
        printf(" Precio actual combustible: RD$ %.2f / galon\n", precio_combustible_galon);
        printf(" Vehiculos en sistema: %d\n", total_vehiculos);
        printf("--------------------------------------------------\n");
        printf(" 1. Registrar nuevo vehiculo\n");
        printf(" 2. Mostrar vehiculos registrados\n");
        printf(" 3. Modificar vehiculo\n");
        printf(" 4. Eliminar vehiculo\n");
        printf(" 5. Configurar precio global del combustible (RD$/gal)\n");
        printf(" 6. Simular y calcular costo real de viaje\n");
        printf(" 7. Guardar y salir\n");
        printf("--------------------------------------------------\n");
        printf(" Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el búfer

        switch (opcion) {
            case 1: agregar_vehiculo(); break;
            case 2: mostrar_vehiculos(); break;
            case 3: modificar_vehiculo(); break;
            case 4: eliminar_vehiculo(); break;
            case 5: cambiar_precio_combustible(); break;
            case 6: calcular_costo_viaje(); break;
            case 7:
                guardar_datos();
                printf("\n[EXITO] Datos guardados correctamente. ¡Hasta luego!\n");
                break;
            default:
                printf("\n[ERROR] Opcion no valida.\n");

        }
    } while (opcion != 7);

    // Liberar memoria dinámica al salir
    free(lista_vehiculos);
    return 0;
}

// Carga los vehículos guardados en el archivo binario
void cargar_datos() {
    FILE *f = fopen(ARCHIVO_DATOS, "rb");
    if (!f) return;

    fread(&precio_combustible_galon, sizeof(double), 1, f);
    fread(&total_vehiculos, sizeof(int), 1, f);

    if (total_vehiculos > 0) {
        lista_vehiculos = (Vehiculo *)malloc(total_vehiculos * sizeof(Vehiculo));
        fread(lista_vehiculos, sizeof(Vehiculo), total_vehiculos, f);
    }
    fclose(f);
}

// Guarda los vehículos en el archivo binario
void guardar_datos() {
    FILE *f = fopen(ARCHIVO_DATOS, "wb");
    if (!f) {
        printf("\n[ERROR] No se pudo abrir el archivo para guardar datos.\n");
        return;
    }
    fwrite(&precio_combustible_galon, sizeof(double), 1, f);
    fwrite(&total_vehiculos, sizeof(int), 1, f);
    if (total_vehiculos > 0) {
        fwrite(lista_vehiculos, sizeof(Vehiculo), total_vehiculos, f);
    }
    fclose(f);
}

// Agrega un nuevo vehículo usando memoria dinámica con realloc
void agregar_vehiculo() {

    printf("=== REGISTRAR NUEVO VEHICULO ===\n\n");

    lista_vehiculos = (Vehiculo *)realloc(lista_vehiculos, (total_vehiculos + 1) * sizeof(Vehiculo));
    Vehiculo *v = &lista_vehiculos[total_vehiculos];

    v->id = total_vehiculos + 1;

    printf("Nombre / Modelo del vehiculo: ");
    fgets(v->nombre, sizeof(v->nombre), stdin);
    v->nombre[strcspn(v->nombre, "\n")] = 0; // Quitar salto de línea

    printf("Precio de compra (RD$): ");
    scanf("%lf", &v->precio_compra);

    printf("Vida util estimada (en anos): ");
    scanf("%lf", &v->vida_util_anos);

    printf("Kilometros totales proyectados de vida util: ");
    scanf("%lf", &v->km_totales_vida_util);

    printf("Rendimiento en ciudad (km/galon): ");
    scanf("%lf", &v->rendimiento_ciudad);

    printf("Rendimiento en autopista (km/galon): ");
    scanf("%lf", &v->rendimiento_autopista);

    printf("Seguro anual de ley (RD$): ");
    scanf("%lf", &v->seguro_anual);

    printf("Mantenimiento total estimado durante vida util (RD$): ");
    scanf("%lf", &v->costo_mantenimiento);

    printf("Costo juego de neumaticos (RD$): ");
    scanf("%lf", &v->costo_neumaticos);

    printf("Duracion estimada del juego de neumaticos (km): ");
    scanf("%lf", &v->duracion_neumaticos);

    total_vehiculos++;
    printf("\n[EXITO] Vehiculo '%s' registrado con ID %d.\n", v->nombre, v->id);

}

// Muestra la lista de vehículos registrados
void mostrar_vehiculos() {

    printf("=== LISTA DE VEHICULOS REGISTRADOS ===\n\n");
    if (total_vehiculos == 0) {
        printf("No hay vehiculos registrados en el sistema.\n");
        return;
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("%-4s | %-22s | %-12s | %-12s | %-12s | %-12s\n", "ID", "Nombre", "Precio (RD$)", "R.Ciudad", "R.Autop.", "Seguro Anual");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < total_vehiculos; i++) {
        printf("%-4d | %-22s | RD$ %-9.2f | %-7.2f km/g | %-7.2f km/g | RD$ %-8.2f\n",
               lista_vehiculos[i].id,
               lista_vehiculos[i].nombre,
               lista_vehiculos[i].precio_compra,
               lista_vehiculos[i].rendimiento_ciudad,
               lista_vehiculos[i].rendimiento_autopista,
               lista_vehiculos[i].seguro_anual);
    }
    printf("----------------------------------------------------------------------------------------------------\n");
}

// Permite modificar los datos de un vehículo
void modificar_vehiculo() {

    if (total_vehiculos == 0) { return; }

    int id;
    printf("\nIngrese el ID del vehiculo a modificar: ");
    scanf("%d", &id);

    if (id < 1 || id > total_vehiculos) {
        printf("\n[ERROR] ID de vehiculo no valido.\n");

        return;
    }

    Vehiculo *v = &lista_vehiculos[id - 1];
    getchar();

    printf("\nNuevo nombre (%s): ", v->nombre);
    char buffer[50];
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(v->nombre, buffer);
    }

    printf("Nuevo precio de compra (Actual: RD$ %.2f): ", v->precio_compra);
    scanf("%lf", &v->precio_compra);

    printf("Nuevo rendimiento en ciudad en km/gal (Actual: %.2f): ", v->rendimiento_ciudad);
    scanf("%lf", &v->rendimiento_ciudad);

    printf("Nuevo rendimiento en autopista en km/gal (Actual: %.2f): ", v->rendimiento_autopista);
    scanf("%lf", &v->rendimiento_autopista);

    printf("\n[EXITO] Datos del vehiculo actualizados.\n");

}

// Elimina un vehículo y reorganiza el arreglo dinámico
void eliminar_vehiculo() {
    mostrar_vehiculos();
    if (total_vehiculos == 0) { return; }

    int id;
    printf("\nIngrese el ID del vehiculo a eliminar: ");
    scanf("%d", &id);

    if (id < 1 || id > total_vehiculos) {
        printf("\n[ERROR] ID invalido.\n");

        return;
    }

    for (int i = id - 1; i < total_vehiculos - 1; i++) {
        lista_vehiculos[i] = lista_vehiculos[i + 1];
        lista_vehiculos[i].id = i + 1; // Reasignar ID correlativo
    }

    total_vehiculos--;
    if (total_vehiculos > 0) {
        lista_vehiculos = (Vehiculo *)realloc(lista_vehiculos, total_vehiculos * sizeof(Vehiculo));
    } else {
        free(lista_vehiculos);
        lista_vehiculos = NULL;
    }

    printf("\n[EXITO] Vehiculo eliminado del sistema.\n");

}

// Cambia la tarifa global por galón
void cambiar_precio_combustible() {

    printf("=== CONFIGURAR PRECIO DEL COMBUSTIBLE ===\n\n");
    printf("Precio actual: RD$ %.2f por galon\n", precio_combustible_galon);
    printf("Ingrese el nuevo precio por galon (RD$): ");
    scanf("%lf", &precio_combustible_galon);
    printf("\n[EXITO] Precio actualizado globalmente a RD$ %.2f por galon.\n", precio_combustible_galon);

}

// Función principal de simulación y cálculo de costos de viaje
void calcular_costo_viaje() {
    mostrar_vehiculos();
    if (total_vehiculos == 0) { return; }

    int id;
    printf("\nSeleccione el ID del vehiculo a utilizar: ");
    scanf("%d", &id);

    if (id < 1 || id > total_vehiculos) {
        printf("\n[ERROR] ID invalido.\n");

        return;
    }

    Vehiculo v = lista_vehiculos[id - 1];

    double km_ciudad, km_autopista;
    printf("\nKilometros a recorrer en CIUDAD: ");
    scanf("%lf", &km_ciudad);
    printf("Kilometros a recorrer en AUTOPISTA: ");
    scanf("%lf", &km_autopista);

    double km_totales = km_ciudad + km_autopista;
    if (km_totales <= 0) {
        printf("\n[ERROR] La distancia total debe ser mayor a 0 km.\n");

        return;
    }

    // 1. Cálculo de Combustible (en Galones y RD$)
    double galones_ciudad = km_ciudad / v.rendimiento_ciudad;
    double galones_autopista = km_autopista / v.rendimiento_autopista;
    double galones_totales = galones_ciudad + galones_autopista;

    double costo_comb_ciudad = galones_ciudad * precio_combustible_galon;
    double costo_comb_autopista = galones_autopista * precio_combustible_galon;
    double costo_combustible_total = costo_comb_ciudad + costo_comb_autopista;

    // 2. Cálculo de Costos Fijos y Desgaste por Kilómetro
    double tasa_amortizacion_km = v.precio_compra / v.km_totales_vida_util;
    double tasa_mantenimiento_km = v.costo_mantenimiento / v.km_totales_vida_util;
    double tasa_neumaticos_km = v.costo_neumaticos / v.duracion_neumaticos;
    double seguro_total_vida_util = v.seguro_anual * v.vida_util_anos;
    double tasa_seguro_km = seguro_total_vida_util / v.km_totales_vida_util;

    // 3. Proporcional de Desgaste para el Viaje Especificado
    double costo_amortizacion = tasa_amortizacion_km * km_totales;
    double costo_mantenimiento = tasa_mantenimiento_km * km_totales;
    double costo_neumaticos = tasa_neumaticos_km * km_totales;
    double costo_seguro = tasa_seguro_km * km_totales;
    double costo_desgaste_total = costo_amortizacion + costo_mantenimiento + costo_neumaticos + costo_seguro;

    // 4. Totales Generales
    double costo_total_real = costo_combustible_total + costo_desgaste_total;
    double costo_promedio_km = costo_total_real / km_totales;

    // Imprimir pantalla de resultados

    printf("========================================================\n");
    printf("             RESUMEN Y COSTO REAL DEL VIAJE             \n");
    printf("========================================================\n");
    printf("Vehiculo: %s\n", v.nombre);
    printf("Precio del combustible: RD$ %.2f / galon\n", precio_combustible_galon);
    printf("Distancia Recorrida: %.2f km (Ciudad: %.2f km | Autopista: %.2f km)\n", km_totales, km_ciudad, km_autopista);
    printf("--------------------------------------------------------\n");
    printf("CONSUMO DE COMBUSTIBLE (EN GALONES Y PESOS):\n");
    printf("  - Ciudad:    %.2f galones  ->  RD$ %.2f\n", galones_ciudad, costo_comb_ciudad);
    printf("  - Autopista: %.2f galones  ->  RD$ %.2f\n", galones_autopista, costo_comb_autopista);
    printf("  - Total Consumo: %.2f gal  ->  RD$ %.2f\n", galones_totales, costo_combustible_total);
    printf("--------------------------------------------------------\n");
    printf("COSTOS PROPORCIONALES DEL VIAJE (DESGASTE Y FIJOS):\n");
    printf("  - Amortizacion (Depreciacion): RD$ %.2f\n", costo_amortizacion);
    printf("  - Mantenimiento Proporcional:  RD$ %.2f\n", costo_mantenimiento);
    printf("  - Desgaste de Neumaticos:      RD$ %.2f\n", costo_neumaticos);
    printf("  - Seguro Prorrateado:          RD$ %.2f\n", costo_seguro);
    printf("  - Subtotal Desgaste y Fijos:   RD$ %.2f\n", costo_desgaste_total);
    printf("--------------------------------------------------------\n");
    printf("COSTO SOLO COMBUSTIBLE POR KM:\n");
    printf("  - En Ciudad:    RD$ %.2f / km\n", precio_combustible_galon / v.rendimiento_ciudad);
    printf("  - En Autopista: RD$ %.2f / km\n", precio_combustible_galon / v.rendimiento_autopista);
    printf("========================================================\n");
    printf("  * COSTO TOTAL REAL DEL VIAJE:    RD$ %.2f\n", costo_total_real);
    printf("  * COSTO REAL PROMEDIO POR KM:    RD$ %.2f / km\n", costo_promedio_km);
    printf("========================================================\n");


}


