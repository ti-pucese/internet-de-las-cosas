# Tutorial: Documentación de un Proyecto IoT y Publicación en el Repositorio de GitHub

**Asignatura:** Internet de las Cosas (IoT)  
**Carrera:** Ingeniería en Tecnologías de la Información  

---

# Índice

1. Introducción
2. Objetivos
3. Requisitos Previos
4. Herramientas Necesarias
5. Procedimiento Paso a Paso
   - Paso 1. Preparar la documentación del proyecto
   - Paso 2. Aceptar la invitación al repositorio
   - Paso 3. Acceder al repositorio "Internet de las Cosas"
   - Paso 4. Crear una carpeta personal
   - Paso 5. Organizar la documentación dentro de la carpeta
   - Paso 6. Subir la documentación al repositorio
   - Paso 7. Confirmar los cambios (Commit)
   - Paso 8. Verificar la documentación publicada
6. Buenas prácticas
7. Errores frecuentes
8. Conclusiones

---

# 1. Introducción

La documentación es una de las fases más importantes en el desarrollo de un proyecto de Internet de las Cosas (IoT), ya que permite registrar de forma organizada el proceso de diseño, implementación y resultados obtenidos. Una documentación adecuada facilita la comprensión del proyecto, permite evidenciar el trabajo realizado y sirve como respaldo técnico para futuras modificaciones.

Con el propósito de centralizar las entregas y mantener una organización uniforme, la asignatura utilizará un repositorio compartido en GitHub denominado **"Internet de las Cosas"**. Cada estudiante será agregado como colaborador por el docente y deberá crear una carpeta con su nombre completo, donde almacenará toda la documentación correspondiente a su proyecto.

Este tutorial describe detalladamente el procedimiento que debe seguir cada estudiante para organizar y publicar correctamente la documentación de su proyecto dentro del repositorio compartido.

---

# 2. Objetivos

## Objetivo General

Documentar correctamente un proyecto de Internet de las Cosas y publicarlo dentro del repositorio compartido de GitHub siguiendo una estructura organizada.

## Objetivos Específicos

- Organizar la documentación técnica del proyecto.
- Acceder al repositorio compartido como colaborador.
- Crear una carpeta personal dentro del repositorio.
- Publicar correctamente toda la documentación del proyecto.
- Verificar que la información haya sido subida correctamente.

---

# 3. Requisitos Previos

Antes de comenzar, el estudiante deberá contar con:

- Una cuenta de GitHub previamente creada.
- Haber sido agregado como colaborador por el docente.
- Acceso a Internet.
- Un navegador web actualizado.
- Toda la documentación del proyecto finalizada.

---

# 4. Herramientas Necesarias

- GitHub.
- Navegador web.
- Editor de texto (Visual Studio Code recomendado).
- Documentación del proyecto.
- Imágenes del proyecto.
- Diagramas electrónicos.

---

# 5. Procedimiento Paso a Paso

---

# Paso 1. Preparar la documentación del proyecto

Antes de acceder al repositorio de GitHub, el estudiante deberá organizar toda la documentación correspondiente a su proyecto IoT. Esta información será la evidencia técnica del trabajo desarrollado durante la asignatura y deberá estar completa antes de ser publicada.

Se recomienda crear una carpeta principal en el computador donde se almacenen todos los documentos relacionados con el proyecto. Dentro de esta carpeta deberán incluirse, como mínimo, los siguientes elementos:

```
Proyecto IoT/

├── Nombre del proyecto.pdf (o documento principal)

├── Descripción General.docx

├── Objetivos.pdf

├── Componentes Electrónicos Utilizados.pdf

├── Arquitectura del Sistema.pdf

├── Diagrama de Conexiones.png

├── Resultados Obtenidos.pdf

├── Evidencias Fotográficas/

└── Conclusiones.pdf
```

Cada uno de estos documentos debe contener la información correspondiente:

### Nombre del proyecto

Debe identificar claramente el trabajo desarrollado, utilizando un título corto, descriptivo y relacionado con la solución IoT implementada.

Ejemplo:

- Sistema Inteligente de Monitoreo Ambiental
- Estación Meteorológica IoT
- Sistema Automatizado de Riego

---

### Descripción general

Explicar de forma resumida el propósito del proyecto, el problema que busca resolver y el funcionamiento general del sistema desarrollado.

---

### Objetivos

Incluir el objetivo general y los objetivos específicos planteados para el desarrollo del proyecto.

---

### Componentes electrónicos utilizados

Presentar una lista de todos los dispositivos utilizados durante la implementación, por ejemplo:

- ESP32
- Arduino UNO
- Sensor DHT11
- Sensor HC-SR04
- Módulo WiFi
- Protoboard
- Resistencias
- LEDs
- Cables Dupont
- Fuente de alimentación

En caso de ser posible, agregar una breve descripción de la función que cumple cada componente dentro del sistema.

---

### Arquitectura del sistema

Describir cómo interactúan los diferentes componentes del proyecto.

Se recomienda incluir un diagrama de arquitectura donde se visualice la comunicación entre sensores, microcontroladores, servicios en la nube y dispositivos finales.

---

### Diagrama de conexiones

Agregar el esquema electrónico utilizado durante el desarrollo del proyecto.

Este diagrama puede haber sido elaborado utilizando herramientas como Tinkercad, Fritzing, Proteus o cualquier otro software similar.

---

### Resultados obtenidos

Describir el comportamiento final del proyecto indicando:

- Funcionamiento alcanzado.
- Pruebas realizadas.
- Resultados obtenidos.
- Limitaciones encontradas.

---

### Evidencias fotográficas

Incluir fotografías claras del proyecto mostrando:

- Montaje electrónico.
- Circuitos.
- Sensores.
- Pantallas.
- Pruebas de funcionamiento.
- Resultado final del prototipo.

Se recomienda nombrar las imágenes de forma organizada.

Ejemplo:

```
evidencia_01.jpg

evidencia_02.jpg

evidencia_03.jpg
```

---

### Conclusiones

Redactar las conclusiones obtenidas durante el desarrollo del proyecto indicando los conocimientos adquiridos, las dificultades encontradas y las posibles mejoras futuras.

Una vez organizada toda esta documentación, el estudiante estará listo para publicarla dentro del repositorio compartido.

---

# Paso 2. Aceptar la invitación al repositorio

El docente agregará a cada estudiante como colaborador del repositorio denominado **"Internet de las Cosas"**.

Cada estudiante deberá revisar el correo electrónico asociado a su cuenta de GitHub o ingresar a la sección de notificaciones de GitHub para aceptar la invitación.

Una vez aceptada, el repositorio aparecerá automáticamente dentro de la lista de repositorios disponibles en la cuenta del estudiante.

---

# Paso 3. Acceder al repositorio "Internet de las Cosas"

Ingresar a GitHub e iniciar sesión.

Desde el panel principal seleccionar el repositorio compartido llamado:

```
Internet de las Cosas
```

Dentro de este repositorio cada estudiante deberá trabajar únicamente sobre su propia carpeta.

---

# Paso 4. Crear una carpeta personal

Dentro del repositorio, cada estudiante deberá crear una carpeta utilizando su nombre y apellido.

Ejemplo:

```
Internet de las Cosas/

├── Juan Perez/

├── Maria Lopez/

├── Carlos Torres/

├── Ana Gonzalez/
```

El nombre de la carpeta debe permitir identificar claramente al propietario de la documentación.

No se deberán modificar ni eliminar las carpetas pertenecientes a otros compañeros.

---

# Paso 5. Organizar la documentación dentro de la carpeta

Una vez creada la carpeta personal, se deberán subir todos los documentos preparados en el Paso 1.

La estructura recomendada será la siguiente:

```
Internet de las Cosas/

└── Juan Perez/

    ├── Nombre del Proyecto.pdf

    ├── Descripción General.pdf

    ├── Objetivos.pdf

    ├── Componentes Electrónicos.pdf

    ├── Arquitectura del Sistema.pdf

    ├── Diagrama de Conexiones.png

    ├── Resultados.pdf

    ├── Evidencias/

    │     ├── evidencia1.jpg

    │     ├── evidencia2.jpg

    │     └── evidencia3.jpg

    └── Conclusiones.pdf
```

Antes de continuar, verificar que todos los archivos estén correctamente organizados y puedan abrirse sin inconvenientes.

---

# Paso 6. Subir la documentación al repositorio

Seleccionar la opción **Add file** y posteriormente **Upload files**.

Arrastrar todos los archivos correspondientes a la carpeta personal o seleccionarlos desde el explorador de archivos.

Esperar a que GitHub complete la carga de todos los documentos antes de continuar.

---

# Paso 7. Confirmar los cambios (Commit)

Una vez cargada toda la documentación, GitHub solicitará un mensaje descriptivo del cambio realizado.

Ejemplos:

- Entrega documentación Proyecto IoT.
- Primera versión de la documentación.
- Publicación del proyecto final.

Posteriormente hacer clic en **Commit changes** para registrar definitivamente la entrega.

---

# Paso 8. Verificar la documentación publicada

Finalmente, revisar que todos los documentos aparezcan correctamente dentro de la carpeta personal.

Comprobar que:

- Todos los archivos fueron cargados.
- Las imágenes pueden visualizarse.
- Los documentos pueden descargarse.
- La carpeta contiene toda la documentación solicitada.

La revisión final permitirá garantizar que la entrega fue realizada correctamente y que el docente podrá acceder a toda la información del proyecto.

---

# 6. Buenas Prácticas

- Mantener una estructura organizada de carpetas.
- Utilizar nombres claros para todos los archivos.
- No modificar la documentación de otros estudiantes.
- Revisar cada archivo antes de subirlo.
- Verificar que todas las imágenes sean visibles.
- Realizar commits con mensajes descriptivos.
- Confirmar la entrega revisando el contenido final del repositorio.

---

# 7. Errores Frecuentes

## Crear la carpeta con un nombre incorrecto

La carpeta debe identificarse con el nombre y apellido del estudiante para facilitar la revisión por parte del docente.

---

## Subir archivos fuera de la carpeta personal

Toda la documentación debe almacenarse únicamente dentro de la carpeta creada por el estudiante.

---

## Omitir documentos solicitados

Antes de realizar el commit, verificar que se encuentren todos los documentos indicados en el Paso 1.

---

## No revisar el contenido publicado

Después del commit, comprobar que todos los archivos sean visibles y puedan abrirse correctamente.

---

# 8. Conclusiones

La utilización de un repositorio compartido en GitHub permite organizar de manera eficiente la documentación de los proyectos desarrollados durante la asignatura de Internet de las Cosas. La creación de una carpeta personal para cada estudiante facilita el almacenamiento ordenado de la información, simplifica el proceso de revisión por parte del docente y promueve el uso de herramientas profesionales de control de versiones.

Asimismo, seguir la estructura propuesta en este tutorial garantiza que cada proyecto contenga la información técnica mínima necesaria para evidenciar su desarrollo, funcionamiento y resultados, fomentando buenas prácticas de documentación y gestión de proyectos tecnológicos.
