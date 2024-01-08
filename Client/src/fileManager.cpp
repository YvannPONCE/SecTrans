#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sys/stat.h>

#include "./../header/fileManager.h"

#define CHUNK_SIZE 1024
#define FOLDER_PATH "./Files"


void FileManager::InitFileSystem(){
    if (!std::filesystem::exists(FOLDER_PATH)){
        if (mkdir(FOLDER_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
            std::cerr << "Error creating folder." << std::endl;
        }
    }
}

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


void FileManager::registerFile(std::string fileName, std::string  data){
    
    std::string filePath = FOLDER_PATH + static_cast<std::string>("/") + fileName ;
    // Open the file in output mode, which erases the file if it already exists
    std::ofstream outputFile(filePath);

    if (outputFile.is_open()) {
        // Write the string to the file
        outputFile << data;

        // Close the file
        outputFile.close();

        std::cout << "File registered at : " << filePath << std::endl;
    } else {
        std::cerr << "Error opening file for writing." << std::endl;
        return; // Return an error code
    }
}
