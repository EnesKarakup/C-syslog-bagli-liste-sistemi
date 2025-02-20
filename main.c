#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maksimum satır uzunluğu tanımı
#define SATIR_MAX 1024

// Syslog kaydı için bağlı liste düğüm yapısı
typedef struct SyslogKayit {
    char *mesaj;                   // Log mesajı metni
    struct SyslogKayit *sonraki;    // Bir sonraki kaydı gösteren işaretçi
} SyslogKayit;

/*
 * Fonksiyon: yeniKayitOlustur
 * Amacı: Girilen satır metninden yeni bir syslog kaydı düğümü oluşturmak.
 * Parametre: satir - syslog kaydı olarak eklenecek metin.
 * Dönüş Değeri: Oluşturulan syslog kaydı düğümünün adresi.
 */
SyslogKayit *yeniKayitOlustur(const char *satir) {
    SyslogKayit *yeniDugum = (SyslogKayit *)malloc(sizeof(SyslogKayit));
    if (!yeniDugum) {
        perror("Bellek tahsis hatası (dugum)");
        exit(EXIT_FAILURE);
    }
    // Satırın kopyasını oluşturuyoruz
    yeniDugum->mesaj = strdup(satir);
    if (!yeniDugum->mesaj) {
        perror("Bellek tahsis hatası (mesaj)");
        free(yeniDugum);
        exit(EXIT_FAILURE);
    }
    yeniDugum->sonraki = NULL;
    return yeniDugum;
}

/*
 * Fonksiyon: kayitEkle
 * Amacı: Yeni syslog kaydını bağlı listenin sonuna eklemek.
 * Parametreler:
 *   - bas: Listenin başlangıcını gösteren işaretçi adresi.
 *   - satir: Eklenecek syslog satırı metni.
 */
void kayitEkle(SyslogKayit **bas, const char *satir) {
    SyslogKayit *yeniDugum = yeniKayitOlustur(satir);
    if (*bas == NULL) {
        // Liste boşsa, yeni düğüm doğrudan başlangıç olur.
        *bas = yeniDugum;
    } else {
        // Listenin sonuna giderek yeni düğümü ekleriz.
        SyslogKayit *gecici = *bas;
        while (gecici->sonraki != NULL) {
            gecici = gecici->sonraki;
        }
        gecici->sonraki = yeniDugum;
    }
}

/*
 * Fonksiyon: listeyiYazdir
 * Amacı: Bağlı listedeki tüm syslog kayıtlarını ekrana yazdırmak.
 * Parametre: bas - Listenin başlangıcını gösteren işaretçi.
 */
void listeyiYazdir(SyslogKayit *bas) {
    while (bas != NULL) {
        printf("%s", bas->mesaj);
        bas = bas->sonraki;
    }
}

/*
 * Fonksiyon: listeyiSerbestBirak
 * Amacı: Bağlı listedeki tüm düğümleri ve mesajlarını serbest bırakmak (belleği temizlemek).
 * Parametre: bas - Listenin başlangıcını gösteren işaretçi.
 */
void listeyiSerbestBirak(SyslogKayit *bas) {
    while (bas != NULL) {
        SyslogKayit *gecici = bas;
        bas = bas->sonraki;
        free(gecici->mesaj);
        free(gecici);
    }
}

/*
 * Fonksiyon: main
 * Amacı: Programın başlangıç noktası; syslog dosyasını okuyup, verileri bağlı listeye ekler,
 *         daha sonra listeyi ekrana yazdırır ve belleği temizler.
 */
int main() {
    FILE *dosya;
    char satir[SATIR_MAX];
    SyslogKayit *kayitListesi = NULL;

    // Syslog dosyasının yolu; sistemden sisteme farklılık gösterebilir.
    // Örneğin: Ubuntu'da genellikle "/var/log/syslog" kullanılır.
    const char *dosyaYolu = "/var/log/syslog";

    // Syslog dosyasını okuma modunda açarız.
    dosya = fopen(dosyaYolu, "r");
    if (dosya == NULL) {
        perror("Dosya açılamadı");
        return EXIT_FAILURE;
    }

    // Dosyadan satır satır okuyup, her bir satırı bağlı listeye ekleriz.
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        kayitEkle(&kayitListesi, satir);
    }

    // Dosya kapatılır.
    fclose(dosya);

    // Oluşturulan syslog kayıtları ekrana yazdırılır.
    listeyiYazdir(kayitListesi);

    // Kullanılan bellek temizlenir.
    listeyiSerbestBirak(kayitListesi);

    return EXIT_SUCCESS;
}
