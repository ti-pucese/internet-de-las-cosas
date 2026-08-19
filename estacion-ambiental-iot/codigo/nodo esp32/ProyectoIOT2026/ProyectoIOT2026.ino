#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <WebServer.h> 
#include <DHT.h>

// Complementos de Firebase
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

// CREDENCIALES 
#define WIFI_SSID "TU_RED_WIFI"
#define WIFI_PASSWORD "TU_CLAVE_WIFI"
#define API_KEY "TU_FIREBASE_API_KEY"
#define DATABASE_URL "https://tu-proyecto.firebaseio.com"
#define USER_EMAIL "correo_del_esp32@ejemplo.com"
#define USER_PASSWORD "clave_esp32"


// Configuración
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Instancia del servidor web en el puerto 80
WebServer server(80);

const byte encoderPin = 27;
const int ranuras = 20;
volatile unsigned long pulsos = 0;

// Temporizadores
unsigned long t0 = 0;          // Temporizador para datos en vivo (2 segundos)
unsigned long t_historial = 0; // Temporizador para el historial (60 segundos)

int firebase_listo = 0; // 0 = No conectado, 1 = Conectado

// Variables globales de lectura
float last_temp = 0.0;
float last_velkmh = 0.0;
float last_pres = 0.0;
float last_alt = 0.0;
float last_hum = 0.0; 

void IRAM_ATTR contar() { pulsos++; }

// Función que genera la página web local
void handleRoot() {
  String html = "<!DOCTYPE html><html lang=\"es\"><head><meta charset=\"UTF-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>Estación Local</title>";
  html += "<meta http-equiv=\"refresh\" content=\"2\">";
  html += "<style>";
  html += "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background-color: #f4f7f6; text-align: center; color: #333; padding: 20px;}";
  html += ".card { background: white; border-radius: 10px; padding: 20px; width: 200px; display: inline-block; margin: 10px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }";
  html += "h2 { font-size: 1.2rem; color: #7f8c8d; margin: 0; }";
  html += ".value { font-size: 2.5rem; font-weight: bold; margin: 10px 0; }";
  html += "</style></head><body>";
  
  html += "<h1>Dashboard Local (ESP32)</h1>";
  html += "<div>";
  
  html += "<div class=\"card\"><h2>Temperatura</h2>";
  html += "<div class=\"value\" style=\"color: #e74c3c;\">" + String(last_temp, 1) + " <span style=\"font-size:1rem;color:#95a5a6;\">°C</span></div></div>";
  
  html += "<div class=\"card\"><h2>Humedad</h2>";
  html += "<div class=\"value\" style=\"color: #3498db;\">" + String(last_hum, 1) + " <span style=\"font-size:1rem;color:#95a5a6;\">%</span></div></div>";

  html += "<div class=\"card\"><h2>Viento</h2>";
  html += "<div class=\"value\" style=\"color: #2ecc71;\">" + String(last_velkmh, 1) + " <span style=\"font-size:1rem;color:#95a5a6;\">km/h</span></div></div>";
  
  html += "<div class=\"card\"><h2>Presión</h2>";
  html += "<div class=\"value\" style=\"color: #34495e;\">" + String(last_pres, 1) + " <span style=\"font-size:1rem;color:#95a5a6;\">hPa</span></div></div>";

  html += "<div class=\"card\"><h2>Altitud</h2>";
  html += "<div class=\"value\" style=\"color: #9b59b6;\">" + String(last_alt, 1) + " <span style=\"font-size:1rem;color:#95a5a6;\">m</span></div></div>";
  
  html += "</div></body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 no encontrado. Revisa conexiones.");
    while (1) { delay(100); }
  }

  // Inicializar sensor DHT22
  dht.begin();

  pinMode(encoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPin), contar, CHANGE);

  // 1. Conexión WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConectado a WiFi!");
  Serial.print("IP del servidor local: http://");
  Serial.println(WiFi.localIP());

  // 2. Configurar y arrancar Servidor Web Local
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Servidor Web Local iniciado.");

  // 3. Configuración de Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Asignar el callback de token
  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  server.handleClient(); 

  // Verificar estado de Firebase
  if (Firebase.ready()) {
    firebase_listo = 1;
  } else {
    firebase_listo = 0;
  }

  // LECTURA Y ACTUALIZACIÓN EN VIVO (CADA 2 SEGUNDOS)

  if (millis() - t0 >= 2000) {
    noInterrupts();
    unsigned long p = pulsos;
    pulsos = 0;
    interrupts();

    float rps = (float)p / ranuras;
    
    // Lecturas de sensores
    last_velkmh = (2 * PI * 0.05 * rps) * 3.6;
    last_temp = bmp.readTemperature(); 
    last_pres = bmp.readPressure() / 100.0;
    last_alt = bmp.readAltitude(1013.25);
    
    float h = dht.readHumidity();
    if (!isnan(h)) {
      last_hum = h;
    }
    
    Serial.printf("En vivo -> Temp: %.1f C | Hum: %.1f %% | Viento: %.1f km/h | Pres: %.1f hPa\n", last_temp, last_hum, last_velkmh, last_pres);

    // Enviar sobrescribiendo 'estacion/actual'
    if (firebase_listo == 1) {
      Firebase.RTDB.setFloat(&fbdo, "estacion/actual/temperatura", last_temp);
      Firebase.RTDB.setFloat(&fbdo, "estacion/actual/humedad", last_hum); 
      Firebase.RTDB.setFloat(&fbdo, "estacion/actual/viento", last_velkmh);
      Firebase.RTDB.setFloat(&fbdo, "estacion/actual/presion", last_pres);
      Firebase.RTDB.setFloat(&fbdo, "estacion/actual/altitud", last_alt); 
    }
    
    t0 = millis();
  }

  //GUARDADO DE HISTORIAL (CADA 60 SEGUNDOS)

  if (millis() - t_historial >= 60000) {
    if (firebase_listo == 1) {
      Serial.println(">>> Guardando paquete en el historial de Firebase...");
      
      // Construir el paquete JSON
      FirebaseJson json;
      json.set("temperatura", last_temp);
      json.set("humedad", last_hum);
      json.set("viento", last_velkmh);
      json.set("presion", last_pres);
      json.set("altitud", last_alt);
      
      // Inyectar el timestamp del servidor de Google
      FirebaseJson timestampJson;
      timestampJson.set(".sv", "timestamp");
      json.set("timestamp", timestampJson);
      
      // Enviar usando pushJSON a 'estacion/historial'
      if (Firebase.RTDB.pushJSON(&fbdo, "estacion/historial", &json)) {
        Serial.println(">>> Historial guardado correctamente.");
      } else {
        Serial.println(">>> Error al guardar historial: " + fbdo.errorReason());
      }
    }
    t_historial = millis();
  }
}