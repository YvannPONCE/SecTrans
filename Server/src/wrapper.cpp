#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "../header/wrapper.h"

std::string Wrapper::getType(std::string request){
    return request.substr(0, 4);
}

std::string Wrapper::wrapPUBK(std::string pubKey){
    return "PUBK#" + pubKey ;
}

void Wrapper::unWrappInit(const std::string &request, int &port, std::string &clientPublicKey){
    std::string subRequest = request.substr(5);
    std::istringstream ss(subRequest);

    std::vector<std::string> parts;
    std::string part;

    while (std::getline(ss, part, '#')) {
        parts.push_back(part);
    }

    std::istringstream(parts[0]) >> port;
    clientPublicKey = parts[1];
}