#ifndef BUZDEVIGEZEGEN_H
#define BUZDEVIGEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen gezegen;
    double yasanmaKatsayisi;
} BuzDeviGezegen;

BuzDeviGezegen* yeniBuzDeviGezegen(char ad[], int saatSayisi, time_t baslangicTarih);
double getBuzDeviYasanmaKatsayisi(BuzDeviGezegen *gezegen);

#endif