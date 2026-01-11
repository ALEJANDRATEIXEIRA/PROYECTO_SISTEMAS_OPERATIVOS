# Guía Rápida 

### 1. INTRODUCCIÓN RÁPIDA
```
"Simulador de algoritmos de planificación de CPU que implementa 
FCFS, SJF, Round Robin y Prioridades para comparar rendimiento."
```

---

### 2. EJECUTAR Y DEMOSTRAR (12 min)

**Abrir terminal y ejecutar:**
```cmd
cd "C:\Users\asus\Documents\proyecto SO"
scheduler_simulator.exe
```

**Secuencia en el programa:**

1. **Cargar caso de prueba**
   ```
   → 1 (Cargar archivo)
   → test_cases/conjunto1.txt
   ```

2. **Ver procesos** (opcional, rápido)
   ```
   → 4 (Ver procesos)
   → Enter
   ```

3. **Ejecutar FCFS**
   ```
   → 3 (Ejecutar simulación)
   → 1 (FCFS)
   → Mostrar resultados
   → Explicar: "Orden de llegada, simple"
   → Enter
   ```

4. **Ejecutar SJF**
   ```
   → 3
   → 2 (SJF)
   → Mostrar resultados
   → Explicar: "Proceso más corto primero"
   → Enter
   ```

5. **Ejecutar Round Robin**
   ```
   → 3
   → 3 (Round Robin)
   → Quantum: 4
   → Mostrar Diagrama de Gantt
   → Explicar: "Quantum, justo, sin inanición"
   → Enter
   ```

6. **Ejecutar Prioridades**
   ```
   → 3
   → 4 (Prioridades Sin Desalojo)
   → Mostrar resultados
   → Explicar: "Por prioridad"
   → Enter
   ```

7. **COMPARAR TODOS** 
   ```
   → 5 (Comparar todos)
   → Mostrar tabla comparativa
   → Explicar diferencias
   → Señalar mejor algoritmo
   → Enter
   ```

8. **Salir**
   ```
   → 6 (Salir)
   ```

---

### 3️. EXPLICACIÓN TÉCNICA RÁPIDA (2 min)

**Puntos clave a mencionar:**

- **Arquitectura:** Modular (Core, algorithms, UI, Utils)
- **Proceso:** Tiene ID, llegada, ráfaga, prioridad, estado
- **Métricas:** Turnaround, Waiting, Response Time
- **Diferencia algoritmos:** Estrategia de selección diferente

---

## DATOS DEL CASO DE PRUEBA 1

```
P1: Llega=0,  Ráfaga=8,  Prioridad=3
P2: Llega=1,  Ráfaga=4,  Prioridad=1
P3: Llega=2,  Ráfaga=9,  Prioridad=4
P4: Llega=3,  Ráfaga=5,  Prioridad=2
```

**Resultados esperados para referencia:**

- **FCFS:** P1→P2→P3→P4 (orden de llegada)
- **SJF:** P2→P4→P1→P3 (orden por ráfaga: 4, 5, 8, 9)
- **Round Robin (q=4):** Alterna procesos
- **Prioridades:** P2→P4→P1→P3 (orden por prioridad: 1, 2, 3, 4)

---

## RESUMEN 

**FCFS:**
> "First Come First Served ejecuta procesos en el orden que llegan. Es simple pero puede tener alto tiempo de espera si un proceso largo llega primero."

**SJF:**
> "Shortest Job First selecciona el proceso con menor tiempo de ráfaga. Minimiza el tiempo promedio de espera pero puede causar inanición."

**Round Robin:**
> "Round Robin usa un quantum de tiempo. Cada proceso recibe su turno equitativo, garantizando respuesta rápida y evitando inanición."

**Prioridades:**
> "Planificación por prioridades permite dar preferencia a procesos importantes. Puede ser con o sin desalojo según la implementación."

---




