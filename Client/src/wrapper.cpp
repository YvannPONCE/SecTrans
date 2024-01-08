#include <string>
#include <iostream>

#include "../header/wrapper.h"

std::string Wrapper::getType(std::string request){
    return request.substr(0, 4);
}

std::string Wrapper::wrapINIT(int port, std::string pubKey){
    return std::to_string(port) + "#" + pubKey;
}

std::string Wrapper::wrapFILE(char* data){
    
    return  "";
}


std::string Wrapper::unwrappPUBK(std::string request){
    return request.substr(5);
}