#ifndef GEZEGEN_H
#define GEZEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STR 256

// Ortak gezegen özellikleri
typedef struct {
    char ad[MAX_STR];
    int saatSayisi;
    time_t mevcutTarih;
} Gezegen;

Gezegen* yeniGezegen(char ad[], int saatSayisi, time_t baslangicTarih);
char* getGezegenAd(Gezegen *gezegen);
int getGezegenSaatSayisi(Gezegen *gezegen);
time_t getMevcutTarih(Gezegen *gezegen);
void birSaatIlerle(Gezegen *gezegen);
char* mevcutTarihiStringeDonustur(Gezegen *gezegen);
int tarihAyni(Gezegen *gezegen, time_t digerTarih);

#endif