#include <string>
#include <iostream>

#include "../header/wrapper.h"

std::string Wrapper::wrap(std::string hostname, int port, std::string pubKey){
    return "INIT#" + hostname + "#" + std::to_string(port) + "#" + pubKey ;
}