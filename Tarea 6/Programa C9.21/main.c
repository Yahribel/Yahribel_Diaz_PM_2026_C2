#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int clave;
    char nombre[20];
    int carrera;
    float promedio;
    float examen;
    char telefono[12];
}alumno;

float F1(FILE *);
void F2(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
void F3(FILE *, FILE *, FILE *, FILE *, FILE *);

void crearDatosDePrueba(void);


void main(void)
{
    float pro;
    FILE *ap, *c1, *c2, *c3, *c4, *c5;

    crearDatosDePrueba();

    ap = fopen("alu1.dat", "rb");
    c1 = fopen("car1.dat", "wb");
    c2 = fopen("car2.dat", "wb");
    c3 = fopen("car3.dat", "wb");
    c4 = fopen("car4.dat", "wb");
    c5 = fopen("car5.dat", "wb");

    if ((ap!=NULL) && (c1!=NULL) && (c2!=NULL) && (c3!=NULL) && (c4!=NULL) && (c5!=NULL))
    {
        pro = F1(ap);
        printf("\nPROMEDIO EXAMEN DE ADMISION :%.2f", pro);
        F2(ap, c1, c2, c3, c4, c5);


        fclose(ap);
        fclose(c1);
        fclose(c2);
        fclose(c3);
        fclose(c4);
        fclose(c5);

        c1 = fopen("car1.dat", "rb");
        c2 = fopen("car2.dat", "rb");
        c3 = fopen("car3.dat", "rb");
        c4 = fopen("car4.dat", "rb");
        c5 = fopen("car5.dat", "rb");

        F3(c1, c2, c3, c4, c5);

        fclose(c1);
        fclose(c2);
        fclose(c3);
        fclose(c4);
        fclose(c5);
    }
    else
    {
        printf("\nEl o los archivos no se pudieron abrir");
    if (ap) fclose(ap);
    if (c1) fclose(c1);
    if (c2) fclose(c2);
    if (c3) fclose(c3);
    if (c4) fclose(c4);
    if (c5) fclose(c5);
  }
}

void crearDatosDePrueba(void)
{
  FILE *f = fopen("alu1.dat", "wb");
  if (f != NULL)
  {
      alumno lista[5] = {
      {1, "Juan Perez", 1, 8.5, 1350.0, "5551234"},
      {2, "Maria Lopez", 2, 7.2, 1420.0, "5555678"},
      {3, "Pedro Gomez", 1, 7.5, 1200.0, "5559012"},
      {4, "Ana Torres", 3, 9.0, 1310.0, "5553456"},
      {5, "Luis Montero", 2, 8.2, 1280.0, "5557890"}

      };
      fwrite(lista, sizeof(alumno), 5, f);
      fclose(f);
  }
}
float F1(FILE *ap)
{
    alumno alu;
    float sum = 0, pro;
    int i = 0;
    rewind(ap);
    fread(&alu, sizeof(alumno), 1, ap);
    while(!feof(ap))
    {
        i++;
        sum += alu.examen;
        fread(&alu, sizeof(alumno), 1, ap);
    }
    pro = i > 0 ? (sum / i) : 0;
    return(pro);
}
void F2(FILE *ap, FILE *c1, FILE *c2, FILE *c3, FILE *c4, FILE *c5)
{
    alumno alu;
    rewind(ap);
    fread(&alu, sizeof(alumno), 1, ap);
    while (!feof(ap))
    {
        if (((alu.examen >= 1300) && (alu.promedio >= 8)) || ((alu.examen >= 1400) && (alu.promedio >= 7)))
        {
            switch (alu.carrera)
            {
                case 1: fwrite(&alu, sizeof(alumno), 1, c1);
                break;
                case 2: fwrite(&alu, sizeof(alumno), 1, c2);
                break;
                case 3: fwrite(&alu, sizeof(alumno), 1, c3);
                break;
                case 4: fwrite(&alu, sizeof(alumno), 1, c4);
                break;
                case 5: fwrite(&alu, sizeof(alumno), 1, c5);
                break;
            }
        }
        fread(&alu, sizeof(alumno), 1, ap);
    }
}

void F3 (FILE *c1, FILE *c2, FILE *c3, FILE *c4, FILE *c5)
{
    alumno alu;
    float cal[5], sum;
    int i;

    i = 0; sum = 0; rewind(c1);
    fread(&alu, sizeof(alumno), 1, c1);
    while (!feof(c1)) { i++; sum += alu.examen; fread(&alu, sizeof(alumno), 1, c1);}
    cal[0] = i ? (sum / i) : 0;

    i = 0; sum = 0; rewind(c2);
    fread(&alu, sizeof(alumno), 1, c2);
    while (!feof(c2)) {i++; sum += alu.examen; fread(&alu, sizeof(alumno), 1, c2);}
    cal[1] = i ? (sum / i) : 0;

    i = 0; sum = 0; rewind(c3);
    fread(&alu, sizeof(alumno), 1, c3);
    while (!feof(c3)) {i++; sum += alu.examen; fread(&alu, sizeof(alumno), 1, c3);}
    cal[2] = i ? (sum / i) : 0;

    i = 0; sum = 0; rewind(c4);
    fread(&alu, sizeof(alumno), 1, c4);
    while (!feof(c4)) {i++; sum += alu.examen; fread(&alu, sizeof(alumno), 1, c4);}
    cal[3] = i ? (sum / i) : 0;

    i = 0; sum = 0; rewind(c5);
    fread(&alu, sizeof(alumno), 1, c5);
    while (!feof(c5)) {i++; sum += alu.examen; fread(&alu, sizeof(alumno), 1, c5);}
    cal[4] = i ? (sum / i) : 0;

    printf("\nRESULTADOS ADMITIDOS POR CARRERA");
    for(i = 0; i<5; i++)
        printf("\nPromedio examen admitidos carrera %d: %.2f", i + 1, cal[i]);
    printf("\n");
}
