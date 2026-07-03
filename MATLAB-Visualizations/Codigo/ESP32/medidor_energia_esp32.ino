#include <WiFi.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <PZEM004Tv30.h>

// Pines y Configuración
#define RXD216
#define TXD217
#define SEND_INTERVAL20000 // Intervalo de Envio a TS

constchar* wifi_ssid = "LAB_MEL";
constchar* wifi_pass = "Mel_1981";
constchar* ap_ssid = "MonitorEnergia_ESP32";
constchar* ap_pass = "12345678";
constchar* apiKey = "2BELFH2ESRXAKIJG";

HardwareSerial pzemSerial(2);
PZEM004Tv30 pzem(pzemSerial, RXD2, TXD2);

AsyncWebServer server(80);
unsignedlong lastSend = 0;

// Estructura para organizar los datos
struct EnergyData {
float v, c, p, e, f, fp;
} data;

// Función para leer el sensor de forma segura
voidreadPZEM() {
data.v = pzem.voltage();
data.c = pzem.current();
data.p = pzem.power();
data.e = pzem.energy();
data.f = pzem.frequency();
data.fp = pzem.pf();

 // Limpiar valores NAN para evitar errores en JSON/ThingSpeak
 if(isnan(data.v)) data.v = 0;
 if(isnan(data.c)) data.c = 0;
 if(isnan(data.p)) data.p = 0;
 if(isnan(data.e)) data.e = 0;
 if(isnan(data.f)) data.f = 0;
 if(isnan(data.fp)) data.fp = 0;
}

constchar index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
 <meta name="viewport" content="width=device-width, initial-scale=1">
 <meta charset="UTF-8">
 <title>Power Dash v2</title>
 <style>
 body { background: #0f0f13; color: #e0e0e0; font-family: 'Segoe UI', sans-serif; margin: 0; padding: 20px; }
 .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(150px, 1fr)); gap: 15px; max-width: 800px; margin: 0 auto; }
 .card { background: #1e1e26; padding: 20px; border-radius: 12px; border-bottom: 4px solid #00f2ff; box-shadow: 0 4px 15px rgba(0,0,0,0.3); }
 .val { font-size: 1.8em; font-weight: bold; color: #fff; display: block; margin-top: 10px; }
 .unit { font-size: 0.5em; color: #00f2ff; margin-left: 5px; }
 h2 { text-align: center; color: #00f2ff; letter-spacing: 2px; }
 .status { font-size: 0.8em; text-align: center; margin-bottom: 20px; color: #666; }
 </style>
</head>
<body>
 <h2>ENERGY MONITOR</h2>
 <div class="status" id="st">Iniciando...</div>
 <div class="grid">
 <div class="card">Voltaje<span class="val" id="v">0<span class="unit">V</span></span></div>
 <div class="card">Corriente<span class="val" id="c">0<span class="unit">A</span></span></div>
 <div class="card">Potencia<span class="val" id="p">0<span class="unit">W</span></span></div>
 <div class="card">Energía<span class="val" id="e">0<span class="unit">kWh</span></span></div>
 <div class="card">Frecuencia<span class="val" id="f">0<span class="unit">Hz</span></span></div>
 <div class="card">Factor P.<span class="val" id="fp">0</span></div>
 </div>
 <script>
 setInterval(() => {
 fetch("/data").then(r => r.json()).then(d => {
 document.getElementById("v").innerHTML = d.v + '<span class="unit">V</span>';
 document.getElementById("c").innerHTML = d.c + '<span class="unit">A</span>';
 document.getElementById("p").innerHTML = d.p + '<span class="unit">W</span>';
 document.getElementById("e").innerHTML = d.e + '<span class="unit">kWh</span>';
 document.getElementById("f").innerHTML = d.f + '<span class="unit">Hz</span>';
 document.getElementById("fp").innerText = d.fp;
 document.getElementById("st").innerText = "Actualizado: " + new Date().toLocaleTimeString();
 }).catch(e => document.getElementById("st").innerText = "Error de conexión");
 }, 2000);
 </script>
</body>
</html>
)rawliteral";

voidsetup(){
Serial.begin(115200);
pzemSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);

 // Configuración de Red Híbrida
WiFi.mode(WIFI_AP_STA);
WiFi.softAP(ap_ssid, ap_pass);
WiFi.begin(wifi_ssid, wifi_pass);

Serial.println("Iniciando puntos de acceso...");

server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
req->send_P(200, "text/html", index_html);
 });

server.on("/data", HTTP_GET, [](AsyncWebServerRequest *req){
readPZEM();
 String json = "{";
 json += "\"v\":" + String(data.v, 1) + ",";
 json += "\"c\":" + String(data.c, 2) + ",";
 json += "\"p\":" + String(data.p, 1) + ",";
 json += "\"e\":" + String(data.e, 3) + ",";
 json += "\"f\":" + String(data.f, 1) + ",";
 json += "\"fp\":" + String(data.fp, 2);
 json += "}";
req->send(200, "application/json", json);
 });

server.begin();
Serial.println("Servidores activos.");
}

voidloop(){
 // Envío a ThingSpeak cada N milisegundos
 if(millis() - lastSend > SEND_INTERVAL){
 lastSend = millis();

 if(WiFi.status() == WL_CONNECTED){
readPZEM();

 HTTPClient http;
 String url = "http://api.thingspeak.com/update?api_key=" + String(apiKey) +
"&field1=" + String(data.v) + "&field2=" + String(data.c) +
"&field3=" + String(data.p) + "&field4=" + String(data.e) +
"&field5=" + String(data.f) + "&field6=" + String(data.fp);

http.begin(url);
int httpCode = http.GET();
 if(httpCode > 0) Serial.println("ThingSpeak: OK");
 else Serial.println("Error en envío");
http.end();
 } else {
Serial.println("Sin conexión WiFi para ThingSpeak...");
 }
 }
}