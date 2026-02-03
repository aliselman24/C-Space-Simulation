#ifndef ARAC_H
#define ARAC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Gezegen.h"
#include "Kisi.h"

#define MAX_STR 256

typedef struct {
    char ad[MAX_STR];
    char cikis[MAX_STR];
    char hedef[MAX_STR];
    time_t cikisTarih;
    double mesafe;
    double kalanSaat;
    char durum[MAX_STR];
    time_t varisTahmini;
    int imha;
    int hedefeEklendiMi;
} Arac;

Arac* yeniArac(const char* ad, const char* cikis, const char* hedef, time_t cikisTarih, double mesafe);
void hesaplaVarisTarihi(Arac *arac, Gezegen *hedefG);
void durumGuncelle(Arac *arac, Gezegen *simdiGezegen);
void ekipKontrol(Arac *arac, Kisi *kisiler[], int kisiSayisi);
int isHedefeEklendiMi(Arac *arac);
void setHedefeEklendiMi(Arac *arac, int deger);
char* getDurum(Arac *arac);
char* getAd(Arac *arac);
char* getCikis(Arac *arac);
char* getHedef(Arac *arac);
double getKalanSaat(Arac *arac);
char* getVarisTahmini(Arac *arac);
time_t getCikisTarih(Arac *arac);

#endif