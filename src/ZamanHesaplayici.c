#include "ZamanHesaplayici.h"

int saatFarki(time_t baslangic, time_t bitis, int gezegenSaatSayisi) {
    double fark = difftime(bitis, baslangic) / 3600; // Saat cinsinden fark
    return (int)(fark / gezegenSaatSayisi); // Kaç gün geçti
}

time_t varisTarihiHesapla(time_t cikisTarih, double mesafe, int hedefGezegenSaatSayisi) {
    // Basitçe mesafe kadar saat ekliyoruz (gerçekçi değil ama örnek için yeterli)
    return cikisTarih + (time_t)(mesafe * 3600);
}

char* timeToString(time_t tarih) {
    char* tarihStr = (char*)malloc(20 * sizeof(char));
    struct tm *tm_info = localtime(&tarih);
    strftime(tarihStr, 20, "%d.%m.%Y %H:%M:%S", tm_info);
    return tarihStr;
}

time_t stringToTime(const char* tarihStr) {
    struct tm tm;
    memset(&tm, 0, sizeof(tm));
    int gun, ay, yil, saat = 0, dakika = 0, saniye = 0; // Varsayılan değerler 0

    // Tarih ve saat ayrımı
    char tarih[11], saatStr[9];
    if (sscanf(tarihStr, "%10s %8s", tarih, saatStr) == 2) {
        sscanf(tarih, "%d.%d.%d", &gun, &ay, &yil);
        sscanf(saatStr, "%d:%d:%d", &saat, &dakika, &saniye);
    } else if (sscanf(tarihStr, "%10s", tarih) == 1) {
        sscanf(tarih, "%d.%d.%d", &gun, &ay, &yil);
    } else {
        fprintf(stderr, "Hatalı tarih formatı: %s\n", tarihStr);
        return 0; // Hata durumunda 0 döndür
    }

    tm.tm_mday = gun;
    tm.tm_mon = ay - 1;       // tm_mon 0-11 aralığında
    tm.tm_year = yil - 1900;  // tm_year 1900'den beri geçen yıl
    tm.tm_hour = saat;
    tm.tm_min = dakika;
    tm.tm_sec = saniye;
    tm.tm_isdst = -1;      // Otomatik yaz saati/kış saati belirleme

    return mktime(&tm);
}