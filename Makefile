# Makefile para Simulador de Planificación de CPU
# Compatible con Windows (MinGW) y Linux

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = scheduler_simulator
SRCDIR = .
OBJDIR = obj

# Directorios
CORE_DIR = Core
ALGORITHMS_DIR = algorithms
UI_DIR = UI
UTILS_DIR = Utils

# Archivos fuente
SOURCES = main.cpp \
          $(CORE_DIR)/process.cpp \
          $(CORE_DIR)/scheduler.cpp \
          $(ALGORITHMS_DIR)/fcfs.cpp \
          $(ALGORITHMS_DIR)/sjf.cpp \
          $(ALGORITHMS_DIR)/round_robin.cpp \
          $(ALGORITHMS_DIR)/priority.cpp \
          metrics.cpp \
          $(UI_DIR)/interface.cpp \
          $(UTILS_DIR)/file_handler.cpp

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# En Windows con MinGW
ifeq ($(OS),Windows_NT)
    RM = del /Q
    MKDIR = if not exist
    RMDIR = rmdir /S /Q
    TARGET_EXT = .exe
    OBJ_PREFIX = $(OBJDIR)\
else
    RM = rm -f
    MKDIR = mkdir -p
    RMDIR = rm -rf
    TARGET_EXT =
    OBJ_PREFIX = $(OBJDIR)/
endif

# Regla principal
all: $(TARGET)$(TARGET_EXT)

$(TARGET)$(TARGET_EXT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)
	@echo Compilación completada: $(TARGET)$(TARGET_EXT)

# Reglas de compilación
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorio de casos de prueba
test_cases:
	@if not exist test_cases mkdir test_cases 2>nul || mkdir -p test_cases

# Limpiar archivos compilados
clean:
	$(RM) $(OBJECTS) $(TARGET)$(TARGET_EXT)
	@echo Archivos limpiados

# Limpiar todo incluyendo objetos
distclean: clean
	$(RMDIR) $(OBJDIR) 2>nul || true
	@echo Limpieza completa realizada

# Ejecutar programa
run: $(TARGET)$(TARGET_EXT)
	./$(TARGET)$(TARGET_EXT)

# Ayuda
help:
	@echo "Makefile para Simulador de Planificación de CPU"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make          - Compilar el programa"
	@echo "  make clean    - Eliminar archivos objeto y ejecutable"
	@echo "  make run      - Compilar y ejecutar el programa"
	@echo "  make help     - Mostrar esta ayuda"
	@echo ""

.PHONY: all clean distclean run help test_cases

