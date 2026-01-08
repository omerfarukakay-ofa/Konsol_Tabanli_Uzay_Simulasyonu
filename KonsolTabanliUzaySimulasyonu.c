#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define GEZEGEN_SAYISI 8
#define PI 3.14159265358979323846

const char *gezegen_isimleri[] = {
    "Merkur", "Venus", "Dunya", "Mars",
    "Jupiter", "Saturn", "Uranus", "Neptun"
};

void menuyu_goster();
double girdi_al_kontrol(char *mesaj);
void sonuclari_yazdir(char **isimler, double *g_degerleri, double sonuc_dunyada, double g_dunya);

// Fonksiyonlar
void serbest_dusme(double *g_ptr, char **p_isim);
void yukari_atis(double *g_ptr, char **p_isim);
void agirlik_deneyi(double *g_ptr, char **p_isim);
void potansiyel_enerji(double *g_ptr, char **p_isim);
void hidrostatik_basinc(double *g_ptr, char **p_isim);
void arsimet_kaldirma(double *g_ptr, char **p_isim);
void basit_sarkac(double *g_ptr, char **p_isim);
void ip_gerilmesi(double *g_ptr, char **p_isim);
void asansor_deneyi(double *g_ptr, char **p_isim);

int main() {
    char bilim_insani[100];
    int secim;

    // Gezegenlerin yerçekim ivmeleri
    // Sirasiyla: Merkür, Venüs, Dünya, Mars, Jüpiter, Satürn, Uranüs, Neptün
    double g_ivmeleri[GEZEGEN_SAYISI] = {3.70, 8.87, 9.80, 3.71, 24.79, 10.44, 8.69, 11.15};

    printf("************************************************\n");
    printf("* UZAY SIMULASYONUNA HOS GELDINIZ        *\n");
    printf("************************************************\n");
    printf("Lutfen Bilim Insani adinizi ve soyadinizi giriniz: ");
    fgets(bilim_insani, 100, stdin);

    bilim_insani[strcspn(bilim_insani, "\n")] = 0;

    printf("\n Hos geldin, Bilim Insani %s.\n", bilim_insani);
    printf("Deneylere baslamak icin haziriz.\n");

    while (1) {
        menuyu_goster();
        printf("\n Seciminiz (Cikis icin -1): ");

        if (scanf("%d", &secim) != 1) {
            // Hatali karakter kontrolu
            while(getchar() != '\n');
            printf("Lutfen gecerli bir sayi giriniz!\n");
            continue;
        }

        if (secim == -1) {
            printf("Simulasyon sonlandiriliyor. Gorusmek uzere %s!\n", bilim_insani);
            break;
        }

        // Pointer ile diziye erisim için dizinin baslangiç adresi
        switch (secim) {
            case 1: serbest_dusme(g_ivmeleri, (char **)gezegen_isimleri); break;
            case 2: yukari_atis(g_ivmeleri, (char **)gezegen_isimleri); break;
            case 3: agirlik_deneyi(g_ivmeleri, (char **)gezegen_isimleri); break;
            case 4: potansiyel_enerji(g_ivmeleri, (char **)gezegen_isimleri); break;
            case 5: hidrostatik_basinc(g_ivmeleri, (char **)gezegen_isimleri); break;
            case 6: arsimet_kaldirma(g_ivmeleri, (char **)gezegen_isimleri); break;
            case 7: basit_sarkac(g_ivmeleri, (char **)gezegen_isimleri); break;
            case 8: ip_gerilmesi(g_ivmeleri, (char **)gezegen_isimleri); break;
            case 9: asansor_deneyi(g_ivmeleri, (char **)gezegen_isimleri); break;
            default: printf("Gecersiz secim! Lutfen 1-9 arasi bir deger girin.\n");
        }
    }

    return 0;
}

void menuyu_goster() {
    printf("\n--- DENEY LISTESI ---\n");
    printf("1. Serbest Dusme Deneyi\n");
    printf("2. Yukari Atis Deneyi\n");
    printf("3. Agirlik Deneyi\n");
    printf("4. Kutlecekimsel Potansiyel Enerji Deneyi\n");
    printf("5. Hidrostatik Basinc Deneyi\n");
    printf("6. Arsimet Kaldirma Kuvveti Deneyi\n");
    printf("7. Basit Sarkac Periyodu Deneyi\n");
    printf("8. Sabit Ip Gerilmesi Deneyi\n");
    printf("9. Asansor Deneyi\n");
}

double girdi_al_kontrol(char *mesaj) {
    double deger;
    printf("%s", mesaj);
    scanf("%lf", &deger);

    // Negatif girilirse mutlak degerini al
    double sonuc = (deger < 0) ? -deger : deger;

    if (deger < 0) {
        printf("UYARI: Negatif deger girildi! Mutlak degeri (%.2f) baz alinacaktir.\n", sonuc);
    }
    return sonuc;
}

// 1. Serbest Dusme: h = 0.5 * g * t^2
void serbest_dusme(double *g_ptr, char **p_isim) {
    printf("\n--- 1. Serbest Dusme Deneyi ---\n");
    double t = girdi_al_kontrol("Dusus suresi (saniye): ");

    printf("\nTum Gezegenler icin Dusulen Mesafe (h - Metre):\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        // Pointer aritmetigi ile dizi erisimi: *(g_ptr + i)
        double g = *(g_ptr + i);
        double h = 0.5 * g * t * t;
        printf("%-10s: %.2f m\n", *(p_isim + i), h);
    }
}

// 2. Yukari Atis: h_max = v0^2 / (2*g)
void yukari_atis(double *g_ptr, char **p_isim) {
    printf("\n--- 2. Yukari Atis Deneyi ---\n");
    double v0 = girdi_al_kontrol("Firlatma hizi (m/s): ");

    printf("\nTum Gezegenler icin Maksimum Yukseklik (h_max - Metre):\n");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(g_ptr + i);
        double h_max = (v0 * v0) / (2 * g);
        printf("%-10s: %.2f m\n", *(p_isim + i), h_max);
    }
}

// 3. Agirlikk: G = m * g
void agirlik_deneyi(double *g_ptr, char **p_isim) {
    printf("\n--- 3. Agirlik Deneyi ---\n");
    double m = girdi_al_kontrol("Cismin kutlesi (kg): ");

    printf("\nTum Gezegenler icin Agirlik (G - Newton):\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(g_ptr + i);
        double agirlik = m * g;
        printf("%-10s: %.2f N\n", *(p_isim + i), agirlik);
    }
}

// 4. Potansiyel Enerji: Ep = m * g * h
void potansiyel_enerji(double *g_ptr, char **p_isim) {
    printf("\n--- 4. Kutlecekimsel Potansiyel Enerji Deneyi ---\n");
    double m = girdi_al_kontrol("Cismin kutlesi (kg): ");
    double h = girdi_al_kontrol("Yukseklik (m): ");

    printf("\nTum Gezegenler icin Potansiyel Enerji (Ep - Joule):\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(g_ptr + i);
        double ep = m * g * h;
        printf("%-10s: %.2f J\n", *(p_isim + i), ep);
    }
}

// 5. Hidrostatik Basinç: P = rho * g * h
void hidrostatik_basinc(double *g_ptr, char **p_isim) {
    printf("\n--- 5. Hidrostatik Basinc Deneyi ---\n");
    double rho = girdi_al_kontrol("Sivinin yogunlugu (kg/m^3): ");
    double h = girdi_al_kontrol("Derinlik (m): ");

    printf("\nTum Gezegenler icin Hidrostatik Basinc (P - Pascal):\n");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(g_ptr + i);
        double p = rho * g * h;
        printf("%-10s: %.2f Pa\n", *(p_isim + i), p);
    }
}

// 6. Arsimet Kaldirma Kuvveti: Fk = rho * g * V
void arsimet_kaldirma(double *g_ptr, char **p_isim) {
    printf("\n--- 6. Arsimet Kaldirma Kuvveti Deneyi ---\n");
    double rho = girdi_al_kontrol("Sivinin yogunlugu (kg/m^3): ");
    double V = girdi_al_kontrol("Batan hacim (m^3): ");

    printf("\nTum Gezegenler icin Kaldirma Kuvveti (Fk - Newton):\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(g_ptr + i);
        double fk = rho * g * V;
        printf("%-10s: %.2f N\n", *(p_isim + i), fk);
    }
}

// 7. Basit Sarkac: T = 2 * pi * sqrt(L / g)
void basit_sarkac(double *g_ptr, char **p_isim) {
    printf("\n--- 7. Basit Sarkac Periyodu Deneyi ---\n");
    double L = girdi_al_kontrol("Sarkac uzunlugu (m): ");

    printf("\nTum Gezegenler icin Periyot (T - Saniye):\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(g_ptr + i);
        double t_periyot = 2 * PI * sqrt(L / g);
        printf("%-10s: %.2f s\n", *(p_isim + i), t_periyot);
    }
}

// 8. ip Gerilmesi: T = m * g
void ip_gerilmesi(double *g_ptr, char **p_isim) {
    printf("\n--- 8. Sabit Ip Gerilmesi Deneyi ---\n");
    double m = girdi_al_kontrol("Cismin kutlesi (kg): ");

    printf("\nTum Gezegenler icin Ip Gerilmesi (T - Newton):\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(g_ptr + i);
        double t_kuvvet = m * g;
        printf("%-10s: %.2f N\n", *(p_isim + i), t_kuvvet);
    }
}

// 9. Asansor Deneyi: N = m(g+a) veya N = m(g-a)
void asansor_deneyi(double *g_ptr, char **p_isim) {
    printf("\n--- 9. Asansor Deneyi ---\n");
    printf("Asansorun hareket yonunu seciniz:\n");
    printf("1. Yukari Hizlanan veya Asagi Yavaslayan (1)\n");
    printf("2. Asagi Hizlanan veya Yukari Yavaslayan (2)\n");

    int yon_secimi;
    scanf("%d", &yon_secimi);

    double a = girdi_al_kontrol("Asansor ivmesi (m/s^2): ");
    double m = girdi_al_kontrol("Cismin kutlesi (kg): ");

    printf("\nTum Gezegenler icin Etkin Agirlik (N - Newton):\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(g_ptr + i);
        double N;

        if (yon_secimi == 1) {
            N = m * (g + a);
        } else {
            N = m * (g - a);

        }


        printf("%-10s: %.2f N\n", *(p_isim + i), N);
    }
}
