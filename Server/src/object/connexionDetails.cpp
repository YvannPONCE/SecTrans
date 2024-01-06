#include <iostream>
#include <string>
#include <vector>

#include "../../header/object/connexionDetails.h"

ConnexionDetails::ConnexionDetails(std::string hostname, int port, std::string pubKey) : _hostname(hostname), _pubKey(pubKey), _port(port)  {}

std::string ConnexionDetails::getHostname(){
    return this->_hostname;
}

std::string ConnexionDetails::getPubKey(){
    return this->_pubKey;
}

int ConnexionDetails::getPort(){
    return this->_port;
}