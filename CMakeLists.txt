cmake_minimum_required(VERSION 3.16)
project(MissionControlSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Busca la librería de Threads requerida por el sistema y la prepara.
find_package(Threads REQUIRED)

# Definimos el nombre de nuestro ejecutable principal.
set(EXECUTABLE_NAME mission_control_app)

# Creamos el ejecutable a partir de los archivos fuente en la carpeta src/.
add_executable(${EXECUTABLE_NAME}
    src/main.cpp
    src/SurveillanceMission.cpp
    src/DeliveryMission.cpp
    src/Drone.cpp
    src/MissionControl.cpp
    # A medida que creemos más clases, añadiremos sus .cpp aquí
)

# Le decimos a CMake que cuando compile este ejecutable,
# debe buscar archivos de cabecera en nuestro directorio 'include'.
target_include_directories(${EXECUTABLE_NAME} PUBLIC include)

# Enlazamos nuestro ejecutable con la librería de Threads.
# Sin esto, los std::thread no funcionarían.
target_link_libraries(${EXECUTABLE_NAME} Threads::Threads)

# ===================================================================
# TESTING SECTION (with Google Test)
# ===================================================================

# Habilitamos la capacidad de realizar pruebas en el proyecto.
enable_testing()

# Incluimos el módulo que nos permite descargar dependencias externas.
include(FetchContent)

# Declaramos nuestra dependencia de Google Test.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0 # Usando la etiqueta correcta que descubrimos
)

# Hacemos que la dependencia esté disponible (la descarga si es necesario).
FetchContent_MakeAvailable(googletest)

# Creamos nuestro ejecutable de pruebas.
# Es crucial incluir no solo el archivo de prueba, sino también todos los archivos .cpp
# del código que queremos probar, para que se compilen y enlacen juntos.
add_executable(run_tests
    tests/test_mission_queue.cpp
    # Fuentes de la aplicación que son necesarias para la prueba:
    src/SurveillanceMission.cpp
    src/DeliveryMission.cpp
    src/Drone.cpp
    src/MissionControl.cpp
)

# Le decimos a nuestro ejecutable de pruebas dónde encontrar los archivos .h
target_include_directories(run_tests PUBLIC include)

# Enlazamos nuestro ejecutable de pruebas con las librerías necesarias:
# 1. GTest::gtest_main (que nos da gtest y una función main() para las pruebas)
# 2. Threads::Threads (porque nuestro código de Drone usa concurrencia)
target_link_libraries(run_tests
    GTest::gtest_main
    Threads::Threads
)

# Descubrimos y añadimos automáticamente todas las pruebas definidas en nuestro ejecutable
# al sistema de pruebas de CMake (CTest).
include(GoogleTest)
gtest_discover_tests(run_tests)