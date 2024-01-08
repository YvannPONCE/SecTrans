#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "../header/wrapper.h"

std::string Wrapper::getType(std::string request){
    return request.substr(0, 4);
}

std::string Wrapper::wrapLIST(std::vector<std::string> fileNames){
    std::string request;
    for (std::string fileName : fileNames) {
        fileName = fileName+ static_cast<std::string>("#");
        request = request + fileName;
    }
    return request;
}

std::vector<std::string> Wrapper::unWrappRequest(const std::string &request){
    std::istringstream ss(request);

    std::vector<std::string> parts;
    std::string part;

    while (std::getline(ss, part, '#')) {
        parts.push_back(part);
    }

    return parts;
}

