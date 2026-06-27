#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char cal [20];
    int num;
    char col[20];
    char cp[5];
    char ciu[20];
} domicilio;

typedef struct
{
    char nom[20];
    int edad;
    char sexo;
    int con;
    domicilio dom;
    char tel[10];
}paciente;

void Lectura(paciente *, int);
void F1(paciente *, int);
void F2(paciente *, int);
void F3(paciente *, int);

void main(void)
{
    paciente HOSPITAL[100];
    int TAM;

    do
    {
        printf("Ingrese el numero de pacientes: ");
        scanf("%d", &TAM);
    }
    while (TAM > 100 || TAM < 1);
    Lectura(HOSPITAL, TAM);
    F1(HOSPITAL, TAM);
    F2(HOSPITAL, TAM);
    F3(HOSPITAL, TAM);
}

void Lectura(paciente A[], int T)
{
    int I;
    for(I + 0; I< T; I++)
    {
        printf("\n\t\tPaciente %d", I + 1);
        while (getchar() != '\n');

        printf("\nNombre: ");
        gets(A[I].nom);

        printf("Edad: ");
        scanf("%d", &A[I].edad);

        printf("Sexo (F-M): ");
        scanf(" %c", &A[I].sexo);

        printf("Condicion:  (1..5) ");
        scanf("%d", &A[I].con);
        while(getchar() != '\n');

        printf("\tCalle: ");
        gets(A[I].dom.cal);

        printf("\tNumero: ");
        scanf("%d", &A[I].dom.num);
        while (getchar() != '\n');

        printf("\tColonia: ");
        gets(A[I].dom.col);

        printf("\tCodigo postal: ");
        gets(A[I].dom.cp);

        printf("\tCiudad: ");
        gets(A[I].dom.ciu);

        printf("Telefono: ");
        gets(A[I].tel);

    }
}

void F1(paciente A[], int T)
{
    int I;
    int FEM = 0, MAS = 0, TOT;

    for (I = 0; I < T; I++)
    {
        switch (A[I].sexo)
        {
            case 'F': case 'f': FEM++;
            break;
            case 'M': case 'm': MAS++;
            break;
        }
    }

    TOT = FEM + MAS;

    if(TOT > 0)
    {
        printf("\nPorcentaje de Hombres: %.2f%%", (float)MAS / TOT * 100);
        printf("\nPorcentaje de Mujeres: %.2f%%", (float)FEM / TOT * 100);
    }
    else
    {
        printf("\nNo se registraron sexos validos para el calculo. ");
    }
}

void F2(paciente A[], int T)
{
    int I, C1 = 0, C2 = 0, C3 = 0, C4 = 0, C5 = 0;
    for (I = 0; I < T; I++)
    {
        switch (A[I].con)
        {
            case 1: C1++; break;
            case 2: C2++; break;
            case 3: C3++; break;
            case 4: C4++; break;
            case 5: C5++; break;
        }
    }
    printf("\n\nNumero de pacientes en condicion 1: %d", C1);
    printf("\nNumero pacientes en condicion 2: %d", C2);
    printf("\nNumero pacientes en condicion 3: %d", C3);
    printf("\nNumero pacientes en condicion 4: %d", C4);
    printf("\nNumero pacientes en condicion 5: %d", C5);
}

void F3(paciente A[], int T)
{
    int I;
    printf("\n\n\acientes ingresados en estados de gravedad (5):");
    for (I = 0; I < T; I++)
    {
        if (A[I].con == 5)
            printf("\n\tNombre: %s\tTelefono: %s", A[I].nom, A[I].tel);

    }
    printf("\n");
}

