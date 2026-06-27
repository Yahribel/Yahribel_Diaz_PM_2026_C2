#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char noba[10];
    char nucu[10];
} banco;

typedef union
{
    banco che;
    banco nomi;
    char venta;
} fpago;

typedef struct
{
    char cnu[20];
    char col[20];
    char cp[5];
    char ciu[15];
} domicilio;

typedef struct
{
    int num;
    char nom[20];
    float ven[12];
    domicilio domi;
    float sal;
    fpago pago;
    int cla;
} vendedor;

void Lectura(vendedor A[], int T);
void F1(vendedor A[], int T);
void F2(vendedor A[], int T);
void F3(vendedor A[], int T);
void F4(vendedor A[], int T);

void main(void)
{
    vendedor VENDEDORES[100];
    int TAM;

    do
    {
        printf("Ingrese el numero de vendedores: ");
        scanf("%d", &TAM);
    }
    while (TAM > 100 || TAM < 1);

    Lectura(VENDEDORES, TAM);
    F1(VENDEDORES, TAM);
    F2(VENDEDORES, TAM);
    F3(VENDEDORES, TAM);
    F4(VENDEDORES, TAM);

    printf("\n\n\tFIN DEL PROGRAMA\n");

}

void Lectura(vendedor A[], int T)
{
    int I, J;
    for (I = 0; I < T; I++)
    {
        printf("\n\tIngrese datos del vendedor", I + 1);
        printf("\nNumero de vendedor: ");
        scanf("%d", &A[I].num);

        while (getchar() != '\n');

        printf("Nombre del vendedor: ");
        gets(A[I].nom);

        printf("Ventas del ano (12 meses: \n");
        for (J = 0; J < 12; J++)
        {
            printf("\tMes %d: ", J + 1);
            scanf("%f", &A[I].ven[J]);
        }
        while(getchar() != '\n');

            printf("Domicilio del vendedor: \n");
        printf("\tCalle y numero: ");
        gets(A[I].domi.cnu);

        printf("\tColonia: ");
        gets(A[I].domi.col);

        printf("\tCodigo Postal: ");
        gets(A[I].domi.cp);

        printf("\tCiudad: ");
        gets(A[I].domi.ciu);

        printf("Salario de vendedor: ");
        scanf("%f", &A[I].sal);

        printf("Forma de Pago (Banco/Cheque-1 Nomina-2 Ventanilla-3): ");
        scanf("%d", &A[I].cla);
        while (getchar() != '\n');

        switch (A[I].cla)
        {
        case 1:
            printf("\tNombre del banco (Cheque): ");
            gets(A[I].pago.che.noba);
            printf("\tNumero de cuenta: ");
            gets(A[I].pago.che.nucu);
            break;
        case 2:
            printf("\tNombre del banco (Nomina): ");
            gets(A[I].pago.nomi.noba);
            printf("\tNumero de cuenta: ");
            gets(A[I].pago.nomi.nucu);
            break;
        case 3:
            A[I].pago.venta = 'S';
            printf("\tPago asignado a Ventanilla.\n");
            break;
        default:
            printf("\tOpcion de pago no valida.\n");
            break;
        }

    }
}

void F1(vendedor A[], int T)
{
    int I, J;
    float SUM;
    printf("\n\n\t\tVentas totales de los vendedores");
    for (I = 0; I < T; I++)
    {
        SUM = 0.0;
        for (J = 0; J < 12; J++)
            SUM += A[I].ven[J];
        printf("\nVendedor Numero: %d\tNombre: %s\tVentas Anuales: %.2f", A[I].num, A[I].nom, SUM);
    }
}

void F2(vendedor A[], int T)
{
    int I, J;
    float SUM;
    printf("\n\n\t\tVendedores con ventas anuales > $1,500,000 (incentivo");
    for(I = 0; I < T; I++)
    {
        SUM = 0.0;
        for (J = 0; J < 12; J++)
        {
            SUM += A[I].ven[J];
        }
        if (SUM > 1500000.00)
        {
            A[I].sal = A[I].sal * 1.05;
            printf("\nNumero de empleado: %d\nVentas: %.2f\nNuveo salario (+5%%): %.2f\n", A[I].num, SUM, A[I].sal);
            }
    }
  }



void F3(vendedor A[], int T)
{
    int I, J;
     float SUM;
     printf("\n\n\t\tVendedora con ventas < $300,000");
     for(I = 0; I < T; I++)
     {
         SUM = 0.0;
         for (J = 0; J < 12; J++);
         {
         SUM += A[I].ven[J];
         }

         if (SUM < 300000.00)
         {
         printf("\nNumero de empleado: %d\nNombre: %s\nVentas: %.2f\n", A[I].num, A[I].nom, SUM);
     }
}
}

void F4(vendedor A[], int T)
{
    int I;
    printf("\n\n\t\tVendedores con cuenta de cheques (banco)");
    for(I = 0; I < T; I++)
    {
        if (A[I].cla == 1)
        {
            printf("\nNumero de vendedor: %d\nBanco: %s\nCuenta: %s\n", A[I].num, A[I].pago.che.noba, A[I].pago.che.nucu);
        }
    }
}


