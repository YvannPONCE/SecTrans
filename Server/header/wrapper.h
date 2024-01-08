// engine.h

#ifndef Wrapper_H
#define Wrapper_H

class Wrapper {
public:
    static std::string getType(std::string request);
    static std::string wrapLIST(std::vector<std::string> fileNames);
    static std::vector<std::string> unWrappRequest(const std::string &request);
private:
};

#endif
