// FileManager.h
#include<vector>

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

class FileManager {
private:

public:
    // Constructor
    FileManager();

    static std::string readFile(std::string username , std::string fileName);
    static std::vector<std::string> wrap(std::vector<std::string> fileData);
    static void print(std::vector<std::string> fileData);
    static void createFolder(std::string username);
    static void registerFile(std::string username, std::string fileName, std::string  data);
    static std::vector<std::string> list(std::string username);
};

#endif
