#include "Kisi.h"

Kisi* yeniKisi(char isim[], int yas, long kalanOmur, char aracAdi[], double yasanmaKatsayisi) {
    Kisi* kisi = (Kisi*)malloc(sizeof(Kisi));
    if (!kisi) {
        perror("Bellek ayırma hatası");
        return NULL;
    }
    strcpy(kisi->isim, isim);
    kisi->kalanOmur = kalanOmur;
    strcpy(kisi->aracAdi, aracAdi);
    kisi->hayatta = 1;
    kisi->yasanmaKatsayisi = yasanmaKatsayisi; // Yaşanma katsayısı atanıyor
    return kisi;
}

char* getKisiIsim(Kisi *kisi) {
    return kisi->isim;
}

char* getAracAdi(Kisi *kisi) {
    return kisi->aracAdi;
}

int hayattaMi(Kisi *kisi) {
    return kisi->hayatta;
}

void saatIlerle(Kisi *kisi) {
    if (kisi->hayatta) {
        kisi->kalanOmur -= (long)(1 * kisi->yasanmaKatsayisi); // Katsayıya göre yaşlanma
        if (kisi->kalanOmur <= 0) kisi->hayatta = 0;
    }
}