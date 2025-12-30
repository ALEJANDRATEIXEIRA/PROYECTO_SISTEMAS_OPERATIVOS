# 📚 Guía de Compilación - Simulador de Planificación de CPU

## 🪟 Para Windows (Tu caso)

### Opción 1: Usar el script compile.bat (RECOMENDADO)

1. **Abre el Explorador de Archivos** y navega a la carpeta del proyecto:
   ```
   C:\Users\asus\Documents\proyecto SO
   ```

2. **Haz doble clic** en el archivo `compile.bat`

   O desde PowerShell/CMD:
   ```cmd
   compile.bat
   ```

3. Si la compilación es exitosa, verás:
   ```
   Compilacion exitosa!
   Ejecutable creado: scheduler_simulator.exe
   ```

4. **Ejecutar el programa:**
   ```cmd
   scheduler_simulator.exe
   ```

---

### Opción 2: Compilar manualmente desde PowerShell/CMD

Abre PowerShell o CMD en la carpeta del proyecto y ejecuta:

```cmd
g++ -std=c++17 -Wall -O2 -o scheduler_simulator.exe main.cpp Core\process.cpp Core\scheduler.cpp algorithms\fcfs.cpp algorithms\sjf.cpp algorithms\round_robin.cpp algorithms\priority.cpp metrics.cpp UI\interface.cpp Utils\file_handler.cpp
```

**Versión más legible (multi-línea):**
```cmd
g++ -std=c++17 -Wall -O2 -o scheduler_simulator.exe ^
    main.cpp ^
    Core\process.cpp ^
    Core\scheduler.cpp ^
    algorithms\fcfs.cpp ^
    algorithms\sjf.cpp ^
    algorithms\round_robin.cpp ^
    algorithms\priority.cpp ^
    metrics.cpp ^
    UI\interface.cpp ^
    Utils\file_handler.cpp
```

---

### Opción 3: Usar Makefile con MinGW

Si tienes `make` instalado (o `mingw32-make`):

```cmd
mingw32-make
```

---

## 🐧 Para Linux/Mac

### Opción 1: Usar Makefile (RECOMENDADO)

```bash
make
```

### Opción 2: Compilar manualmente

```bash
g++ -std=c++17 -Wall -O2 -o scheduler_simulator \
    main.cpp \
    Core/process.cpp \
    Core/scheduler.cpp \
    algorithms/fcfs.cpp \
    algorithms/sjf.cpp \
    algorithms/round_robin.cpp \
    algorithms/priority.cpp \
    metrics.cpp \
    UI/interface.cpp \
    Utils/file_handler.cpp
```

---

## ✅ Verificar la Compilación

Después de compilar, deberías ver un archivo ejecutable:

- **Windows:** `scheduler_simulator.exe`
- **Linux/Mac:** `scheduler_simulator`

## 🚀 Ejecutar el Programa

### Windows:
```cmd
scheduler_simulator.exe
```

### Linux/Mac:
```bash
./scheduler_simulator
```

---

## ⚠️ Solución de Problemas

### Error: "g++ no se reconoce como comando"

**Solución:** Necesitas instalar MinGW (Minimalist GNU for Windows)

1. Descarga MinGW-w64 desde: https://www.mingw-w64.org/downloads/
2. O instala usando Chocolatey:
   ```cmd
   choco install mingw
   ```
3. O instala Code::Blocks que incluye MinGW
4. Agrega MinGW al PATH del sistema:
   - Busca "Variables de entorno" en Windows
   - Agrega `C:\MinGW\bin` al PATH

### Error: "No such file or directory"

**Solución:** Asegúrate de estar en el directorio correcto:
```cmd
cd "C:\Users\asus\Documents\proyecto SO"
```

### Error de compilación: "undefined reference"

**Solución:** Asegúrate de incluir TODOS los archivos .cpp en el comando de compilación.

### Errores relacionados con C++17

**Solución:** Verifica que tu versión de g++ soporte C++17:
```cmd
g++ --version
```
Debería ser g++ 7.0 o superior.

---

## 📝 Notas Importantes

- El código requiere **C++17** o superior
- Asegúrate de tener todos los archivos en sus respectivas carpetas
- Los casos de prueba están en `test_cases/`
- El ejecutable se crea en la misma carpeta que el código fuente

---

## 🎯 Comandos Rápidos de Referencia

```cmd
# Compilar
compile.bat

# Compilar y ejecutar
compile.bat && scheduler_simulator.exe

# Limpiar archivos compilados (si usas Makefile)
mingw32-make clean
```



