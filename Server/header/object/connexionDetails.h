// Server.h

#ifndef CONNEXION_DETAILS_H
#define CONNEXION_DETAILS_H

class ConnexionDetails {
private:
    std::string _hostname;
    std::string _pubKey;
    int _port; 

public:
    // Constructor
    ConnexionDetails(std::string hostname, int port, std::string pubKey);

    std::string getHostname();
    std::string getPubKey(); 
    int getPort();
};

#endif
