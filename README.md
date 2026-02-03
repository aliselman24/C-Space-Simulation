# 🌌 Space Travel Simulation in C (C ile Uzay Simülasyonu)

![C](https://img.shields.io/badge/Language-C-A8B9CC?style=for-the-badge&logo=c&logoColor=white)
![Memory Management](https://img.shields.io/badge/Focus-Pointers%20%26%20Memory-red?style=for-the-badge)
![Structs](https://img.shields.io/badge/Architecture-Struct%20Composition-blue?style=for-the-badge)

## 🚀 Proje Hakkında (About)
Bu proje, Java ile geliştirilen uzay simülasyonunun **C programlama dili** ile yeniden uygulanmış halidir. Amaç, Nesne Yönelimli Programlama (OOP) kavramlarını (Kalıtım, Polimorfizm) saf C dilinde **Struct (Yapı)** ve **Pointer** kullanarak simüle etmektir.

Proje, gezegenler arası seyahat eden araçları, mürettebatın yaşam döngüsünü ve zamanın göreceli akışını yöneten bir konsol simülasyonudur.

## ⚙️ Teknik Özellikler (Technical Highlights)

Bu projeyi teknik açıdan değerli kılan özellikler:

* **Struct Composition (Yapısal Mimari):**
    * C dilinde sınıf (class) yapısı olmadığı için, `Gezegen` struct'ı temel alınarak `GazDeviGezegen`, `KayacGezegen` gibi özelleşmiş yapılar oluşturulmuştur.
* **Dynamic Memory Management (Bellek Yönetimi):**
    * Tüm nesneler (Araçlar, Kişiler, Gezegenler) çalışma zamanında `malloc` ile dinamik olarak oluşturulur ve simülasyon sonunda `free` ile temizlenir, böylece bellek sızıntısı (memory leak) önlenir.
* **File I/O & Parsing:**
    * `DosyaOkuyucu.c` modülü, metin dosyalarını satır satır okur ve string manipülasyonu ile verileri `struct` yapılarına dönüştürür.
* **Modüler Tasarım:**
    * Her varlık (Arac, Kisi, ZamanHesaplayici) kendi `.c` ve `.h` dosyalarında izole edilmiştir.

## 📦 Dosya Yapısı

* **`uzay_simulasyonu.c`**: `main` fonksiyonunu içeren ve simülasyon döngüsünü (Loop) yöneten ana dosya.
* **`Gezegen.c` / `KayacGezegen.c`...**: Gezegen türleri ve özellikleri.
* **`Arac.c`**: Araçların durumu (`Bekliyor`, `Yolda`, `İMHA`) ve yakıt hesabı.
* **`ZamanHesaplayici.c`**: Gezegenlerin dönüş hızına göre varış sürelerini hesaplayan matematiksel modül.

## 🛠️ Kurulum ve Derleme (Build & Run)

Projeyi derlemek için GCC derleyicisi önerilir.

**1. Derleme (Compile):**
Terminalde proje dizinine gidip şu komutu çalıştırın:
```bash
gcc uzay_simulasyonu.c Arac.c DosyaOkuyucu.c GazDeviGezegen.c Gezegen.c KayacGezegen.c BuzDeviGezegen.c CuceGezegen.c Kisi.c ZamanHesaplayici.c -o SpaceSim
