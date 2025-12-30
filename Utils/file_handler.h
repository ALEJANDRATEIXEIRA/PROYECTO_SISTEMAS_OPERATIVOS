#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../Core/process.h"
#include <vector>
#include <string>

class FileHandler {
public:
    static std::vector<Process> loadProcessesFromFile(const std::string& filename);
    static bool saveProcessesToFile(const std::vector<Process>& processes, const std::string& filename);
    static void createDefaultTestFiles();
};

#endif // FILE_HANDLER_H

