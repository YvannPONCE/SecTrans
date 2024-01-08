#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <sys/stat.h>

#include "./../header/fileManager.h"

#define CHUNK_SIZE 1024
#define FOLDER_PATH "./Files"

FileManager::FileManager(){
    if (!std::filesystem::exists(FOLDER_PATH)){
        if (mkdir(FOLDER_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
            std::cerr << "Error creating folder." << std::endl;
        }
    }
}


std::string FileManager::readFile(std::string username , std::string fileName) {
    
    std::filesystem::path filePath(FOLDER_PATH + static_cast<std::string>("/") + username + static_cast<std::string>("/") + fileName);
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


std::vector<std::string> FileManager::wrap(std::vector<std::string> fileData)
{
    fileData.push_back("###EOF###");
    return fileData;
}

void FileManager::createFolder(std::string username){
    std::string path = static_cast<std::string>(FOLDER_PATH) + static_cast<std::string>("/") + username;
     if (!std::filesystem::exists(path.c_str())){
        if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
            std::cerr << "Error creating folder : " << username << std::endl;
        }
     }
}

void FileManager::registerFile(std::string username, std::string fileName, std::string  data){
        
    std::string filePath = FOLDER_PATH + static_cast<std::string>("/") + username + static_cast<std::string>("/") + fileName ;
    // Open the file in output mode, which erases the file if it already exists
    std::ofstream outputFile(filePath);

    if (outputFile.is_open()) {
        // Write the string to the file
        outputFile << data;

        // Close the file
        outputFile.close();

        //std::cout << "File registered at : " << filePath << std::endl;
    } else {
        std::cerr << "Error opening file for writing." << std::endl;
        return; // Return an error code
    }

}

std::vector<std::string> FileManager::list(std::string username){
    std::vector<std::string> fileNames;
    std::filesystem::path folderPath(static_cast<std::string>(FOLDER_PATH) + static_cast<std::string>("/") + username );

    try {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            fileNames.push_back(entry.path().filename().string());
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing the folder: " << e.what() << std::endl;
        return fileNames; // Return an error code
    }
    return fileNames;
}