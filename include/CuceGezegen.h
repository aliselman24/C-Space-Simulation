#ifndef CUCEGEZEGEN_H
#define CUCEGEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen gezegen;
    double yasanmaKatsayisi;
} CuceGezegen;

CuceGezegen* yeniCuceGezegen(char ad[], int saatSayisi, time_t baslangicTarih);
double getCuceYasanmaKatsayisi(CuceGezegen *gezegen);

#endif