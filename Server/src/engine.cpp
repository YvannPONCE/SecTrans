#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <filesystem>

#include "../header/engine.h"
#include "../header/wrapper.h"
#include "../header/encryptionManager.h"
#include "../header/client.h"

Engine::Engine(): _encryptionManager(), _client(5002), _authentification(), _fileManager() {}

void Engine::processRequest(std::string request){
    std::string type = request.substr(0,4);
    request = request.substr(5);

    if(type == "INIT"){
         
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);
        std::string clientPublicKey= requestParameters[1];

        _encryptionManager.setClientPublicKey(clientPublicKey);
        _client.sendmsg("PUBK#", _encryptionManager.getPublicKey());
    }
    else if (type == "FILE")
    {   
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);

        std::cout << std::endl;
        std::string plainUsername = _encryptionManager.decrypt(requestParameters[0]);
        std::cout << std::endl;
        std::string plainPassword = _encryptionManager.decrypt(requestParameters[1]);
        std::cout << std::endl;
        std::string plainFileName = _encryptionManager.decrypt(requestParameters[2]);
        std::cout << std::endl;
        std::string sha256DataFile = requestParameters[4];
        std::string computeSha256 = EncryptionManager::sha256(requestParameters[3]);

        if(sha256DataFile != computeSha256){
            _client.sendmsg("CORR#","");
        }

        std::string username = EncryptionManager::sha256(plainUsername);
        std::string password = EncryptionManager::sha256(plainPassword);

        if(!_authentification.login(username, password)){
            _client.sendmsg("DEND#","");
        }
         _fileManager.registerFile(username, plainFileName, requestParameters[3]);
        _client.sendmsg("SUCC#","");
           
    } else if (type == "LIST")
    {
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);

        std::cout << std::endl;
        std::string plainUsername = _encryptionManager.decrypt(requestParameters[0]);
        std::cout << std::endl;
        std::string plainPassword = _encryptionManager.decrypt(requestParameters[1]);

        std::string username = EncryptionManager::sha256(plainUsername);
        std::string password = EncryptionManager::sha256(plainPassword);

        if(!_authentification.login(username, password)){
            _client.sendmsg("DEND#","");
        }
        std::vector<std::string> fileNames = FileManager::list(username);
        sendRequest(fileNames);
    } else if (type == "DOWN")
    {
        std::vector<std::string> requestParameters = Wrapper::unWrappRequest(request);

        std::cout << std::endl;
        std::string plainUsername = _encryptionManager.decrypt(requestParameters[0]);
        std::cout << std::endl;
        std::string plainPassword = _encryptionManager.decrypt(requestParameters[1]);
        std::cout << std::endl;
        std::string plainFileName = _encryptionManager.decrypt(requestParameters[2]);

        std::string username = EncryptionManager::sha256(plainUsername);
        std::string password = EncryptionManager::sha256(plainPassword);

        if(!_authentification.login(username, password)){
            _client.sendmsg("DEND#","");
        }
        std::string cypherFileData = FileManager::readFile(username, plainFileName);

        std::cout << " "<<std::endl;
        std::string cypherFileName = _encryptionManager.encrypt(plainFileName);
        
        sendRequest(cypherFileName , cypherFileData);
    }   
}



void Engine::sendRequest( std::vector<std::string> fileNames){
    std::string request = Wrapper::wrapLIST(fileNames);
    _client.sendmsg("LIST#" , request);
}

void Engine::sendRequest(std::string fileName, std::string fileData){
    std::string request = fileName + static_cast<std::string>("#") + fileData + static_cast<std::string>("#") + EncryptionManager::sha256(fileData);
    _client.sendmsg("FILE#" , request);
}