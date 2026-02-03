#include "DosyaOkuyucu.h"
#include "ZamanHesaplayici.h"
#include "KayacGezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "CuceGezegen.h"

// Yardımcı fonksiyon: Bir satırı '#' karakterine göre böler ve token dizisi döndürür
char** splitString(char* str, const char* delimiter, int* tokenCount) {
    char** tokens = NULL;
    char* token = strtok(str, delimiter);
    *tokenCount = 0;

    while (token != NULL) {
        tokens = (char**)realloc(tokens, (*tokenCount + 1) * sizeof(char*));
        if (tokens == NULL) {
            perror("Bellek ayırma hatası");
            for (int i = 0; i < *tokenCount; i++) {
                free(tokens[i]);
            }
            free(tokens);
            return NULL;
        }
        tokens[*tokenCount] = strdup(token);
        if (tokens[*tokenCount] == NULL) {
            perror("Bellek ayırma hatası");
            for (int i = 0; i < *tokenCount; i++) {
                free(tokens[i]);
            }
            free(tokens);
            return NULL;
        }
        (*tokenCount)++;
        token = strtok(NULL, delimiter);
    }
    return tokens;
}

Gezegen** gezegenleriOku(const char *yol, int *gezegenSayisi) {
    Gezegen** gezegenler = NULL;
    FILE *dosya = fopen(yol, "r");
    if (dosya == NULL) {
        perror("Dosya açma hatası");
        return NULL;
    }

    char satir[256];
    *gezegenSayisi = 0;

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        satir[strcspn(satir, "\n")] = 0;
        int tokenSayisi;
        char* tempSatir = strdup(satir);
        if (tempSatir == NULL) {
            perror("Bellek ayırma hatası");
            fclose(dosya);
            for (int i = 0; i < *gezegenSayisi; i++) {
                free(gezegenler[i]);
            }
            free(gezegenler);
            return NULL;
        }
        char** p = splitString(tempSatir, "#", &tokenSayisi);
        free(tempSatir);

        if (p != NULL && tokenSayisi == 4) {
            gezegenler = (Gezegen**)realloc(gezegenler, (*gezegenSayisi + 1) * sizeof(Gezegen*));
            if (gezegenler == NULL) {
                perror("Bellek ayırma hatası");
                // Belleği ve dosyayı temizle
                for (int i = 0; i < *gezegenSayisi; i++) {
                    free(gezegenler[i]);
                }
                free(gezegenler);
                for (int i = 0; i < tokenSayisi; i++) {
                    free(p[i]);
                }
                free(p);
                fclose(dosya);
                return NULL;
            }
            time_t baslangicTarih = stringToTime(p[3]);

            // Gezegen türüne göre doğru yapıyı oluştur
            int gezegenTuru = atoi(p[1]); // Gezegen türünü sayıya çevir
            switch (gezegenTuru) {
                case 1: // Kayac
                    gezegenler[*gezegenSayisi] = (Gezegen*)yeniKayacGezegen(p[0], atoi(p[2]), baslangicTarih);
                    break;
                case 2: // GazDevi
                    gezegenler[*gezegenSayisi] = (Gezegen*)yeniGazDeviGezegen(p[0], atoi(p[2]), baslangicTarih);
                    break;
                case 3: // BuzDevi
                    gezegenler[*gezegenSayisi] = (Gezegen*)yeniBuzDeviGezegen(p[0], atoi(p[2]), baslangicTarih);
                    break;
                case 4: // Cuce
                    gezegenler[*gezegenSayisi] = (Gezegen*)yeniCuceGezegen(p[0], atoi(p[2]), baslangicTarih);
                    break;
                default:
                    fprintf(stderr, "Bilinmeyen gezegen türü: %s\n", p[1]);
                    // Belleği ve dosyayı temizle
                    for (int i = 0; i < *gezegenSayisi; i++) {
                        free(gezegenler[i]);
                    }
                    free(gezegenler);
                    for (int i = 0; i < tokenSayisi; i++) {
                        free(p[i]);
                    }
                    free(p);
                    fclose(dosya);
                    return NULL;
            }

            if (gezegenler[*gezegenSayisi] == NULL) {
                fprintf(stderr, "Gezegen oluşturma hatası\n");
                // Belleği ve dosyayı temizle
                for (int i = 0; i < *gezegenSayisi; i++) {
                    free(gezegenler[i]);
                }
                free(gezegenler);
                for (int i = 0; i < tokenSayisi; i++) {
                    free(p[i]);
                }
                free(p);
                fclose(dosya);
                return NULL;
            }
            (*gezegenSayisi)++;

            for (int i = 0; i < tokenSayisi; i++) {
                free(p[i]);
            }
            free(p);
        } else {
            fprintf(stderr, "Hatalı gezegen satırı: %s\n", satir);
        }
    }

    fclose(dosya);
    return gezegenler;
}

Arac** araclariOku(const char *yol, int *aracSayisi) {
    Arac** araclar = NULL;
    FILE *dosya = fopen(yol, "r");
    if (dosya == NULL) {
        perror("Dosya açma hatası");
        return NULL;
    }

    char satir[256];
    *aracSayisi = 0;

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        satir[strcspn(satir, "\n")] = 0;
        int tokenSayisi;
        char* tempSatir = strdup(satir);
        if (tempSatir == NULL) {
            perror("Bellek ayırma hatası");
            fclose(dosya);
            for (int i = 0; i < *aracSayisi; i++) {
                free(araclar[i]);
            }
            free(araclar);
            return NULL;
        }
        char** p = splitString(tempSatir, "#", &tokenSayisi);
        free(tempSatir);

        if (p != NULL && tokenSayisi == 5) {
            araclar = (Arac**)realloc(araclar, (*aracSayisi + 1) * sizeof(Arac*));
            if (araclar == NULL) {
                perror("Bellek ayırma hatası");
                for (int i = 0; i < *aracSayisi; i++) {
                    free(araclar[i]);
                }
                free(araclar);
                for (int i = 0; i < tokenSayisi; i++) {
                    free(p[i]);
                }
                free(p);
                fclose(dosya);
                return NULL;
            }
            time_t cikisTarih = stringToTime(p[3]);
            araclar[*aracSayisi] = yeniArac(p[0], p[1], p[2], cikisTarih, atof(p[4]));
            if (araclar[*aracSayisi] == NULL) {
                fprintf(stderr, "Araç oluşturma hatası\n");
                for (int i = 0; i < *aracSayisi; i++) {
                    free(araclar[i]);
                }
                free(araclar);
                for (int i = 0; i < tokenSayisi; i++) {
                    free(p[i]);
                }
                free(p);
                fclose(dosya);
                return NULL;
            }
            (*aracSayisi)++;

            for (int i = 0; i < tokenSayisi; i++) {
                free(p[i]);
            }
            free(p);
        } else {
            fprintf(stderr, "Hatalı araç satırı: %s\n", satir);
        }
    }

    fclose(dosya);
    return araclar;
}

Kisi** kisileriOku(const char *yol, int *kisiSayisi, Gezegen** gezegenler, int gezegenSayisi) {
    Kisi** kisiler = NULL;
    FILE *dosya = fopen(yol, "r");
    if (dosya == NULL) {
        perror("Dosya açma hatası");
        return NULL;
    }

    char satir[256];
    *kisiSayisi = 0;

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        satir[strcspn(satir, "\n")] = 0;
        int tokenSayisi;
        char* tempSatir = strdup(satir);
        if (tempSatir == NULL) {
            perror("Bellek ayırma hatası");
            fclose(dosya);
            for (int i = 0; i < *kisiSayisi; i++) {
                free(kisiler[i]);
            }
            free(kisiler);
            return NULL;
        }
        char** p = splitString(tempSatir, "#", &tokenSayisi);
        free(tempSatir);

        if (p != NULL && tokenSayisi == 4) {
            kisiler = (Kisi**)realloc(kisiler, (*kisiSayisi + 1) * sizeof(Kisi*));
            if (kisiler == NULL) {
                perror("Bellek ayırma hatası");
                for (int i = 0; i < *kisiSayisi; i++) {
                    free(kisiler[i]);
                }
                free(kisiler);
                for (int i = 0; i < tokenSayisi; i++) {
                    free(p[i]);
                }
                free(p);
                fclose(dosya);
                return NULL;
            }
            
            double yasanmaKatsayisi = 1.0; // Varsayılan değer
            for (int i = 0; i < gezegenSayisi; i++) {
                if (strcmp(p[3], gezegenler[i]->ad) == 0) {
                    if (strcmp(gezegenler[i]->ad, "Kayac") == 0) {
                         yasanmaKatsayisi = getKayacYasanmaKatsayisi((KayacGezegen*)gezegenler[i]);
                    } else if (strcmp(gezegenler[i]->ad, "GazDevi") == 0) {
                         yasanmaKatsayisi = getGazDeviYasanmaKatsayisi((GazDeviGezegen*)gezegenler[i]);
                    } else if (strcmp(gezegenler[i]->ad, "BuzDevi") == 0) {
                         yasanmaKatsayisi = getBuzDeviYasanmaKatsayisi((BuzDeviGezegen*)gezegenler[i]);
                    } else if (strcmp(gezegenler[i]->ad, "Cuce") == 0) {
                         yasanmaKatsayisi = getCuceYasanmaKatsayisi((CuceGezegen*)gezegenler[i]);
                    }
                    break;
                }
            }
            
            kisiler[*kisiSayisi] = yeniKisi(p[0], atoi(p[1]), atol(p[2]), p[3], yasanmaKatsayisi);
            if (kisiler[*kisiSayisi] == NULL) {
                fprintf(stderr, "Kişi oluşturma hatası\n");
                for (int i = 0; i < *kisiSayisi; i++) {
                    free(kisiler[i]);
                }
                free(kisiler);
                for (int i = 0; i < tokenSayisi; i++) {
                    free(p[i]);
                }
                free(p);
                fclose(dosya);
                return NULL;
            }
            (*kisiSayisi)++;

            for (int i = 0; i < tokenSayisi; i++) {
                free(p[i]);
            }
            free(p);
        } else {
            fprintf(stderr, "Hatalı kişi satırı: %s\n", satir);
        }
    }

    fclose(dosya);
    return kisiler;
}