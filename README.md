# Proyecto 6: Simulador de un Centro de Control de Misiones para Drones

Este es un proyecto avanzado en C++ que simula un centro de control para una flota de drones autónomos. El sistema es capaz de gestionar y asignar misiones con diferentes prioridades a múltiples drones que operan de forma concurrente.

## Conceptos y Características Clave

* **Arquitectura Polimórfica:** Utiliza una clase base abstracta `Mission` para permitir diferentes tipos de misiones (Vigilancia, Entrega), demostrando un uso práctico de la herencia y el polimorfismo.
* **Simulación Concurrente:** Cada dron en la flota opera en su propio hilo de ejecución (`std::thread`), permitiendo la ejecución de misiones en paralelo.
* **Gestión de Tareas Priorizadas:** Una cola de prioridad (`std::priority_queue`) con un comparador personalizado asegura que las misiones de mayor urgencia se asignen primero.
* **Seguridad en Concurrencia (Thread-Safety):** El acceso a los recursos compartidos (la cola de misiones) está protegido mediante primitivas de sincronización (`std::mutex`, `std::lock_guard`) para prevenir condiciones de carrera.
* **Gestión de Memoria Moderna:** Utiliza punteros inteligentes (`std::shared_ptr`) para una gestión de memoria automática, segura y sin fugas en un entorno concurrente (RAII).
* **Prácticas de C++ Moderno:** Hace uso de características como `override`, `mutable`, `enum class`, `std::atomic`, `std::move`, y `std::make_shared`.
* **Pruebas Unitarias:** Incluye un conjunto de pruebas con el framework Google Test para verificar la corrección lógica y la seguridad en concurrencia de los componentes críticos.
* **Sistema de Compilación Profesional:** El proyecto es gestionado por CMake, que maneja las dependencias (como Google Test vía `FetchContent`) y la compilación de múltiples ejecutables (la aplicación principal y el corredor de pruebas).
* **Contenerización:** Incluye un `Dockerfile` con una estrategia de "build" multi-etapa para crear una imagen de producción ligera, portable y eficiente.

## Requisitos

* Un compilador de C++17 o superior (ej. g++)
* CMake (versión 3.16+)
* Docker (opcional, para ejecución contenerizada)

## Cómo Construir y Ejecutar

### Construcción con CMake

1.  **Clonar el repositorio:**
    ```bash
    git clone [URL_DE_TU_REPO_DE_GITHUB]
    cd mission-control-sim
    ```

2.  **Configurar el proyecto con CMake:**
    (Este comando se ejecuta una vez, o cada vez que se modifica `CMakeLists.txt`)
    ```bash
    cmake -S . -B build
    ```

3.  **Compilar el proyecto:**
    (Este comando compilará tanto la aplicación principal como las pruebas)
    ```bash
    cmake --build build
    ```

### Ejecución

Los ejecutables se encontrarán dentro del directorio `build/`.

* **Ejecutar la Simulación Principal:**
    ```bash
    ./build/mission_control_app
    ```
    La simulación comenzará y se ejecutará hasta que presiones `Enter`.

* **Ejecutar las Pruebas Unitarias:**
    ```bash
    ./build/run_tests
    ```

### Ejecución con Docker

1.  **Construir la imagen Docker:**
    (Asegúrate de estar en la raíz del proyecto)
    ```bash
    docker build -t mission-control-image .
    ```

2.  **Ejecutar un contenedor a partir de la imagen:**
    ```bash
    docker run --rm -it mission-control-image
    ```
    *Nota: Se añade `-it` para asegurar que el contenedor se ejecute en modo interactivo y pueda capturar la pulsación de `Enter` para detener la simulación.*