@echo off
echo Compilando Simulador de Planificacion de CPU...
echo.

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

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilacion exitosa!
    echo Ejecutable creado: scheduler_simulator.exe
    echo.
    echo Para ejecutar: scheduler_simulator.exe
) else (
    echo.
    echo Error en la compilacion.
    echo Asegurese de tener g++ instalado (MinGW).
)

pause

