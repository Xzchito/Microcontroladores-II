#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Definir comunicación Bluetooth en pines 10 (RX) y 11 (TX)
SoftwareSerial BT(10, 11);

LiquidCrystal_I2C lcd(0x27, 16, 2); 

String mensaje = "";  // Variable para almacenar mensaje recibido

void setup() {
    BT.begin(9600);  // Iniciar Bluetooth a 9600 baudios
    lcd.init();
    lcd.backlight();
    lcd.clear();  // Asegurar pantalla en blanco
}

void loop() {
    // Verificar si hay datos recibidos por Bluetooth
    if (BT.available()) {
        mensaje = BT.readString();  // Capturar el mensaje enviado por el dispositivo
        mensaje.trim();  // Limpiar espacios innecesarios
    }

    // Si hay un mensaje recibido, desplazarlo en la pantalla
    if (mensaje.length() > 0) {
        // Aparecer progresivamente desde la derecha
        for (int posicion = 16; posicion >= 0; posicion--) {
            lcd.clear();
            lcd.setCursor(posicion, 0);  
            lcd.print(mensaje.substring(0, min(16, mensaje.length()))); // Muestra parte del mensaje visible
            delay(300);
        }

        // Desplazamiento continuo de derecha a izquierda
        for (int i = 0; i <= mensaje.length(); i++) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(mensaje.substring(i, i + 16)); // Mueve el texto en la pantalla
            delay(400);
        }
    }
}
