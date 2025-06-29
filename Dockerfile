# --- ETAPA 1: El Taller de Construcción (Builder) ---
# Usamos una imagen base de gcc que incluye g++, make, y cmake.
FROM gcc:latest AS builder

# Establecemos el directorio de trabajo.
WORKDIR /app

# Copiamos todo el código fuente del proyecto al contenedor.
COPY . .

# Ejecutamos el flujo de compilación de CMake.
# 1. Configuramos el proyecto, creando los archivos de build en /app/build
RUN cmake -S . -B build

# 2. Compilamos el proyecto usando la configuración generada.
RUN cmake --build build

# --- ETAPA 2: El Paquete Final y Limpio ---
# Empezamos desde una imagen base de Ubuntu ligera.
FROM ubuntu:latest

# Establecemos el directorio de trabajo.
WORKDIR /app

# La magia: Copiamos SOLAMENTE el ejecutable compilado desde la etapa "builder".
# Nota que la ruta de origen ahora es /app/build/
COPY --from=builder /app/build/mission_control_app .

# El comando que se ejecutará por defecto cuando se inicie el contenedor.
# Usamos "sh -c" para asegurar que la entrada del usuario (Enter) sea manejada correctamente.
CMD ["sh", "-c", "./mission_control_app"]