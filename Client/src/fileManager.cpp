#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "./../header/fileManager.h"

#define CHUNK_SIZE 1024



std::string FileManager::read(std::filesystem::path filePath) {
    
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return "";
    } 
    std::string fileContent((std::istreambuf_iterator<char>(inputFile)),
                            std::istreambuf_iterator<char>());
    
    inputFile.close();
    return fileContent;
}
void FileManager::print(std::vector<std::string> fileData)
{
    std::cout << "FileName : " << fileData.front() << std::endl;
   for (auto it = fileData.begin() + 1; it != fileData.end(); ++it)  {
        std::cout << *it;
    }
    std::cout << std::endl;
}
