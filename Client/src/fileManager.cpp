#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "./../header/fileManager.h"

#define CHUNK_SIZE 1024

namespace fileManager{

    std::vector<std::string> read(std::filesystem::path filePath) {
        
        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            std::cerr << "Unable to open file" << std::endl;
            return std::vector<std::string>();
        } 

        char buffer[CHUNK_SIZE];
        std::vector<std::string> fileData;
        fileData.push_back(filePath.filename().string());

        while (!inputFile.eof()) {
            // Read a slice of data from the file
            inputFile.read(buffer, CHUNK_SIZE);

            // Get the number of characters actually read
            std::streamsize bytesRead = inputFile.gcount();

            // Add the slice to the vector as a string
            fileData.push_back(std::string(buffer, bytesRead));
        }

        inputFile.close();

        return fileData;
    }


    std::vector<std::string> wrap(std::vector<std::string> fileData)
    {
        fileData.push_back("###EOF###");
        return fileData;
    }

    void print(std::vector<std::string> fileData)
    {
        std::cout << "FileName : " << fileData.front() << std::endl;
       for (auto it = fileData.begin() + 1; it != fileData.end(); ++it)  {
            std::cout << *it;
        }
        std::cout << std::endl;
    }

}