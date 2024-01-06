// fileManager.h

#include <filesystem>

#ifndef FileManager_H
#define FileManager_H

class FileManager {
public:
    static std::string read(std::filesystem::path filePath);
    static void print(std::vector<std::string> fileData);
private:
};

#endif
