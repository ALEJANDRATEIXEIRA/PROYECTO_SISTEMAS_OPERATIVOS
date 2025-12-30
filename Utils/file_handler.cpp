#include "file_handler.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Process> FileHandler::loadProcessesFromFile(const std::string& filename) {
    std::vector<Process> processes;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        return processes;
    }
    
    std::string line;
    // Saltar la primera línea si es un encabezado
    if (std::getline(file, line)) {
        // Verificar si es encabezado (contiene "Proceso" o "Process")
        if (line.find("Proceso") == std::string::npos && 
            line.find("Process") == std::string::npos &&
            line.find("ID") == std::string::npos) {
            // No es encabezado, procesar esta línea
            file.seekg(0);
        }
    } else {
        file.seekg(0);
    }
    
    int id = 1;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        
        while (iss >> token) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 3) {
            int arrivalTime = std::stoi(tokens[1]);
            int burstTime = std::stoi(tokens[2]);
            int priority = (tokens.size() >= 4) ? std::stoi(tokens[3]) : 1;
            
            processes.push_back(Process(id, arrivalTime, burstTime, priority));
            id++;
        }
    }
    
    file.close();
    return processes;
}

bool FileHandler::saveProcessesToFile(const std::vector<Process>& processes, const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo " << filename << std::endl;
        return false;
    }
    
    file << "Proceso\tLlegada\tRáfaga\tPrioridad\n";
    for (const auto& process : processes) {
        file << "P" << process.getId() << "\t"
             << process.getArrivalTime() << "\t"
             << process.getBurstTime() << "\t"
             << process.getPriority() << "\n";
    }
    
    file.close();
    return true;
}

void FileHandler::createDefaultTestFiles() {
    // Conjunto 1: Procesos Básicos
    std::ofstream file1("test_cases/conjunto1.txt");
    if (file1.is_open()) {
        file1 << "Proceso\tLlegada\tRáfaga\tPrioridad\n";
        file1 << "P1\t0\t8\t3\n";
        file1 << "P2\t1\t4\t1\n";
        file1 << "P3\t2\t9\t4\n";
        file1 << "P4\t3\t5\t2\n";
        file1.close();
    }
    
    // Conjunto 2: Procesos Variados
    std::ofstream file2("test_cases/conjunto2.txt");
    if (file2.is_open()) {
        file2 << "Proceso\tLlegada\tRáfaga\tPrioridad\n";
        file2 << "P1\t0\t10\t2\n";
        file2 << "P2\t2\t3\t1\n";
        file2 << "P3\t4\t6\t3\n";
        file2 << "P4\t6\t1\t1\n";
        file2 << "P5\t8\t4\t2\n";
        file2.close();
    }
}

