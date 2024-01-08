#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "../header/engine.h"
#include "../header/wrapper.h"
#include "../header/encryptionManager.h"
#include "../header/client.h"

#define MAX_SIZE 256

Engine::Engine(): _encryptionManager(), _client(5001), _server(5002) {
    FileManager::InitFileSystem();
    _encryptionManager.loadKeyFile();
}

void Engine::sendRequest(std::string type){
    if(type == "INIT"){
        std::string request = Wrapper::wrapINIT(5002, _encryptionManager.getPublicKey());
        _client.sendmsg("INIT#" , request.c_str());
        std::string response = waitForResponse();
        processRequest(response);
    }
}

void Engine::sendRequest(std::string type, std::string username, std::string password, std::string path){
    if (type == "FILE")
    {  
        std::string file_data = FileManager::read(std::filesystem::path(path));

        std::string cypherFileData = _encryptionManager.ownEncrypt(file_data);
        std::string cypherFileName = _encryptionManager.encrypt(std::filesystem::path(path).filename());
        std::string cypherUsername = _encryptionManager.encrypt(username);
        std::string cypherPassword = _encryptionManager.encrypt(password);

        std::string request = Wrapper::wrapFILE(cypherUsername, cypherPassword, cypherFileName, cypherFileData);
        _client.sendmsg("FILE#", request);
        std::string response = waitForResponse();
        processRequest(response);

    }else if(type == "DOWN"){
        std::cout <<""<< std::endl;
        std::string cypherFileName = _encryptionManager.encrypt(path);
        std::string cypherUsername = _encryptionManager.encrypt(username);
        std::string cypherPassword = _encryptionManager.encrypt(password);

        std::string request = Wrapper::wrapDOWN(cypherUsername, cypherPassword, cypherFileName);

        _client.sendmsg("DOWN#", request);
        std::string response = waitForResponse();
        processRequest(response);
    }
    
}

void Engine::sendRequest(std::string type, std::string username, std::string password){
    if (type == "LIST")
    {  
        std::cout <<""<< std::endl;
        std::string cypherUsername = _encryptionManager.encrypt(username);
        std::string cypherPassword = _encryptionManager.encrypt(password);

        std::string request = Wrapper::wrapLIST(cypherUsername, cypherPassword);
        _client.sendmsg("LIST#", request);
        std::string response = waitForResponse();
        processRequest(response);
    }
}

void Engine::processRequest(std::string request){
    std::string type = Wrapper::getType(request);
    request = request.substr(5);
    if(type == "PUBK"){
        _encryptionManager.setServerPublicKey(request);
    }
    else if (type == "FILE")
    {
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);

        std::cout <<""<< std::endl;
        std::string plainFileName = _encryptionManager.decrypt(requestParameters[0]);
        std::cout <<""<< std::endl;
        std::string plainFileData = _encryptionManager.decrypt(requestParameters[1]);

        FileManager::registerFile(plainFileName, plainFileData);        
    }
    else if (type == "LIST")
    {
        std::vector<std::string> fileNames = Wrapper::unWrappRequest(request);

        std::cout << "Files : " << std::endl;
        for (const auto& fileName : fileNames){
            std::cout << fileName << std::endl;
        }
    }
    else if (type == "DEND")
    {
        std::cout << "Wrong credentials" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if (type == "SUCC")
    {
        std::cout << "Operation succeed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "None" << std::endl;
    }
    
}

std::string Engine::waitForResponse(){
    return  _server.getRequest(); 
}