#include "Arac.h"
#include "ZamanHesaplayici.h"
#include "Gezegen.h" // Eklendi
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Arac* yeniArac(const char* ad, const char* cikis, const char* hedef, time_t cikisTarih, double mesafe) {
    Arac* arac = (Arac*)malloc(sizeof(Arac));
    if (arac == NULL) {
        perror("Bellek ayırma hatası");
        return NULL;
    }
    strcpy(arac->ad, ad);
    strcpy(arac->cikis, cikis);
    strcpy(arac->hedef, hedef);
    arac->cikisTarih = cikisTarih;
    arac->mesafe = mesafe;
    arac->kalanSaat = mesafe;
    strcpy(arac->durum, "Bekliyor");
    arac->varisTahmini = 0; // Başlangıçta 0 olarak ayarla
    arac->imha = 0;
    arac->hedefeEklendiMi = 0;
    return arac;
}

void hesaplaVarisTarihi(Arac *arac, Gezegen *hedefG) {
    arac->varisTahmini = varisTarihiHesapla(arac->cikisTarih, arac->mesafe, hedefG->saatSayisi);
}

void durumGuncelle(Arac *arac, Gezegen *simdiGezegen) {
    if (arac->imha) {
        strcpy(arac->durum, "IMHA");
        return;
    }

    if (strcmp(arac->durum, "Bekliyor") == 0 && strcmp(simdiGezegen->ad, arac->cikis) == 0 && tarihAyni(simdiGezegen, arac->cikisTarih)) {
        strcpy(arac->durum, "Yolda");
    }

    if (strcmp(arac->durum, "Yolda") == 0) {
        arac->kalanSaat -= 1;
        if (arac->kalanSaat <= 0) {
            strcpy(arac->durum, "Vardi");
            arac->kalanSaat = 0;
        }
    }
}

void ekipKontrol(Arac *arac, Kisi *kisiler[], int kisiSayisi) {
    int hayattaVar = 0;
    for (int i = 0; i < kisiSayisi; i++) {
        if (strcmp(kisiler[i]->aracAdi, arac->ad) == 0 && kisiler[i]->hayatta) {
            hayattaVar = 1;
            break;
        }
    }
    if (!hayattaVar) {
        arac->imha = 1;
        strcpy(arac->durum, "IMHA");
    }
}

int isHedefeEklendiMi(Arac *arac) {
    return arac->hedefeEklendiMi;
}

void setHedefeEklendiMi(Arac *arac, int deger) {
    arac->hedefeEklendiMi = deger;
}

char* getDurum(Arac *arac) {
    return arac->durum;
}

char* getAd(Arac *arac) {
    return arac->ad;
}

char* getCikis(Arac *arac) {
    return arac->cikis;
}

char* getHedef(Arac *arac) {
    return arac->hedef;
}

double getKalanSaat(Arac *arac) {
    return arac->kalanSaat;
}

char* getVarisTahmini(Arac *arac) {
    return arac->imha ? "--" : timeToString(arac->varisTahmini);
}

time_t getCikisTarih(Arac *arac) {
    return arac->cikisTarih;
}