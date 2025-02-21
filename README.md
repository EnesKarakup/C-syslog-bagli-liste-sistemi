# Syslog Kayıtlarını Tek Yönlü Bağlı Liste ile Yönetme (C)

## Açıklama
Bu proje, Linux sistemlerinde syslog mekanizmasından elde edilen log verilerini C dilinde yazılmış bir program aracılığıyla **tek yönlü bağlı liste** kullanarak saklayan,
ekrana yazdıran ve bellek yönetimini sağlayan bir uygulamadır. 

## Özellikler
- **Syslog Okuma:** Varsayılan olarak `/var/log/syslog` dosyasından log kayıtlarını okur.
- **Dinamik Veri Yapısı:** Tek yönlü bağlı liste ile log kayıtları tutulur.
- **Bellek Yönetimi:** Dinamik olarak tahsis edilen bellek program sonunda serbest bırakılır.
- **C Dili ile Uygulama:** Linux sistemlerinde `GCC` derleyicisi ile çalıştırılabilir.

## Gereksinimler
- **Linux işletim sistemi** (Syslog dosyasına erişim için `/var/log/syslog` olmalıdır.)
- **GCC veya uyumlu bir C derleyicisi(C lion vb.)**

## Kurulum ve Derleme

Projeyi derlemek için aşağıdaki adımları takip edin:

1. Terminali açın ve projenin olduğu dizine gidin:
  ```
  cd c-syslog-bagli-liste-sistemi
  ```
2. GCC ile kodu derleyin:
  ```
  gcc -o syslog_parser main.c
  ```
3. Uygulamayı çalıştırın:
  ```
  ./syslog_parser
  ```
**Not:** Eğer derleme sırasında `Permission denied ` hatası alırsanız, `chmod +x syslog_parser ` komutunu çalıştırarak çalıştırılabilir hale getirin.

## Kullanım
Derleme tamamlandıktan sonra uygulamayı çalıştırmak için:
```
./syslog_parser
```
**Not:** Program ```/var/log/syslog``` dosyasını okumaya çalışır.
Eğer sisteminizde farklı bir log dosyası kullanılıyorsa, ```main.c``` içerisindeki dosya yolunu güncellemeniz gerekebilir.

## Örnek Çıktı

Program çalıştırıldığında aşağıdaki gibi bir çıktı üretebilir:

```
[INFO]     Feb 20 14:23:45 myhost systemd: Starting User Manager for UID 1000...
[WARNING]  Feb 20 14:24:00 myhost kernel: CPU temperature high!
[ERROR]    Feb 20 14:24:15 myhost sshd: Failed password attempt for user root
```


## Proje Yapısı
```
c-syslog-bagli-liste-sistemi/
├── main.c           # Ana kaynak kodu dosyası (C dilinde syslog kayıtlarını bağlı liste ile işleme)
└── README.md        # Proje açıklamalarını içeren dosya
```

## Lisans
Bu proje, özgürce kullanılabilir ve paylaşılabilir. Kodu değiştirebilir, geliştirebilir ve ticari olmayan projelerinizde kullanabilirsiniz.
Ancak, projenin yazarı olarak her zaman yazarı belirtmeniz rica olunur. 
