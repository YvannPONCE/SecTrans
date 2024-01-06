#include <string>
#include <iostream>

#include "../header/wrapper.h"

std::string Wrapper::getType(std::string request){
    return request.substr(0, 4);
}

std::string Wrapper::wrapINIT(int port, std::string pubKey){
    return "INIT#" + std::to_string(port) + "#" + pubKey;
}

std::string Wrapper::wrapFILE(std::string data){
    return "FILE#" + data;
}



std::string Wrapper::unwrappPUBK(std::string request){
    return request.substr(5);
}