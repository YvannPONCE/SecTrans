#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "./../header/fileREader.h"

#define CHUNK_SIZE 1024

std::vector<std::string> fileREader::read(std::string filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return std::vector<std::string>();
    } 

    char buffer[CHUNK_SIZE];
    std::vector<std::string> fileData;

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
