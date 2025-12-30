# 🔧 Solución al Error del Diagrama de Gantt

## ❌ Error Encontrado

```
terminate called after throwing an instance of 'std::length_error'
what(): basic_string::_M_create
```

**Causa del Error:**
El error ocurría en la función `printGanttChart` cuando el quantum de Round Robin era pequeño. Al calcular el espacio necesario para mostrar los tiempos en el diagrama, se podía generar un número negativo, y `std::string` no puede crear strings con tamaño negativo.

**Ubicación del problema:**
- Archivo: `metrics.cpp`
- Función: `MetricsCalculator::printGanttChart()`
- Línea problemática (antes): 
  ```cpp
  std::string(entry.second * 2 - std::to_string(currentTime).length() + 1, ' ')
  ```

---

## ✅ Solución Implementada

Se corrigió la función `printGanttChart` para:

1. **Validar entrada vacía:** Verifica que el Diagrama de Gantt no esté vacío
2. **Ancho mínimo:** Define un ancho mínimo (4 caracteres) para cada segmento
3. **Prevenir valores negativos:** Usa `std::max()` para asegurar tamaños válidos
4. **Cálculo seguro:** Todos los cálculos ahora garantizan valores no negativos

**Cambios realizados:**
- Se agregó constante `MIN_WIDTH = 4`
- Todos los cálculos de ancho usan `std::max(MIN_WIDTH, ...)`
- Los espacios se calculan con protección contra valores negativos
- Manejo correcto de casos donde el quantum es muy pequeño

---

## 🔄 Cómo Aplicar la Solución

### Opción 1: Si el programa NO está ejecutándose

1. **Cierra cualquier instancia del programa**
2. **Ejecuta el script de compilación:**
   ```cmd
   compile.bat
   ```

### Opción 2: Si el programa está ejecutándose

1. **Cierra el programa** (`scheduler_simulator.exe`)
2. **Espera unos segundos** para que Windows libere el archivo
3. **Ejecuta:**
   ```cmd
   compile.bat
   ```

### Opción 3: Compilación Manual

```cmd
g++ -std=c++17 -Wall -O2 -o scheduler_simulator.exe main.cpp Core\process.cpp Core\scheduler.cpp algorithms\fcfs.cpp algorithms\sjf.cpp algorithms\round_robin.cpp algorithms\priority.cpp metrics.cpp UI\interface.cpp Utils\file_handler.cpp
```

---

## ✅ Verificación

Después de recompilar:

1. **Ejecuta el programa:**
   ```cmd
   scheduler_simulator.exe
   ```

2. **Prueba Round Robin con conjunto1.txt:**
   - Opción 1: Cargar `test_cases/conjunto1.txt`
   - Opción 3: Ejecutar simulación
   - Opción 3: Round Robin
   - Quantum: 4 (o cualquier valor)

3. **Debería funcionar correctamente** y mostrar el Diagrama de Gantt sin errores

---

## 📝 Notas Técnicas

**¿Por qué fallaba?**
Cuando el quantum es pequeño (ej: 1 o 2) y el tiempo acumulado es grande (ej: 26+), el cálculo:
```
entry.second * 2 - std::to_string(currentTime).length() + 1
```
podía resultar en un número negativo o cero, causando que `std::string` lance una excepción.

**Ejemplo del problema:**
- Quantum = 1 → entry.second = 1
- currentTime = 100 → std::to_string(100).length() = 3
- Cálculo: 1 * 2 - 3 + 1 = 0 (problema!)

**Solución:**
Con el ancho mínimo y `std::max()`, siempre garantizamos un tamaño válido:
```cpp
int spaceNeeded = std::max(1, width - timeStr.length() + 1);
```

---

## ✨ Mejoras Adicionales

La corrección también incluye:
- Validación de entrada vacía (mejor manejo de errores)
- Diagrama más legible incluso con quantums pequeños
- Código más robusto y mantenible

---

**El error está corregido y el programa debería funcionar correctamente ahora.** ✅

