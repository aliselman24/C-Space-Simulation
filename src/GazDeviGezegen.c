#include "GazDeviGezegen.h"

GazDeviGezegen* yeniGazDeviGezegen(char ad[], int saatSayisi, time_t baslangicTarih) {
    GazDeviGezegen* gazDeviGezegen = (GazDeviGezegen*)malloc(sizeof(GazDeviGezegen));
    if (!gazDeviGezegen) {
        perror("Bellek ayırma hatası");
        return NULL;
    }
    gazDeviGezegen->gezegen = *yeniGezegen(ad, saatSayisi, baslangicTarih);
    gazDeviGezegen->yasanmaKatsayisi = 0.8;
    return gazDeviGezegen;
}

double getGazDeviYasanmaKatsayisi(GazDeviGezegen *gezegen) {
    return gezegen->yasanmaKatsayisi;
}