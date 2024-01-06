// Server.h

#ifndef CONNEXION_DETAILS_H
#define CONNEXION_DETAILS_H

class ConnexionDetails {
private:
    std::string _pubKey;
    int _port; 

public:
    // Constructor
    ConnexionDetails(int port, std::string pubKey);

    std::string getPubKey(); 
    int getPort();
};

#endif
