// wrapper.h
#include<vector>

#ifndef Wrapper_H
#define Wrapper_H

class Wrapper {
public:
    static std::string getType(std::string request);
    static std::string wrapINIT(int port, std::string pubKey);
    static std::vector<std::string> unWrappRequest(std::string request);
    static std::string wrapFILE(std::string cypherUsername, std::string cypherPassword, std::string cypherFileName, std::string cypherFileData);
    static std::string wrapLIST(std::string cypherUsername, std::string cypherPassword);
    static std::string wrapDOWN(std::string cypherUsername, std::string cypherPassword, std::string cypherFileName);
};

#endif
