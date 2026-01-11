#  Explicación Técnica Detallada del Proyecto
Scheduler
    │
    ├── FCFS
    ├── SJF
    ├── RoundRobin
    └── PriorityScheduler
```

**Principio usado:** Herencia y Polimorfismo
- Cada algoritmo hereda de `Scheduler`
- Todos implementan el método virtual `schedule()`
- Permite agregar nuevos algoritmos fácilmente

---

## ANÁLISIS DETALLADO DE CADA ALGORITMO

### 1. FCFS (First Come First Served)

**Pseudocódigo:**
```
1. Ordenar procesos por tiempo de llegada
2. Para cada proceso en orden:
   a. Esperar hasta su tiempo de llegada
   b. Ejecutar hasta completarse
   c. Marcar como terminado
```

**Código clave en fcfs.cpp:**
```cpp
std::sort(processes.begin(), processes.end(), 
    [](const Process& a, const Process& b) {
        return a.getArrivalTime() < b.getArrivalTime();
    });

for (auto& process : processes) {
    if (currentTime < process.getArrivalTime()) {
        currentTime = process.getArrivalTime();
    }
    executeProcess(process, currentTime, process.getBurstTime());
}
```

**Complejidad temporal:** O(n log n) por el ordenamiento

**Características:**
-  No apropiativo (no interrumpe)
-  Simple de implementar
-  Puede causar convoy effect (proceso largo bloquea a otros)
-  Alto tiempo de espera promedio

---

### 2. SJF (Shortest Job First)

**Pseudocódigo:**
```
1. Mientras haya procesos sin completar:
   a. Encontrar proceso con menor ráfaga que haya llegado
   b. Si no hay, avanzar tiempo hasta próximo proceso
   c. Ejecutar proceso encontrado hasta completarse
   d. Repetir
```

**Código clave en sjf.cpp:**
```cpp
Process* getShortestJob(int currentTime) {
    Process* shortest = nullptr;
    int shortestBurst = INT_MAX;
    
    for (auto& process : processes) {
        if (process.getState() != ProcessState::TERMINATED &&
            process.getArrivalTime() <= currentTime) {
            if (process.getBurstTime() < shortestBurst) {
                shortestBurst = process.getBurstTime();
                shortest = &process;
            }
        }
    }
    return shortest;
}
```

**Complejidad temporal:** O(n²) - busca proceso más corto en cada iteración

**Características:**
-  Minimiza tiempo promedio de espera
-  Óptimo para minimizar tiempo de retorno promedio
-  Puede causar inanición (starvation)
-  Requiere conocer el tiempo de ráfaga de antemano

---

### 3. Round Robin

**Pseudocódigo:**
```
1. Crear cola de procesos listos
2. Agregar procesos que llegan al tiempo 0
3. Mientras haya procesos sin completar:
   a. Si cola vacía, avanzar tiempo hasta próximo proceso
   b. Tomar primer proceso de la cola
   c. Ejecutar por quantum o hasta terminar
   d. Si no terminó, agregar al final de la cola
   e. Agregar procesos nuevos que lleguen durante ejecución
```

**Código clave en round_robin.cpp:**
```cpp
std::queue<int> readyQueue;
int executionTime = std::min(quantum, currentProcess.getRemainingTime());
executeProcess(currentProcess, startTime, executionTime);

if (currentProcess.getState() != ProcessState::TERMINATED) {
    readyQueue.push(currentIndex);  // Volver a la cola
}
```

**Complejidad temporal:** O(n × tiempo_total / quantum)

**Características:**
-  Justo - todos reciben tiempo equitativo
-  Buen tiempo de respuesta
-  No causa inanición
- Overhead por cambios de contexto frecuentes
-  Quantum configurable afecta rendimiento

**Efecto del quantum:**
- Quantum muy pequeño → Muchos cambios de contexto → Overhead alto
- Quantum muy grande → Similar a FCFS → Mal tiempo de respuesta
- Quantum óptimo: Balance entre overhead y respuesta

---

### 4. Priority Scheduling

**Versión Sin Desalojo (Non-Preemptive):**

**Pseudocódigo:**
```
1. Mientras haya procesos sin completar:
   a. Encontrar proceso con mayor prioridad (menor número) que haya llegado
   b. Si no hay, avanzar tiempo
   c. Ejecutar proceso hasta completarse
```

**Versión Con Desalojo (Preemptive):**

**Pseudocódigo:**
```
1. En cada unidad de tiempo:
   a. Encontrar proceso con mayor prioridad que haya llegado
   b. Si es diferente al actual, desalojar actual
   c. Ejecutar proceso de mayor prioridad por 1 unidad
   d. Si terminó, marcar como completado
   e. Repetir
```

**Código clave en priority.cpp:**
```cpp
Process* getHighestPriorityProcess(int currentTime) {
    Process* highest = nullptr;
    int highestPriority = INT_MAX;  // Menor número = mayor prioridad
    
    for (auto& process : processes) {
        if (process.getState() != ProcessState::TERMINATED &&
            process.getArrivalTime() <= currentTime) {
            if (process.getPriority() < highestPriority) {
                highestPriority = process.getPriority();
                highest = &process;
            }
        }
    }
    return highest;
}
```

**Complejidad temporal:** 
- Sin desalojo: O(n²)
- Con desalojo: O(n × tiempo_total)

**Características:**
-  Permite priorizar procesos importantes
-  Útil para sistemas en tiempo real
- Puede causar inanición para baja prioridad
-  Prioridades deben asignarse cuidadosamente

---

## SISTEMA DE MÉTRICAS

### Fórmulas Implementadas

**1. Turnaround Time (Tiempo de Retorno)**
```
T_turnaround = T_finalizacion - T_llegada
```
- **Significado:** Tiempo total desde que el proceso llega hasta que termina
- **Unidad:** Unidades de tiempo

**2. Waiting Time (Tiempo de Espera)**
```
T_espera = T_turnaround - T_rafaga
```
- **Significado:** Tiempo que el proceso espera en cola sin ejecutarse
- **Relación:** Es el turnaround menos el tiempo que realmente usó CPU

**3. Response Time (Tiempo de Respuesta)**
```
T_respuesta = T_primera_ejecucion - T_llegada
```
- **Significado:** Tiempo hasta que el proceso recibe CPU por primera vez
- **Importante:** Mide la responsividad del sistema

**4. CPU Utilization (Utilización de CPU)**
```
U_CPU = (Tiempo_CPU_usado / Tiempo_total) × 100%
```
- **Significado:** Porcentaje de tiempo que la CPU está ocupada
- **Rango:** 0% a 100%

### Implementación en metrics.cpp

```cpp
SystemMetrics calculateSystemMetrics(const std::vector<Process>& processes, int totalTime) {
    double sumTurnaround = 0;
    double sumWaiting = 0;
    double sumResponse = 0;
    int totalBurstTime = 0;
    
    for (const auto& process : processes) {
        sumTurnaround += process.getTurnaroundTime();
        sumWaiting += process.getWaitingTime();
        sumResponse += process.getResponseTime();
        totalBurstTime += process.getBurstTime();
    }
    
    metrics.averageTurnaroundTime = sumTurnaround / processes.size();
    metrics.averageWaitingTime = sumWaiting / processes.size();
    metrics.averageResponseTime = sumResponse / processes.size();
    metrics.cpuUtilization = (static_cast<double>(totalBurstTime) / totalTime) * 100.0;
    
    return metrics;
}
```

---

##  DIAGRAMA DE GANTT

**Formato de salida:**
```
|----|--|------|
| P1 |P2|  P3  |
|----|--|------|
0    4  8      17
```

**Interpretación:**
- Cada barra representa ejecución continua
- Los números debajo son tiempos
- Muestra el orden de ejecución visualmente

**Implementación:**
```cpp
void printGanttChart(const std::vector<std::pair<int, int>>& ganttChart) {
    // ganttChart contiene: {process_id, duration}
    // Dibuja barras proporcionales al tiempo
}
```

---

## 🔄 FLUJO DE EJECUCIÓN DEL PROGRAMA

```
main()
  ↓
UserInterface::printMainMenu()
  ↓
Usuario selecciona opción
  ↓
[Opción 1] → FileHandler::loadProcessesFromFile()
[Opción 2] → UserInterface::createProcessManually()
[Opción 3] → Crear Scheduler específico
              ↓
              scheduler->schedule()
              ↓
              MetricsCalculator::printProcessMetrics()
              ↓
              MetricsCalculator::printSystemMetrics()
              ↓
              MetricsCalculator::printGanttChart()
[Opción 4] → UserInterface::printProcessList()
[Opción 5] → Ejecutar todos los algoritmos
              ↓
              MetricsCalculator::compareAlgorithms()
```

---

##  ESTRUCTURA DE DATOS UTILIZADAS

### std::vector<Process>
- **Uso:** Almacenar lista de procesos
- **Ventaja:** Acceso aleatorio O(1), tamaño dinámico

### std::queue<int>
- **Uso:** Cola en Round Robin
- **Ventaja:** FIFO automático, O(1) push/pop

### std::map<std::string, SystemMetrics>
- **Uso:** Almacenar resultados de comparación
- **Ventaja:** Búsqueda ordenada, acceso por clave

### std::pair<int, int>
- **Uso:** Diagrama de Gantt {process_id, duration}
- **Ventaja:** Estructura simple para tuplas

---
##  DECISIONES DE DISEÑO

### 1. ¿Por qué clases separadas para cada algoritmo?
**Respuesta:** Principio de responsabilidad única. Cada algoritmo tiene su propia lógica y puede evolucionar independientemente.

### 2. ¿Por qué una clase base Scheduler?
**Respuesta:** Polimorfismo. Permite tratar todos los algoritmos de manera uniforme y facilita comparación.

### 3. ¿Por qué guardar procesos originales y una copia?
**Respuesta:** Los procesos originales mantienen datos iniciales. La copia se modifica durante la simulación. Al final, se actualizan los originales con las métricas calculadas.

### 4. ¿Por qué calcular métricas por separado?
**Respuesta:** Separación de responsabilidades. Los algoritmos solo planifican. Las métricas se calculan después, independientemente del algoritmo.

---

##  FUNCIONES AUXILIARES IMPORTANTES

### executeProcess()
```cpp
void Scheduler::executeProcess(Process& process, int startTime, int duration) {
    process.setState(ProcessState::RUNNING);
    process.setStartTime(startTime);  // Solo primera vez
    // Actualiza tiempos ejecutados y restantes
    // Actualiza estado
    // Agrega al diagrama de Gantt
}
```

### reset()
```cpp
void Scheduler::reset() {
    // Restaura procesos a estado inicial
    // Limpia diagrama de Gantt
    // Resetea tiempo actual
}
```

---

##  COMPARACIÓN DE COMPLEJIDAD

| Algoritmo | Complejidad Temporal | Complejidad Espacial |
|-----------|---------------------|---------------------|
| FCFS      | O(n log n)          | O(n)                |
| SJF       | O(n²)               | O(n)                |
| Round Robin| O(n × T/q)          | O(n)                |
| Prioridades (NP) | O(n²)        | O(n)                |
| Prioridades (P)  | O(n × T)           | O(n)                |

*Donde: n = número de procesos, T = tiempo total, q = quantum*

---

##  CONCEPTOS DE SISTEMAS OPERATIVOS APLICADOS

1. **Estados de Proceso:** Nuevo, Listo, Ejecutando, Terminado
2. **Cola de Listos:** Procesos esperando CPU
3. **Desalojo (Preemption):** Interrumpir proceso en ejecución
4. **Quantum:** Unidad de tiempo en Round Robin
5. **Cambio de Contexto:** Cambiar de un proceso a otro (implícito en el código)
6. **Inanición (Starvation):** Proceso nunca recibe CPU
7. **Fairness:** Equidad en distribución de CPU

---

##  MEJORAS POSIBLES (Opcional para mencionar)

Si preguntan sobre mejoras futuras:

1. **SRTF (Shortest Remaining Time First):** SJF apropiativo
2. **Multilevel Queue:** Múltiples colas con diferentes algoritmos
3. **Multilevel Feedback Queue:** Procesos cambian de cola
4. **Interfaz Gráfica:** Visualización más rica
5. **Exportar Resultados:** Guardar métricas en CSV/PDF
6. **Simulación de I/O:** Procesos que bloquean esperando I/O


