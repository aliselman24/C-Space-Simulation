#ifndef ZAMANHESAPLAYICI_H
#define ZAMANHESAPLAYICI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STR 256

// Fonksiyon prototipleri
int saatFarki(time_t baslangic, time_t bitis, int gezegenSaatSayisi);
time_t varisTarihiHesapla(time_t cikisTarih, double mesafe, int hedefGezegenSaatSayisi);
char* timeToString(time_t tarih);
time_t stringToTime(const char* tarihStr);

#endif