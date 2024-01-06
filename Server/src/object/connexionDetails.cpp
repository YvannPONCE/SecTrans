#include <iostream>
#include <string>
#include <vector>

#include "../../header/object/connexionDetails.h"

ConnexionDetails::ConnexionDetails(int port, std::string pubKey) : _pubKey(pubKey), _port(port)  {}


std::string ConnexionDetails::getPubKey(){
    return this->_pubKey;
}

int ConnexionDetails::getPort(){
    return this->_port;
}