#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h> // Windows'ta konsolu temizlemek için
#else
#include <unistd.h>   // Unix/Linux'ta konsolu temizlemek için
#endif

#include "Gezegen.h"
#include "Arac.h"
#include "Kisi.h"
#include "DosyaOkuyucu.h"
#include "ZamanHesaplayici.h"
#include "KayacGezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "CuceGezegen.h"

#define MAX_GEZEGEN 100
#define MAX_ARAC 100
#define MAX_KISI 100

// Yardımcı fonksiyon: Diziyi serbest bırakır
void freeDizi(void** dizi, int boyut) {
    if (dizi == NULL) return;
    for (int i = 0; i < boyut; i++) {
        free(dizi[i]);
    }
    free(dizi);
}

// Yardımcı fonksiyon: Konsolu temizler
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    // Dosyadan okunan verileri saklamak için dinamik diziler
    Gezegen* gezegenler[MAX_GEZEGEN];
    Arac* araclar[MAX_ARAC];
    Kisi* kisiler[MAX_KISI];

    int gezegenSayisi = 0;
    int aracSayisi = 0;
    int kisiSayisi = 0;

    // Dosyaları oku
    Gezegen** gezegenler_temp = gezegenleriOku("./data/Gezegenler.txt", &gezegenSayisi);
    Arac** araclar_temp = araclariOku("./data/Araclar.txt", &aracSayisi);
    Kisi** kisiler_temp = kisileriOku("./data/Kisiler.txt", &kisiSayisi, gezegenler_temp, gezegenSayisi);

    // Okunan verileri ana dizilere kopyala ve geçici diziyi serbest bırak
    if (gezegenler_temp != NULL) {
        for (int i = 0; i < gezegenSayisi; i++) {
            gezegenler[i] = gezegenler_temp[i];
        }
        free(gezegenler_temp);
    }
    if (araclar_temp != NULL) {
        for (int i = 0; i < aracSayisi; i++) {
            araclar[i] = araclar_temp[i];
        }
        free(araclar_temp);
    }
    if (kisiler_temp != NULL) {
        for (int i = 0; i < kisiSayisi; i++) {
            kisiler[i] = kisiler_temp[i];
        }
        free(kisiler_temp);
    }

    // Gezegen nüfusunu saklamak için dinamik bir dizi
    int gezegenNufus[MAX_GEZEGEN];
    for (int i = 0; i < gezegenSayisi; i++) {
        gezegenNufus[i] = rand() % 26 + 5; // 5-30 arası rastgele
    }

    // Araçların varış tarihlerini hesapla
    for (int i = 0; i < aracSayisi; i++) {
        for (int j = 0; j < gezegenSayisi; j++) {
            if (strcmp(araclar[i]->hedef, gezegenler[j]->ad) == 0) {
                hesaplaVarisTarihi(araclar[i], gezegenler[j]);
                break;
            }
        }
    }

    // Simülasyon döngüsü
    int iterasyonSayisi = 1;
    int simulasyonDevamEdiyor = 1;

    while (simulasyonDevamEdiyor) {
        clearConsole();

        printf("----------------------------------------------------------------------------------\n");
        printf("                          UZAY SIMULASYONU - ITERASYON: %d                          \n", iterasyonSayisi);
        printf("----------------------------------------------------------------------------------\n\n");

        // Gezegenlerin durumu
        printf("GEZEGENLER:\n");
        printf("----------------------------------------------------------------------------------\n");
        printf("%-10s | %-20s | %-10s\n", "Gezegen", "Tarih", "Nüfus");
        printf("----------------------------------------------------------------------------------\n");
        for (int i = 0; i < gezegenSayisi; i++) {
            char* tarihStr = mevcutTarihiStringeDonustur(gezegenler[i]);
            printf("%-10s | %-20s | %-10d\n", gezegenler[i]->ad, tarihStr, gezegenNufus[i]);
            free(tarihStr);
        }
        printf("----------------------------------------------------------------------------------\n\n");

        // Uzay araçlarının durumu
        printf("UZAY ARACLARI:\n");
        printf("------------------------------------------------------------------------------------------------------------------\n");
        printf("%-20s | %-15s | %-10s | %-10s | %-20s | %-20s\n",
               "Araç Adı", "Durum", "Çıkış", "Varış", "Kalan Süre", "Varış Tarihi");
        printf("------------------------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < aracSayisi; i++) {
            for (int j = 0; j < gezegenSayisi; j++) {
                if (strcmp(araclar[i]->cikis, gezegenler[j]->ad) == 0) {
                    durumGuncelle(araclar[i], gezegenler[j]);
                    break;
                }
            }
            ekipKontrol(araclar[i], kisiler, kisiSayisi);

            // Varış tarihini al
            char* varisTarihiStr = timeToString(araclar[i]->varisTahmini);

            printf("%-20s | %-15s | %-10s | %-10s | %-20.0f Saat | %-20s\n",
                   araclar[i]->ad, araclar[i]->durum, araclar[i]->cikis, araclar[i]->hedef,
                   araclar[i]->kalanSaat, varisTarihiStr);

            free(varisTarihiStr); // Belleği serbest bırak
        }
        printf("------------------------------------------------------------------------------------------------------------------\n\n");

        // Araçlar hedefe vardıysa içindeki kişileri ilgili gezegene taşı
        for (int i = 0; i < aracSayisi; i++) {
            if (strcmp(araclar[i]->durum, "Vardi") == 0 && !isHedefeEklendiMi(araclar[i])) {
                int gelenKisiSayisi = 0;
                for (int k = 0; k < kisiSayisi; k++) {
                    if (strcmp(kisiler[k]->aracAdi, araclar[i]->ad) == 0 && kisiler[k]->hayatta) {
                        gelenKisiSayisi++;
                    }
                }
                for (int j = 0; j < gezegenSayisi; j++) {
                    if (strcmp(gezegenler[j]->ad, araclar[i]->hedef) == 0) {
                        gezegenNufus[j] += gelenKisiSayisi;
                        setHedefeEklendiMi(araclar[i], 1); // true
                        break;
                    }
                }
            }
        }

        // Kişiler her saatte yaşlanacak
        for (int i = 0; i < kisiSayisi; i++) {
            saatIlerle(kisiler[i]);
        }

        // Gezegenlerde saat ilerlemesi
        for (int i = 0; i < gezegenSayisi; i++) {
            birSaatIlerle(gezegenler[i]);
        }

        // Simülasyon devam kontrolü
        simulasyonDevamEdiyor = 0;
        for (int i = 0; i < aracSayisi; i++) {
            if (strcmp(araclar[i]->durum, "Vardi") != 0 && strcmp(araclar[i]->durum, "IMHA") != 0) {
                simulasyonDevamEdiyor = 1;
                break;
            }
        }
        if (simulasyonDevamEdiyor == 0) {
            for (int i = 0; i < kisiSayisi; i++) {
                if (kisiler[i]->hayatta) {
                    simulasyonDevamEdiyor = 1;
                    break;
                }
            }
        }

        
        #ifdef _WIN32
        
        #endif

        iterasyonSayisi++;
    }

    // Belleği serbest bırak
    for (int i = 0; i < gezegenSayisi; i++) {
        free(gezegenler[i]);
    }
    for (int i = 0; i < aracSayisi; i++) {
        free(araclar[i]);
    }
    for (int i = 0; i < kisiSayisi; i++) {
        free(kisiler[i]);
    }

    return 0;
}