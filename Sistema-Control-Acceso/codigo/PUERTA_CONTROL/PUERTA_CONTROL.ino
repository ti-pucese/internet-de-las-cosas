#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Servo.h> // https://madhephaestus.github.io/ESP32Servo/annotated.html
#include "SinricPro.h" // https://github.com/sinricpro/esp8266-esp32-sdk.git
#include "SinricProLock.h" 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>// https://github.com/johnrickman/LiquidCrystal_I2C.git
// Credenciales de Sinric Pro
#define APP_KEY    ""
#define APP_SECRET ""
#define LOCK_ID    ""

// Datos de la red Wi-Fi
const char* ssid = "";
const char* password = "";

// Pines utilizados
const int pinServo  = 18; // Servomotor
const int pinRele   = 26; // Módulo Relé
const int pinRDM_RX = 16; // RX2 para lector RDM6300
const int pinSDA    = 21; // SDA para pantalla LCD I2C
const int pinSCL    = 22; // SCL para pantalla LCD I2C

// Posiciones del servomotor
const int POS_CERRADO = 0;
const int POS_ABIERTO = 90;
// BASE DE DATOS DE TARJETAS AUTORIZADAS
String tarjetasAceptadas[] = {
  "0000961260",   // Número impreso en decimal
  "02000EAAEC4A", // Trama cruda recibida del RDM6300
  "EA6EC",        // Valor Hexadecimal
  "AAEC"          // Subcadena
};

// OBJETOS Y VARIABLES GLOBALES
LiquidCrystal_I2C lcd(0x27, 16, 2); 
HardwareSerial rfidSerial(2);        
Servo miServo;
String tagRaw = "";
// Variables de estado y temporización 
bool estadoBloqueado = true;          // true = CERRADO, false = ABIERTO
unsigned long tiempoApertura = 0;     // Marca de tiempo cuando se abrió
const unsigned long TIEMPO_AUTOCIERRE = 15000; // 15 segundos para el autocierre
bool autoCierrePendiente = false;
// FUNCIONES AUXILIARES Y DE CONTROL
bool esTarjetaAceptada(String tag) {
  tag.trim();
  int totalTarjetas = sizeof(tarjetasAceptadas) / sizeof(tarjetasAceptadas[0]);
  for (int i = 0; i < totalTarjetas; i++) {
    if (tag.indexOf(tarjetasAceptadas[i]) != -1) {
      return true;
    }
  }
  return false;
}

void actualizarPantallaEspera() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Esperando");
  lcd.setCursor(0, 1);
  lcd.print("tarjeta...");
}

void ejecutarMovimientoMecanico(bool bloquear, String origen = "") {
  miServo.attach(pinServo, 500, 2500);
  estadoBloqueado = bloquear;

  lcd.clear();
  if (bloquear) {
    Serial.println("Estado: CERRANDO PUERTA");
    lcd.setCursor(0, 0);
    lcd.print("Puerta: CERRADA");
    if (origen != "") {
      lcd.setCursor(0, 1);
      lcd.print(origen);
    }
    digitalWrite(pinRele, HIGH); // Apaga relé
    miServo.write(POS_CERRADO);
  } else {
    Serial.println("Estado: ABRIENDO PUERTA");
    lcd.setCursor(0, 0);
    lcd.print("Acceso Permitido");
    if (origen != "") {
      lcd.setCursor(0, 1);
      lcd.print(origen);
    }
    digitalWrite(pinRele, LOW);  // Enciende relé
    miServo.write(POS_ABIERTO);
  }
  
  delay(600); // Pequeña pausa no crítica solo para mover el motor
  miServo.detach();
}

// Abrir cerradura y programar auto-cierre
void abrirPuerta(String origen) {
  ejecutarMovimientoMecanico(false, origen);
  tiempoApertura = millis();
  autoCierrePendiente = true;
}

// Cerrar cerradura
void cerrarPuerta(String origen) {
  ejecutarMovimientoMecanico(true, origen);
  autoCierrePendiente = false;
  delay(1500);
  actualizarPantallaEspera();
}

// CALLBACK DE SINRIC PRO / ALEXA
bool onLockState(const String &deviceId, bool &lockState) {
  Serial.print("Comando Sinric Pro recibido -> ");
  
  if (lockState == false) { 
    // Solicitud de Desbloqueo (Abrir)
    Serial.println("DESBLOQUEAR");
    abrirPuerta("App / Alexa");
    // Notificamos respuesta inmediata a Sinric Pro
  } else { 
    // Solicitud de Bloqueo (Cerrar manual)
    Serial.println("BLOQUEAR");
    cerrarPuerta("App / Alexa");
    SinricProLock &myLock = SinricPro[LOCK_ID];
    myLock.sendLockStateEvent(true);
  }

  return true; // Responde al instante a la nube sin demoras
}

// SETUP
void setup() {
  Serial.begin(115200);

  Wire.begin(pinSDA, pinSCL);
  lcd.init();
  lcd.backlight();
  actualizarPantallaEspera();

  rfidSerial.begin(9600, SERIAL_8N1, pinRDM_RX, -1);

  pinMode(pinRele, OUTPUT);
  digitalWrite(pinRele, HIGH); 

  miServo.attach(pinServo, 500, 2500);
  miServo.write(POS_CERRADO);
  delay(500);
  miServo.detach();

  Serial.println("Conectando a Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n¡Wi-Fi Conectado exitosamente!");

  SinricProLock &myLock = SinricPro[LOCK_ID];
  myLock.onLockState(onLockState);
  SinricPro.begin(APP_KEY, APP_SECRET);

  actualizarPantallaEspera();
}
// LOOP PRINCIPAL
void loop() {
  // Mantiene viva la conexión con Sinric Pro sin interrupciones
  SinricPro.handle();
  // LÓGICA DE AUTO-CIERRE AUTOMÁTICO 
  if (autoCierrePendiente && (millis() - tiempoApertura >= TIEMPO_AUTOCIERRE)) {
    Serial.println("Ejecutando Auto-Cierre de seguridad...");
    
    // 1. Cierra físicamente el cerrojo
    cerrarPuerta("Auto-Cierre");

    // 2. Notifica el estado 'CERRADO' a Sinric Pro 
    SinricProLock &myLock = SinricPro[LOCK_ID];
    myLock.sendLockStateEvent(true);
  }
  // LECTURA DEL LECTOR RFID
  while (rfidSerial.available() > 0) {
    byte c = rfidSerial.read();

    if (c == 0x02) { 
      tagRaw = ""; 
    } else if (c == 0x03) { 
      if (tagRaw.length() >= 10) {
        Serial.print("ID leido: ");
        Serial.println(tagRaw);

        if (esTarjetaAceptada(tagRaw)) {
          // Abrir por Tarjeta
          abrirPuerta("Tarjeta Ok");

          // Notifica de inmediato a Sinric Pro 
          SinricProLock &myLock = SinricPro[LOCK_ID];
          myLock.sendLockStateEvent(false);

        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("ID: " + tagRaw.substring(0, 10));
          lcd.setCursor(0, 1);
          lcd.print("Tarjeta Invalida");
          delay(2000);
          actualizarPantallaEspera();
        }

        while (rfidSerial.available()) rfidSerial.read();
      }
    } else {
      if (c != '\r' && c != '\n') {
        tagRaw += (char)c;
      }
    }
  }
}
