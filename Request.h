#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
public:
    Request(const std::string& ipIn, const std::string& ipOut, int time);
    std::string getIpIn() const;
    std::string getIpOut() const;
    int getTime() const;

private:
    std::string ipIn;
    std::string ipOut;
    int time;
};

#endif
