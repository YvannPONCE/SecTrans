#include <string>
#include <iostream>
#include <sstream>

#include "../header/wrapper.h"
#include "../header/encryptionManager.h"

std::string Wrapper::getType(std::string request){
    return request.substr(0, 4);
}

std::string Wrapper::wrapINIT(int port, std::string pubKey){
    return std::to_string(port) + "#" + pubKey;
}

std::string Wrapper::wrapFILE(std::string cypherUsername, std::string cypherPassword, std::string cypherFileName, std::string cypherFileData){
    
    return cypherUsername +"#"+ cypherPassword +"#"+ cypherFileName +"#"+ cypherFileData+"#"+ EncryptionManager::sha256(cypherFileData);
}

std::string Wrapper::wrapDOWN(std::string cypherUsername, std::string cypherPassword, std::string cypherFileName){
    return cypherUsername +"#"+ cypherPassword +"#"+ cypherFileName;
}

std::string Wrapper::wrapLIST(std::string cypherUsername, std::string cypherPassword){
    
    return cypherUsername +"#"+ cypherPassword;
}

std::vector<std::string> Wrapper::unWrappRequest(std::string request){
    std::istringstream ss(request);

    std::vector<std::string> parts;
    std::string part;

    while (std::getline(ss, part, '#')) {
        parts.push_back(part);
    }

    return parts;
}