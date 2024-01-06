// engine.h

#ifndef Wrapper_H
#define Wrapper_H

class Wrapper {
public:
    static std::string getType(std::string request);
    static std::string wrapPUBK(std::string pubKey);
    static void unWrappInit(const std::string &request, int &port, std::string &clientPublicKey);
private:
};

#endif
