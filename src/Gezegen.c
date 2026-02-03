#include "Gezegen.h"
#include "ZamanHesaplayici.h"

Gezegen* yeniGezegen(char ad[], int saatSayisi, time_t baslangicTarih) {
    Gezegen* gezegen = (Gezegen*)malloc(sizeof(Gezegen));
    if (!gezegen) {
        perror("Bellek ayırma hatası");
        return NULL;
    }
    strcpy(gezegen->ad, ad);
    gezegen->saatSayisi = saatSayisi;
    gezegen->mevcutTarih = baslangicTarih;
    return gezegen;
}

char* getGezegenAd(Gezegen *gezegen) {
    return gezegen->ad;
}

int getGezegenSaatSayisi(Gezegen *gezegen) {
    return gezegen->saatSayisi;
}

time_t getMevcutTarih(Gezegen *gezegen) {
    return gezegen->mevcutTarih;
}

void birSaatIlerle(Gezegen *gezegen) {
    gezegen->mevcutTarih += 3600 * gezegen->saatSayisi;
}

char* mevcutTarihiStringeDonustur(Gezegen *gezegen) {
    return timeToString(gezegen->mevcutTarih);
}

int tarihAyni(Gezegen *gezegen, time_t digerTarih) {
    return gezegen->mevcutTarih == digerTarih;
}