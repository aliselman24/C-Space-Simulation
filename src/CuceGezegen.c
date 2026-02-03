#include "CuceGezegen.h"

CuceGezegen* yeniCuceGezegen(char ad[], int saatSayisi, time_t baslangicTarih) {
    CuceGezegen* cuceGezegen = (CuceGezegen*)malloc(sizeof(CuceGezegen));
    if (!cuceGezegen) {
        perror("Bellek ayırma hatası");
        return NULL;
    }
    cuceGezegen->gezegen = *yeniGezegen(ad, saatSayisi, baslangicTarih);
    cuceGezegen->yasanmaKatsayisi = 0.4;
    return cuceGezegen;
}

double getCuceYasanmaKatsayisi(CuceGezegen *gezegen) {
    return gezegen->yasanmaKatsayisi;
}