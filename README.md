# Simulador de Algoritmos de Planificación de CPU

Simulador que implementa y compara los principales algoritmos de planificación de procesos en sistemas operativos:

- **FCFS** (First Come First Served) - Planificación por orden de llegada
- **SJF** (Shortest Job First) - Planificación por trabajo más corto (no apropiativo)
- **Round Robin** - Planificación circular con quantum configurable
- **Prioridades** - Planificación por prioridades (con y sin desalojo)

### Métricas de Rendimiento
- Tiempo de Retorno (Turnaround Time)
- Tiempo de Espera (Waiting Time)
- Tiempo de Respuesta (Response Time)
- Utilización de CPU
- Métricas promedio del sistema

### Funcionalidades
- Carga de procesos desde archivos de texto
- Creación manual de procesos
- Visualización de Diagrama de Gantt
- Comparación entre algoritmos
- Análisis automático de mejor algoritmo

## Requisitos
- Compilador C++ compatible con C++17 (g++, clang++, o MSVC)
- Sistema operativo: Windows, Linux o macOS
- Make (opcional, para usar Makefile)

## Instalación

### Compilación Manual

```bash
g++ -std=c++17 -Wall -O2 -o scheduler_simulator \
    main.cpp \
    Core/*.cpp \
    algorithms/*.cpp \
    metrics.cpp \
    UI/*.cpp \
    Utils/*.cpp
```

### Compilación con Makefile

```bash
make
```

Para Windows con MinGW:
```cmd
mingw32-make
```

## Uso

### Ejecutar el programa

```bash
./scheduler_simulator
```

O en Windows:
```cmd
scheduler_simulator.exe
```

### Menú Principal

1. **Cargar procesos desde archivo**: Carga un conjunto de procesos desde un archivo de texto
2. **Crear procesos manualmente**: Permite ingresar procesos uno por uno
3. **Ejecutar simulación**: Ejecuta un algoritmo seleccionado
4. **Ver procesos actuales**: Muestra los procesos cargados
5. **Comparar todos los algoritmos**: Ejecuta todos los algoritmos y los compara
6. **Salir**: Termina el programa

### Formato de Archivos de Procesos

Los archivos de texto deben seguir el formato:

```
Proceso	Llegada	Ráfaga	Prioridad
P1	0	8	3
P2	1	4	1
P3	2	9	4
P4	3	5	2
```

O simplemente (sin encabezado):
```
P1	0	8	3
P2	1	4	1
P3	2	9	4
P4	3	5	2
```

## Casos de Prueba

El programa incluye dos casos de prueba obligatorios:

### Conjunto 1: Procesos Básicos
- P1: Llegada=0, Ráfaga=8, Prioridad=3
- P2: Llegada=1, Ráfaga=4, Prioridad=1
- P3: Llegada=2, Ráfaga=9, Prioridad=4
- P4: Llegada=3, Ráfaga=5, Prioridad=2

### Conjunto 2: Procesos Variados
- P1: Llegada=0, Ráfaga=10, Prioridad=2
- P2: Llegada=2, Ráfaga=3, Prioridad=1
- P3: Llegada=4, Ráfaga=6, Prioridad=3
- P4: Llegada=6, Ráfaga=1, Prioridad=1
- P5: Llegada=8, Ráfaga=4, Prioridad=2

## Ejemplos de Uso

### Ejemplo 1: Ejecutar FCFS

1. Seleccione opción 1: "Cargar procesos desde archivo"
2. Ingrese: `test_cases/conjunto1.txt`
3. Seleccione opción 3: "Ejecutar simulación"
4. Seleccione opción 1: "FCFS"
5. Revise los resultados

### Ejemplo 2: Comparar Todos los Algoritmos

1. Cargue o cree procesos
2. Seleccione opción 5: "Comparar todos los algoritmos"
3. Revise la tabla comparativa y el mejor algoritmo

## Solución de Problemas

### Error de compilación en Windows
- Asegúrese de tener MinGW instalado
- Use `mingw32-make` en lugar de `make`

### Archivo no encontrado
- Verifique que los archivos de prueba estén en `test_cases/`
- Use rutas relativas o absolutas correctas

### Errores de ejecución
- Verifique que todos los archivos fuente estén presentes
- Asegúrese de usar C++17 o superior

##  Notas

- Las prioridades son numéricas: menor número = mayor prioridad
- El quantum en Round Robin es configurable por el usuario
- El Diagrama de Gantt muestra visualmente el orden de ejecución
- Todas las métricas se calculan automáticamente

## Autores

Daniel Verschuur 
Alejandra Teixeira 
Valeria Leon
