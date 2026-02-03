#ifndef KISI_H
#define KISI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 256

typedef struct {
    char isim[MAX_STR];
    long kalanOmur;
    char aracAdi[MAX_STR];
    int hayatta;
    double yasanmaKatsayisi; // Kişinin yaşlanma katsayısı
} Kisi;

Kisi* yeniKisi(char isim[], int yas, long kalanOmur, char aracAdi[], double yasanmaKatsayisi);
char* getKisiIsim(Kisi *kisi);
char* getAracAdi(Kisi *kisi);
int hayattaMi(Kisi *kisi);
void saatIlerle(Kisi *kisi);

#endif