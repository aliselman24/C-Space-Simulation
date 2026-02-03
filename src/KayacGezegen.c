#include "KayacGezegen.h"

KayacGezegen* yeniKayacGezegen(char ad[], int saatSayisi, time_t baslangicTarih) {
    KayacGezegen* kayacGezegen = (KayacGezegen*)malloc(sizeof(KayacGezegen));
    if (!kayacGezegen) {
        perror("Bellek ayırma hatası");
        return NULL;
    }
    kayacGezegen->gezegen = *yeniGezegen(ad, saatSayisi, baslangicTarih);
    kayacGezegen->yasanmaKatsayisi = 1.0;
    return kayacGezegen;
}

double getKayacYasanmaKatsayisi(KayacGezegen *gezegen) {
    return gezegen->yasanmaKatsayisi;
}