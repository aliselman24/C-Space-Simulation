#include "BuzDeviGezegen.h"

BuzDeviGezegen* yeniBuzDeviGezegen(char ad[], int saatSayisi, time_t baslangicTarih) {
    BuzDeviGezegen* buzDeviGezegen = (BuzDeviGezegen*)malloc(sizeof(BuzDeviGezegen));
    if (!buzDeviGezegen) {
        perror("Bellek ayırma hatası");
        return NULL;
    }
    buzDeviGezegen->gezegen = *yeniGezegen(ad, saatSayisi, baslangicTarih);
    buzDeviGezegen->yasanmaKatsayisi = 0.6;
    return buzDeviGezegen;
}

double getBuzDeviYasanmaKatsayisi(BuzDeviGezegen *gezegen) {
    return gezegen->yasanmaKatsayisi;
}