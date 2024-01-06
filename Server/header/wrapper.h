// engine.h

#ifndef Wrapper_H
#define Wrapper_H

class Wrapper {
public:
    static std::string getType(std::string request);
    static void unWrappInit(const std::string &request, std::string &hostname, int &port, std::string &clientPublicKey);
private:
};

#endif
