
# Diseño e Implementación de un Sistema IoT de Control de Acceso Remoto para Laboratorios Universitarios Basado en ESP32 y Servicios en la Nube

## 2. Descripción del proyecto
El presente proyecto aborda las limitaciones operativas de las llaves mecánicas tradicionales en laboratorios universitarios, tales como retrasos, pérdida de llaves y la dificultad para gestionar el ingreso de los usuarios. Con el propósito de desarrollar un prototipo de control de acceso basado en Internet de las Cosas (IoT), el sistema integra autenticación presencial mediante tarjeta RFID y control remoto a través de Amazon Alexa, mejorando significativamente la seguridad y la administración de los espacios. Como solución desarrollada, se implementó un sistema embebido basado en ESP32 que agrupa autenticación RFID de 125 kHz, un servomotor para el control del pestillo, comunicación Wi-Fi mediante la plataforma SinricPro y un registro detallado de eventos. Todo este conjunto tecnológico se orienta a un contexto de aplicación enfocado en la seguridad electrónica y la automatización en laboratorios académicos.

## 3. Integrantes
* **Nombres completos:** Grace Johamy Contreras Montaño, Jersson Delgado Quintero
* **Carrera:** Tecnologías de la Información
* **Institución:** Pontificia Universidad Católica del Ecuador Sede Esmeraldas (PUCE-SE)
* **Asignatura:** Internet de las Cosas
* **Docente:** Mgt. Manuel Nevárez Toledo

## 4. Objetivos
### 4.1 Objetivo general
Diseñar e implementar un prototipo IoT de control de acceso para laboratorios académicos mediante autenticación local y administración remota.

### 4.2 Objetivos específicos
* Integrar autenticación presencial mediante lector RFID RDM6300.
* Implementar control remoto y monitoreo mediante la plataforma SinricPro y Amazon Alexa.
* Desarrollar un mecanismo de autocierre no bloqueante y registro histórico de eventos.

## 5. Arquitectura del sistema
![Diagrama de Arquitectura](evidencias/Arquitectura.png)

## 6. Hardware utilizado

| Dispositivo | Modelo | Fabricante | Función | Enlace |
| :--- | :--- | :--- | :--- | :--- |
| Microcontrolador | ESP32-WROOM-32 | Espressif | Procesamiento y conectividad Wi-Fi | [Espressif](https://www.espressif.com/) |
| Lector RFID | RDM6300 | — | Identificación de credenciales (125 kHz) | — |
| Servomotor | MG996R | Tower Pro | Accionamiento mecánico del pestillo | — |
| Pantalla LCD | 16x2 I2C | — | Visualización del estado del sistema | — |
| Módulo Relé | Relé 1 canal | — | Control del estado de acceso (5V DC) | — |

## 7. Materiales y componentes
* **Fuentes de alimentación:** Módulo MB102 / XD-42 con salidas estables de 3.3V y 5V DC.
* **Protoboard:** Protoboard de 400 puntos sin soldadura.
* **Cables y conexiones:** Cables Jumper de tipo macho-macho, macho-hembra y hembra-hembra.
* **Credenciales de acceso:** Tarjetas de proximidad RFID de 125 kHz.
* **Estructura física:** Gabinete de soporte y protección fabricado con paneles de MDF y Alucobond para alojar los módulos, la pantalla y el sistema mecánico.

## 8. Diagrama esquemático
![Esquema](hardware/Esquematico.png)
## 9. Códigos fuente
Todos los códigos y programas desarrollados para el funcionamiento del prototipo se encuentran almacenados y accesibles en la carpeta del repositorio:
* [Ver código fuente](codigo/PUERTA_CONTROL/PUERTA_CONTROL.ino)
* **Propósito del programa:** Gestionar la lectura del identificador mediante el lector RFID, controlar el posicionamiento PWM del servomotor, administrar el temporizador de autocierre no bloqueante mediante la función `millis()` y mantener la comunicación bidireccional por WebSockets con la plataforma SinricPro.
* **Parámetros modificables:** Es necesario actualizar en el código fuente las credenciales de la red inalámbrica (`SSID` y contraseña) junto con las claves de autenticación de la plataforma IoT (`APP_KEY`, `APP_SECRET` y `LOCK_ID`).

## 10. Librerías utilizadas
* **SinricPro / SinricProLock:** Permite la gestión de dispositivos virtuales en la nube y su vinculación con Amazon Alexa. [Repositorio oficial](https://github.com/sinricpro/esp8266-esp32-sdk.git)
* **ESP32Servo:** Utilizada para controlar con precisión la posición angular del servomotor. [Repositorio oficial](https://madhephaestus.github.io/ESP32Servo/annotated.html)
* **LiquidCrystal_I2C:** Facilita la comunicación y el despliegue visual de textos y estados en la pantalla LCD. [Repositorio oficial](https://github.com/johnrickman/LiquidCrystal_I2C.git)
* **HardwareSerial:** Empleada para gestionar la comunicación UART con el lector RDM6300.

## 11. Configuración de dispositivos
* **ESP32:** Configurado a través del entorno de desarrollo Arduino IDE empleando C++, con la placa ESP32-WROOM-32 y una velocidad de transmisión en el monitor serial fijada en 115200 baudios.
* **Lector RFID (RDM6300):** Configurado mediante interfaz UART a una velocidad de 9600 baudios.
* **Pantalla LCD:** Conectada mediante el protocolo I2C utilizando los pines GPIO 21 para SDA y GPIO 22 para SCL.
* **Servomotor:** Accionado mediante una señal de control PWM asignada al pin GPIO 18.

## 12. Plataforma IoT
* **Nombre de la plataforma:** SinricPro.
* **Función:** Servidor IoT basado en WebSockets encargado de procesar los comandos de control remoto y habilitar la compatibilidad con Amazon Alexa.
* **Configuración y variables:** Se configuró un dispositivo virtual de tipo cerradura nombrado `Puerta_ESP32`, el cual registra de forma dinámica los estados de eventos correspondientes a `Unlocked` y `Locked`.
* 🔗 **Enlace de acceso al Dashboard (Evidencia):** [Ver panel de control en línea](evidencias/sinricpro_dashboard_puerta.png)
## 13. Configuración paso a paso
* **Paso 1:** Preparar el hardware base y posicionar los componentes electrónicos sobre la protoboard.
* **Paso 2:** Realizar el cableado y las conexiones eléctricas principales, estableciendo un puente de distribución de energía en los rieles de la protoboard para conectar las líneas de alimentación positiva (5V/3.3V) y negativa (GND) desde la fuente externa hacia todos los módulos.
* **Paso 3:** Conectar el lector RFID RDM6300 al ESP32 interconectando el pin TX del lector al pin RX correspondiente del microcontrolador, además de alimentar el módulo a 5V asegurando compartir la tierra (GND).
* **Paso 4:** Conectar la pantalla LCD 16x2 I2C utilizando el pin SDA al GPIO 21 y el pin SCL al GPIO 22 del ESP32, con sus respectivas líneas de alimentación VCC (5V) y GND.
* **Paso 5:** Conectar la señal de control PWM del servomotor MG996R al pin GPIO 18 del ESP32, alimentando su potencia directamente desde la fuente externa y unificando las tierras (GND común).
* **Paso 6:** Instalar y configurar el entorno de desarrollo Arduino IDE junto con el paquete de soporte para placas ESP32.
* **Paso 7:** Descargar e instalar las librerías necesarias dentro del entorno de desarrollo (`SinricPro`, `ESP32Servo`, `LiquidCrystal_I2C`).
* **Paso 8:** Modificar en el código fuente los parámetros de conexión de red Wi-Fi y los identificadores únicos provistos por la plataforma SinricPro.
* **Paso 9:** Compilar y cargar el programa directamente en el microcontrolador ESP32.
* **Paso 10:** Validar la correcta ejecución y lectura utilizando la credencial autorizada (tarjeta de proximidad RFID de 125 kHz), comprobando el flujo de datos mediante el Monitor Serial.
* **Paso 11:** Configurar la Skill correspondiente para lograr la integración con los comandos de voz de Amazon Alexa.
* **Paso 12:** Acoplar y posicionar físicamente el servomotor MG996R conectándolo de forma directa al mecanismo de la chapa o pestillo, asegurándolo firmemente mediante la estructura de soporte diseñada para resistir el esfuerzo mecánico al girar.
* **Paso 13:** Integrar y ensamblar todo el circuito y los mecanismos dentro de la caja protectora definitiva fabricada en MDF y Alucobond, la cual alberga la pantalla LCD y los componentes del sistema.
* **Paso 14:** Realizar las pruebas finales de validación, comprobando la recepción de datos, la sincronización de estados en la nube y el funcionamiento operativo general del prototipo.
## 14. Video de presentación
[🎥 Ver video de presentación del proyecto en YouTube](https://youtu.be/f8vocLhxorY)

## 15. Referencias
* Las fuentes bibliográficas y los 10 artículos científicos de soporte (correspondientes al periodo 2022-2026) que sustentan el desarrollo de este proyecto se encuentran organizados y disponibles dentro de la carpeta `/referencias/` del repositorio.
* [📚 Ver referencias del proyecto](referencias)
