# 🎓 Guía Completa para la Defensa del Proyecto
## Simulador de Algoritmos de Planificación de CPU

---

## ✅ ESTADO DEL PROYECTO

**¡SÍ, EL PROYECTO ESTÁ LISTO!**

Tu proyecto tiene:
- ✅ 4 algoritmos implementados (FCFS, SJF, Round Robin, Prioridades)
- ✅ Sistema de métricas completo
- ✅ Interfaz de usuario funcional
- ✅ Casos de prueba obligatorios
- ✅ Ejecutable compilado (`scheduler_simulator.exe`)
- ✅ Código estructurado y comentado

---

## 📋 PARTE 1: COMPILACIÓN PASO A PASO

### Método 1: Usando el Script (MÁS FÁCIL)

1. **Abre el Explorador de Archivos**
   - Navega a: `C:\Users\asus\Documents\proyecto SO`

2. **Haz doble clic en `compile.bat`**
   - O abre PowerShell/CMD y ejecuta:
   ```cmd
   cd "C:\Users\asus\Documents\proyecto SO"
   compile.bat
   ```

3. **Verifica que se haya creado `scheduler_simulator.exe`**
   - El archivo debería aparecer en la carpeta del proyecto

---

### Método 2: Compilación Manual (Para Demostrar)

Si quieres mostrar cómo compilas desde cero:

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

**Explicación del comando:**
- `g++`: Compilador de C++
- `-std=c++17`: Usa el estándar C++17
- `-Wall -O2`: Habilita advertencias y optimización
- `-o scheduler_simulator.exe`: Nombre del ejecutable
- Luego lista todos los archivos `.cpp` a compilar

---

## 🎯 PARTE 2: CÓMO FUNCIONA EL PROYECTO

### Arquitectura del Sistema

```
┌─────────────────────────────────────────┐
│         main.cpp (Programa Principal)   │
│         - Menú de usuario               │
│         - Coordina todo                 │
└──────────────┬──────────────────────────┘
               │
       ┌───────┴────────┐
       │                │
┌──────▼──────┐  ┌──────▼─────────┐
│   UI/       │  │  Utils/        │
│ interface   │  │ file_handler   │
└──────┬──────┘  └──────┬─────────┘
       │                │
       └───────┬────────┘
               │
      ┌────────▼─────────┐
      │   Core/          │
      │ - Process        │ ← Representa un proceso
      │ - Scheduler      │ ← Clase base abstracta
      └────────┬─────────┘
               │
      ┌────────▼──────────────────┐
      │   algorithms/              │
      │ - FCFS                     │
      │ - SJF                      │
      │ - RoundRobin               │
      │ - PriorityScheduler        │
      └────────┬───────────────────┘
               │
      ┌────────▼─────────┐
      │   metrics.cpp    │
      │ - Calcula métricas│
      │ - Muestra resultados│
      └──────────────────┘
```

---

### Componentes Principales Explicados

#### 1. **Core/process.h y process.cpp**
**¿Qué es?** Clase que representa un proceso

**Atributos:**
- `id`: Identificador único (P1, P2, etc.)
- `arrivalTime`: Cuándo llega el proceso al sistema
- `burstTime`: Cuánto tiempo necesita de CPU
- `priority`: Prioridad (menor número = mayor prioridad)
- `state`: Estado actual (Nuevo, Listo, Ejecutando, Terminado)

**Métricas que calcula:**
- `turnaroundTime`: Tiempo total (finalización - llegada)
- `waitingTime`: Tiempo esperando en cola
- `responseTime`: Tiempo hasta primera ejecución

**Ejemplo:**
```cpp
Process p1(1, 0, 8, 3);  // ID=1, Llega=0, Ráfaga=8, Prioridad=3
```

---

#### 2. **Core/scheduler.h y scheduler.cpp**
**¿Qué es?** Clase base abstracta para todos los algoritmos

**Responsabilidades:**
- Gestionar lista de procesos
- Mantener Diagrama de Gantt
- Proporcionar estructura común

**Método clave:**
- `virtual void schedule() = 0;` - Cada algoritmo lo implementa

---

#### 3. **algorithms/fcfs.cpp** - First Come First Served
**¿Cómo funciona?**

```
1. Ordena procesos por tiempo de llegada
2. Ejecuta cada proceso hasta completarse
3. El primero en llegar se ejecuta primero
4. No hay interrupciones
```

**Ejemplo visual:**
```
Procesos: P1(llega=0, ráfaga=8), P2(llega=1, ráfaga=4)

Tiempo:  0--------8--------12
         |   P1   |  P2  |
         
P1 espera: 0 (empieza inmediatamente)
P2 espera: 7 (espera que P1 termine)
```

**Ventajas:** Simple, justo (orden de llegada)
**Desventajas:** Puede tener alto tiempo de espera promedio

---

#### 4. **algorithms/sjf.cpp** - Shortest Job First
**¿Cómo funciona?**

```
1. En cada momento, selecciona el proceso con menor ráfaga
2. Ejecuta hasta completarse
3. No es apropiativo (no interrumpe)
```

**Ejemplo:**
```
Procesos: P1(0, 8), P2(1, 4), P3(2, 9)

Orden de ejecución: P1 → P2 → P3 (por ráfaga: 4 < 8 < 9)
Pero espera a que lleguen todos...

Tiempo:  0--4--8----17
         |P2|P1|  P3 |
```

**Ventajas:** Minimiza tiempo promedio de espera
**Desventajas:** Puede causar inanición (starvation) para procesos largos

---

#### 5. **algorithms/round_robin.cpp** - Round Robin
**¿Cómo funciona?**

```
1. Cada proceso recibe un "quantum" de tiempo (ej: 4 unidades)
2. Si no termina, se mueve al final de la cola
3. Proceso siguiente en la cola se ejecuta
4. Repite hasta que todos terminen
```

**Ejemplo (quantum=4):**
```
Procesos: P1(0, 8), P2(1, 4), P3(2, 9)

Cola inicial: [P1, P2, P3]
Tiempo 0-4:  Ejecuta P1 (queda 4 unidades)
Tiempo 4-8:  Ejecuta P2 (termina)
Tiempo 8-12: Ejecuta P3 (queda 5 unidades)
Tiempo 12-16: Ejecuta P1 (termina)
Tiempo 16-21: Ejecuta P3 (termina)

Tiempo:  0-4 4-8 8-12 12-16 16-21
         |P1 |P2 | P3 | P1 | P3 |
```

**Ventajas:** Justo, respuesta rápida, no hay inanición
**Desventajas:** Overhead por cambios de contexto

---

#### 6. **algorithms/priority.cpp** - Prioridades
**¿Cómo funciona?**

**Versión Sin Desalojo:**
```
1. Selecciona proceso con mayor prioridad (menor número)
2. Ejecuta hasta completarse
3. Luego selecciona el siguiente
```

**Versión Con Desalojo:**
```
1. En cada unidad de tiempo, revisa si hay proceso de mayor prioridad
2. Si llega uno de mayor prioridad, interrumpe el actual
3. Proceso desalojado vuelve a cola lista
```

**Ejemplo:**
```
Procesos: P1(0, 8, prioridad=3), P2(1, 4, prioridad=1)

Sin desalojo: P1 se ejecuta completo, luego P2
Con desalojo: P2 interrumpe a P1 porque tiene mayor prioridad
```

**Ventajas:** Permite dar prioridad a procesos importantes
**Desventajas:** Riesgo de inanición para procesos de baja prioridad

---

#### 7. **metrics.cpp**
**¿Qué calcula?**

1. **Por Proceso:**
   - Turnaround Time = Tiempo Finalización - Tiempo Llegada
   - Waiting Time = Turnaround Time - Burst Time
   - Response Time = Tiempo Primera Ejecución - Tiempo Llegada

2. **Del Sistema:**
   - Promedios de todas las métricas
   - CPU Utilization = (Tiempo CPU usado / Tiempo total) × 100%

3. **Comparación:**
   - Compara todos los algoritmos
   - Identifica el mejor algoritmo (menor tiempo de espera promedio)

---

#### 8. **UI/interface.cpp**
**¿Qué hace?**

- Muestra menú interactivo
- Permite cargar procesos desde archivo
- Permite crear procesos manualmente
- Muestra resultados en formato tabla

---

#### 9. **Utils/file_handler.cpp**
**¿Qué hace?**

- Lee procesos desde archivos de texto
- Formato: `Proceso Llegada Ráfaga Prioridad`
- Crea archivos de casos de prueba por defecto

---

## 🎤 PARTE 3: CÓMO PRESENTAR Y DEMOSTRAR

### ESTRUCTURA RECOMENDADA PARA LA PRESENTACIÓN

#### 1. INTRODUCCIÓN (2-3 minutos)
```
"Buenos días/tardes. Nuestro proyecto es un simulador de algoritmos 
de planificación de CPU que implementa 4 algoritmos principales:
FCFS, SJF, Round Robin y Prioridades. Permite analizar y comparar 
el rendimiento de cada algoritmo bajo diferentes cargas de trabajo."
```

---

#### 2. DEMOSTRACIÓN PRÁCTICA (8-10 minutos)

**PASO 1: Mostrar la Estructura del Código**
```
"Tenemos una arquitectura modular:
- Core: Clases base (Process, Scheduler)
- algorithms: Implementación de los 4 algoritmos
- UI: Interfaz de usuario
- Utils: Utilidades como manejo de archivos
- metrics: Cálculo de métricas de rendimiento"
```

**PASO 2: Compilar el Proyecto (Si es necesario)**
```cmd
# Abrir terminal y mostrar:
compile.bat

# Explicar: "Compilamos todos los archivos .cpp en un ejecutable"
```

**PASO 3: Ejecutar el Simulador**
```cmd
scheduler_simulator.exe
```

**PASO 4: Cargar Caso de Prueba Obligatorio**
```
1. Seleccionar opción 1: "Cargar procesos desde archivo"
2. Ingresar: test_cases/conjunto1.txt
3. Mostrar que se cargaron 4 procesos correctamente
```

**PASO 5: Ejecutar Cada Algoritmo**

**A) FCFS:**
```
1. Opción 3: "Ejecutar simulación"
2. Opción 1: "FCFS"
3. Mostrar resultados:
   - Métricas por proceso
   - Métricas del sistema
   - Diagrama de Gantt
4. Explicar: "FCFS ejecuta en orden de llegada, simple pero puede tener alto tiempo de espera"
```

**B) SJF:**
```
1. Opción 3 → Opción 2: "SJF"
2. Mostrar resultados
3. Explicar: "SJF minimiza tiempo de espera eligiendo el proceso más corto primero"
```

**C) Round Robin:**
```
1. Opción 3 → Opción 3: "Round Robin"
2. Pedir quantum: 4
3. Mostrar resultados
4. Explicar: "Round Robin es justo, cada proceso recibe un quantum de tiempo. Evita inanición."
```

**D) Prioridades:**
```
1. Opción 3 → Opción 4: "Prioridades Sin Desalojo"
2. Mostrar resultados
3. Explicar: "Selecciona por prioridad (menor número = mayor prioridad)"
```

**PASO 6: Comparar Todos los Algoritmos**
```
1. Opción 5: "Comparar todos los algoritmos"
2. Mostrar tabla comparativa
3. Señalar cuál es el mejor algoritmo para este caso
4. Explicar las diferencias
```

---

#### 3. EXPLICACIÓN TÉCNICA (3-4 minutos)

**Explicar cómo funciona UN algoritmo en detalle:**

Ejemplo con Round Robin:
```
"Round Robin funciona con una cola circular. Cada proceso recibe 
un quantum de tiempo. Si no termina, se mueve al final de la cola 
y el siguiente proceso se ejecuta. Esto garantiza que todos los 
procesos reciban tiempo de CPU de manera equitativa."
```

**Mostrar código relevante:**
- Abrir `algorithms/round_robin.cpp`
- Mostrar la función `schedule()`
- Explicar el uso de `std::queue` para la cola

---

#### 4. MÉTRICAS Y RESULTADOS (2-3 minutos)

**Explicar las fórmulas:**
```
"Calculamos 3 métricas principales:

1. Turnaround Time = Tiempo Finalización - Tiempo Llegada
   (Cuánto tiempo pasa desde que llega hasta que termina)

2. Waiting Time = Turnaround Time - Burst Time
   (Cuánto tiempo espera en cola sin ejecutarse)

3. Response Time = Primera Ejecución - Tiempo Llegada
   (Cuánto tarda en responder)

También calculamos la utilización de CPU y promedios del sistema."
```

---

#### 5. CONCLUSIÓN (1-2 minutos)
```
"En resumen, implementamos 4 algoritmos de planificación que son 
fundamentales en sistemas operativos. El simulador permite comparar 
su rendimiento y entender cuándo usar cada uno. Por ejemplo, Round 
Robin es bueno para sistemas interactivos, mientras que SJF minimiza 
el tiempo de espera pero puede causar inanición."
```

---

## 📝 SCRIPT DE DEMOSTRACIÓN PASO A PASO

### Secuencia Exacta para la Presentación:

```
1. [Abrir terminal]
   cd "C:\Users\asus\Documents\proyecto SO"
   
2. [Mostrar estructura]
   dir
   dir Core
   dir algorithms
   
3. [Compilar si es necesario - OPCIONAL]
   compile.bat
   
4. [Ejecutar]
   scheduler_simulator.exe
   
5. [En el programa]
   → Opción 1: Cargar archivo
   → Ingresar: test_cases/conjunto1.txt
   → Ver procesos cargados (Opción 4)
   
6. [Ejecutar FCFS]
   → Opción 3: Ejecutar simulación
   → Opción 1: FCFS
   → Explicar resultados
   
7. [Ejecutar SJF]
   → Opción 3
   → Opción 2: SJF
   → Explicar diferencias
   
8. [Ejecutar Round Robin]
   → Opción 3
   → Opción 3: Round Robin
   → Quantum: 4
   → Explicar diagrama de Gantt
   
9. [Ejecutar Prioridades]
   → Opción 3
   → Opción 4: Prioridades Sin Desalojo
   
10. [Comparar todos]
    → Opción 5: Comparar todos los algoritmos
    → Explicar tabla comparativa
    → Señalar mejor algoritmo
```

---

## 💡 PREGUNTAS FRECUENTES EN LA DEFENSA

### P: "¿Por qué elegiste C++?"
**R:** "C++ permite programación orientada a objetos, es eficiente para sistemas operativos, y nos permite implementar los algoritmos desde cero sin bibliotecas que hagan el trabajo por nosotros."

### P: "¿Cómo manejas las colas en Round Robin?"
**R:** "Uso una cola estándar (std::queue) que mantiene los procesos en orden FIFO. Cuando un proceso no termina en su quantum, lo agrego de nuevo al final de la cola."

### P: "¿Qué pasa si dos procesos tienen la misma prioridad?"
**R:** "En caso de empate, uso el tiempo de llegada como criterio de desempate. El que llegó primero tiene prioridad."

### P: "¿Por qué SJF no es apropiativo?"
**R:** "Implementamos la versión no apropiativa donde un proceso se ejecuta hasta completarse. La versión apropiativa sería SRTF (Shortest Remaining Time First), que sería más compleja."

### P: "¿Cómo calculas el tiempo de respuesta?"
**R:** "El tiempo de respuesta es la diferencia entre cuando un proceso ejecuta por primera vez (startTime) y cuando llegó al sistema (arrivalTime). Es importante porque mide la responsividad del sistema."

---

## ✅ CHECKLIST ANTES DE LA PRESENTACIÓN

- [ ] Proyecto compila sin errores
- [ ] Ejecutable funciona correctamente
- [ ] Casos de prueba están en test_cases/
- [ ] Código tiene comentarios importantes
- [ ] Sabes explicar cada algoritmo
- [ ] Has probado todos los algoritmos
- [ ] Conoces las fórmulas de las métricas
- [ ] Tienes respuestas para preguntas comunes
- [ ] Archivos de código están organizados
- [ ] README está completo

---

## 🎯 CONSEJOS FINALES

1. **Practica la demostración** antes de la presentación
2. **Prepara ejemplos específicos** para cada algoritmo
3. **Ten abierto el código** en tu editor para mostrar si te lo piden
4. **Explica el Diagrama de Gantt** claramente
5. **Compara resultados** entre algoritmos
6. **Sé honesto** sobre limitaciones si las hay
7. **Muestra entusiasmo** por lo que implementaste

---

**¡ÉXITO EN TU PRESENTACIÓN! 🚀**


