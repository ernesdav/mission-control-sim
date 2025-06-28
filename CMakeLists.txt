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
    # A medida que creemos más clases, añadiremos sus .cpp aquí
)

# Le decimos a CMake que cuando compile este ejecutable,
# debe buscar archivos de cabecera en nuestro directorio 'include'.
target_include_directories(${EXECUTABLE_NAME} PUBLIC include)

# Enlazamos nuestro ejecutable con la librería de Threads.
# Sin esto, los std::thread no funcionarían.
target_link_libraries(${EXECUTABLE_NAME} Threads::Threads)