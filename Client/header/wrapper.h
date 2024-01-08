// wrapper.h

#ifndef Wrapper_H
#define Wrapper_H

class Wrapper {
public:
    static std::string getType(std::string request);
    static std::string wrapINIT(int port, std::string pubKey);
    static std::string unwrappPUBK(std::string request);
    static std::string wrapFILE(char* data);
private:
};

#endif
