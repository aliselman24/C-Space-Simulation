#ifndef DOSYAOKUYUCU_H
#define DOSYAOKUYUCU_H

#include "Gezegen.h"
#include "Arac.h"
#include "Kisi.h"

Gezegen** gezegenleriOku(const char *yol, int *gezegenSayisi);
Arac** araclariOku(const char *yol, int *aracSayisi);
Kisi** kisileriOku(const char *yol, int *kisiSayisi, Gezegen** gezegenler, int gezegenSayisi); // Güncellendi

#endif