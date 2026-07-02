# Sistema IoT para Monitoreo de Variables Eléctricas con ThingSpeak y MATLAB Online

## Descripción general

Este proyecto consiste en el desarrollo de una solución IoT para el monitoreo de variables eléctricas mediante un ESP32, un módulo PZEM-004T v3.0, la plataforma ThingSpeak y herramientas de MATLAB Online.

El sistema permite adquirir datos de voltaje, corriente, energía, potencia, frecuencia y factor de potencia. Estos valores son enviados desde el ESP32 hacia ThingSpeak, donde se almacenan en un canal IoT. Posteriormente, los datos son visualizados y analizados mediante MATLAB Visualizations, utilizando código personalizado para generar gráficas de tiempo y comparaciones entre variables.

## Problema que resuelve

El monitoreo manual de variables eléctricas puede ser limitado, poco práctico y difícil de registrar de forma continua. Este proyecto permite visualizar las mediciones eléctricas en tiempo real y consultar datos históricos desde una plataforma en la nube, facilitando el análisis del comportamiento del consumo eléctrico.

## Objetivos

### Objetivo general

Implementar un sistema IoT que permita adquirir, transmitir, visualizar y analizar variables eléctricas mediante ESP32, ThingSpeak y MATLAB Online.

### Objetivos específicos

- Capturar variables eléctricas mediante el módulo PZEM-004T v3.0.
- Enviar los datos desde el ESP32 hacia ThingSpeak mediante conexión WiFi.
- Visualizar las variables eléctricas en el canal de ThingSpeak.
- Crear gráficas personalizadas mediante MATLAB Visualizations.
- Comparar variables eléctricas, como voltaje vs corriente.
- Documentar el proyecto en GitHub para facilitar su reutilización y mejora.

## Arquitectura de la solución IoT

La solución está compuesta por cuatro etapas principales:

1. **Adquisición de datos:** el módulo PZEM-004T mide las variables eléctricas.
2. **Procesamiento local:** el ESP32 recibe los datos mediante comunicación serial.
3. **Envío a la nube:** el ESP32 transmite los datos hacia ThingSpeak mediante HTTP.
4. **Visualización y análisis:** ThingSpeak almacena los datos y MATLAB Online genera gráficas personalizadas.

```text
Carga eléctrica
      │
      ▼
PZEM-004T v3.0
      │ Comunicación serial
      ▼
ESP32
      │ WiFi / HTTP
      ▼
ThingSpeak
      │ MATLAB Visualizations
      ▼
Gráficas y análisis de variables eléctricas
Componentes de hardware utilizados
Componente	Descripción
ESP32 DevKit	Microcontrolador encargado de procesar y enviar los datos
PZEM-004T v3.0	Módulo de medición de variables eléctricas
Cable USB	Programación y alimentación del ESP32
Cables de conexión	Conexión entre ESP32 y módulo de medición
Protoboard	Organización de conexiones de bajo voltaje
Router WiFi	Acceso a Internet para enviar datos a ThingSpeak
Carga eléctrica de prueba	Elemento utilizado para generar mediciones
Componentes de software utilizados
Software	Uso
Arduino IDE	Programación del ESP32
ThingSpeak	Plataforma IoT para almacenamiento y visualización de datos
MATLAB Online	Visualización y análisis de datos
GitHub	Documentación y publicación del proyecto
Librerías utilizadas
Librería	Función
WiFi.h	Conexión del ESP32 a la red WiFi
HTTPClient.h	Envío de datos hacia ThingSpeak mediante solicitudes HTTP
PZEM004Tv30.h	Comunicación con el módulo PZEM-004T v3.0
AsyncTCP.h	Comunicación asíncrona para servidor web local
ESPAsyncWebServer.h	Creación del dashboard web local en el ESP32
Tecnologías de comunicación implementadas
Tecnología	Descripción
WiFi	Conexión del ESP32 a Internet
HTTP	Envío de datos desde el ESP32 hacia ThingSpeak
Serial UART	Comunicación entre ESP32 y PZEM-004T
JSON	Entrega de datos al dashboard local
MATLAB thingSpeakRead	Lectura de datos almacenados en ThingSpeak
Plataforma IoT empleada

La plataforma IoT utilizada fue ThingSpeak, donde se creó el canal Medidor de Energía.

Campos configurados en ThingSpeak
Campo	Variable	Unidad
Field 1	Voltaje	V
Field 2	Corriente	A
Field 3	Energía	kWh
Field 4	Potencia	W
Field 5	Frecuencia	Hz
Field 6	Factor de potencia	fp

Diagrama de conexión o arquitectura

Fotografías del prototipo

Capturas del dashboard
Dashboard local

Canal en ThingSpeak

Capturas del funcionamiento
Monitor serial del ESP32

![alt text](imagenes/Gráficas%20de%20tiempo.png)

Comparación voltaje vs corriente

Instrucciones de instalación
Instalar Arduino IDE.
Instalar el soporte para placas ESP32 en Arduino IDE.
Instalar las librerías necesarias:
WiFi.h
HTTPClient.h
PZEM004Tv30.h
AsyncTCP.h
ESPAsyncWebServer.h
Descargar o clonar este repositorio.
Abrir el archivo del ESP32 ubicado en:
Codigo/ESP32/medidor_energia_esp32.ino
Configurar las credenciales WiFi y la API Key de ThingSpeak.
Instrucciones de configuración

En el código del ESP32 se deben modificar los siguientes valores:

const char* ssid = "NOMBRE_DE_TU_WIFI";
const char* password = "CONTRASENA_DE_TU_WIFI";
String writeAPIKey = "TU_WRITE_API_KEY";

En los scripts de MATLAB se debe configurar el ID del canal:

channelID = 3410710;

Si el canal es público, se puede leer sin colocar la clave de lectura. Si el canal es privado, se debe utilizar:

readAPIKey = 'TU_READ_API_KEY';
Forma de ejecución del proyecto
Conectar el módulo PZEM-004T al ESP32.
Conectar el ESP32 al computador mediante cable USB.
Abrir el código en Arduino IDE.
Seleccionar la placa ESP32 correspondiente.
Cargar el programa en el ESP32.
Abrir el Monitor Serial para verificar la conexión WiFi y el envío de datos.
Ingresar al canal de ThingSpeak y comprobar la actualización de los campos.
Ejecutar las visualizaciones de MATLAB desde ThingSpeak.
Verificar las gráficas de tiempo y la comparación entre voltaje y corriente.
Códigos MATLAB utilizados
Gráficas de tiempo

Archivo:

Codigo/graficas-tiempo-variables-eléctricas.m

Este script lee los datos almacenados en ThingSpeak y genera gráficas de tiempo para voltaje, corriente, energía, potencia, frecuencia y factor de potencia.

Comparación voltaje vs corriente

Archivo:

Codigo/comparacion-voltaje-vs-corriente.m

Este script lee los campos de voltaje y corriente para generar una gráfica comparativa entre ambas variables.

Resultados obtenidos

Como resultado del proyecto se logró implementar un sistema IoT funcional para el monitoreo de variables eléctricas. El ESP32 obtuvo los datos del módulo PZEM-004T y los envió correctamente hacia ThingSpeak.

En ThingSpeak se visualizaron los datos en tiempo real mediante los campos configurados en el canal. Además, mediante MATLAB Online se generaron gráficas personalizadas de las variables eléctricas y una comparación entre voltaje y corriente.

Las gráficas permitieron comprobar que los datos almacenados en ThingSpeak correspondían a los valores enviados por el ESP32, evidenciando la comunicación entre el microcontrolador, la plataforma IoT y MATLAB Online.

Trabajos futuros
Agregar alertas automáticas cuando el voltaje o la corriente superen valores límite.
Incorporar almacenamiento histórico en una base de datos externa.
Mejorar el diseño del dashboard local.
Añadir autenticación para el acceso al dashboard.
Implementar análisis de consumo eléctrico por día, semana o mes.
Integrar notificaciones mediante correo electrónico o aplicaciones móviles.
Integrantes del grupo
Jorel Figueroa Villegas
Matias Holguin Ayala
Docente
Ing. Manuel Nevárez
Asignatura
Internet de las Cosas
Licencia

Este proyecto se desarrolló con fines académicos. Su uso, modificación y distribución quedan sujetos a las indicaciones de la asignatura.

## Referencias bibliográficas

Arduino. (2024, 16 de abril). *Installing a board package in the IDE 2*. Arduino Documentation.  
https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-board-manager/

Arduino Libraries. (s. f.). *PZEM004Tv30*. Arduino Libraries.  
https://www.arduinolibraries.info/libraries/pzem004-tv30

Espressif Systems. (s. f.). *ESP32 Wi-Fi & Bluetooth SoC*. Espressif.  
https://www.espressif.com/en/products/socs/esp32

Espressif Systems. (s. f.). *Wi-Fi API: Arduino ESP32 documentation*. Espressif Documentation.  
https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html

ESP32Async. (s. f.). *ESPAsyncWebServer*. GitHub.  
https://github.com/ESP32Async/ESPAsyncWebServer

ESP32Async. (s. f.). *AsyncTCP*. GitHub.  
https://github.com/ESP32Async/AsyncTCP

GitHub Docs. (s. f.). *About README files*. GitHub.  
https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/about-readmes

GitHub Docs. (s. f.). *Basic writing and formatting syntax*. GitHub.  
https://docs.github.com/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax

GitHub Docs. (s. f.). *Best practices for repositories*. GitHub.  
https://docs.github.com/en/repositories/creating-and-managing-repositories/best-practices-for-repositories

Mandula, J. (s. f.). *PZEM-004T-v30: Arduino library for the updated PZEM-004T v3.0 power and energy meter*. GitHub.  
https://github.com/mandulaj/PZEM-004T-v30

MathWorks. (s. f.). *ThingSpeak documentation*. MathWorks.  
https://www.mathworks.com/help/thingspeak/

MathWorks. (s. f.). *thingSpeakRead: Read data stored in ThingSpeak channel*. MathWorks.  
https://www.mathworks.com/help/thingspeak/thingspeakread.html

MathWorks. (s. f.). *thingSpeakWrite: Write data to ThingSpeak channel*. MathWorks.  
https://www.mathworks.com/help/thingspeak/thingspeakwrite.html

MathWorks. (s. f.). *MATLAB documentation*. MathWorks.  
https://www.mathworks.com/help/matlab/

MathWorks. (s. f.). *MATLAB plot gallery*. MathWorks.  
https://www.mathworks.com/products/matlab/plot-gallery.html

Pontificia Universidad Católica del Ecuador, Sede Esmeraldas. (2026). *Visualización de variables eléctricas con MATLAB en ThingSpeak: NRC6475_visualizacion_MATLAB_grupo_B* [Informe técnico académico].