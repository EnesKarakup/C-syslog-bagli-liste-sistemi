# C-syslog-bagli-liste-sistemi
 /*  * main.c  *   * Bu dosya, Linux işletim sistemlerinde syslog kayıtlarını okuyarak tek yönlü bağlı liste veri yapısına ekleyen bir C programının ana kaynak dosyasıdır.  * Program, /var/log/syslog dosyasındaki her satır için yeni bir kayıt oluşturur ve bu kayıtları bağlı listeye ekler.   * Ayrıca, log verilerinin ekrana sırasıyla yazdırılması ve belleğin doğru bir şekilde yönetilmesi sağlanır.  *   * Özellikler:  * - Syslog verilerinin dinamik olarak işlenmesi.  * - Bağlı liste veri yapısı kullanılarak log kayıtlarının sıralı şekilde saklanması.  * - Bellek yönetimi ile ilgili serbest bırakma işlemleri.  */
