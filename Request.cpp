#include "Request.h"

Request::Request(const std::string& ipIn, const std::string& ipOut, int time)
    : ipIn(ipIn), ipOut(ipOut), time(time) {}

std::string Request::getIpIn() const {
    return ipIn;
}

std::string Request::getIpOut() const {
    return ipOut;
}

int Request::getTime() const {
    return time;
}
