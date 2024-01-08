// fileManager.h

#include <filesystem>

#ifndef FileManager_H
#define FileManager_H

class FileManager {
public:
    static void InitFileSystem();
    static std::string read(std::filesystem::path filePath);
    static void print(std::vector<std::string> fileData);
    static void registerFile(std::string fileName, std::string  data);
private:
};

#endif
