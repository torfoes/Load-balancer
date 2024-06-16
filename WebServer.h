#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <chrono>

class WebServer {
public:
    WebServer();
    void handleRequest(const Request& request);
    bool isAvailable();
    void update();

private:
    bool available;
    std::chrono::steady_clock::time_point finishTime;
};

#endif
