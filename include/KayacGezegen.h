#ifndef KAYACGEZEGEN_H
#define KAYACGEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen gezegen;
    double yasanmaKatsayisi;
} KayacGezegen;

KayacGezegen* yeniKayacGezegen(char ad[], int saatSayisi, time_t baslangicTarih);
double getKayacYasanmaKatsayisi(KayacGezegen *gezegen);

#endif