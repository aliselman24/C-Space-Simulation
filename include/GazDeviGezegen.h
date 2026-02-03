#ifndef GAZDEVIGEZEGEN_H
#define GAZDEVIGEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen gezegen;
    double yasanmaKatsayisi;
} GazDeviGezegen;

GazDeviGezegen* yeniGazDeviGezegen(char ad[], int saatSayisi, time_t baslangicTarih);
double getGazDeviYasanmaKatsayisi(GazDeviGezegen *gezegen);

#endif