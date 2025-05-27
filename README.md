# yilanOyunu
# 🎮 Joystick Kontrollü Yılan Oyunu

Bu proje, **Arduino** ve **Pygame** kullanılarak geliştirilen joystick kontrollü klasik bir *Snake (Yılan)* oyunudur. Oyuncu, fiziksel bir **joystick modülü** üzerinden yılanı yönlendirerek ekran üzerinde yemleri toplamaya çalışır.

## 🧠 Proje Amacı

Bu proje, **gömülü sistemler** ve **Python ile oyun programlama** alanında öğrenme ve uygulama amaçlı geliştirilmiştir. Arduino ile joystick'ten veri okunup, bu veriler Python’daki Pygame kütüphanesi kullanılarak işlenmiştir.

## 🛠️ Kullanılan Teknolojiler

- Arduino UNO
- Joystick modülü
- USB Seri Haberleşme
- Python 3.x
- [Pygame](https://www.pygame.org/)
- Arduino IDE
- VS Code

## 📦 Donanım Gereksinimleri

- Arduino UNO
- Joystick Shield (veya ayrı joystick modülü)
- USB kablosu
- Bilgisayar

## ⚙️ Kurulum ve Çalıştırma

### Arduino Tarafı

1. Arduino IDE’yi aç.
2. `arduino_code.ino` dosyasını yükle.
3. Arduino'ya uygun portu seç ve kodu yükle.

### Python Tarafı

1. Python 3 yüklü değilse indir: https://www.python.org/
2. Gerekli kütüphaneleri yükle:
   ```bash
   pip install pygame pyserial
snake_game.py dosyasını çalıştır:

'''bash

            python snake_game.py
🎮 Oyun Kontrolleri
Joystick konumlarına göre yılan şu şekilde hareket eder:

Yukarı: Y > 600

Aşağı: Y < 100

Sağ: X > 600

Sol: X < 100

Joystick'in orta değeri yaklaşık olarak (318, 326)'dır. Bu değer etrafındaki küçük sapmalar hareket olarak algılanmaz.


👨‍💻 Geliştirici
Ad Soyad: Merve Karagülle

GitHub: @merve-karagulle

Üniversite: Fırat Üniversitesi, Yazılım Mühendisliği

📝 Lisans
Bu proje MIT lisansı ile lisanslanmıştır. Daha fazla bilgi için LICENSE dosyasına göz atabilirsiniz.
