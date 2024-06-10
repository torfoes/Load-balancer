#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "RequestQueue.h"
#include "Request.h"
#include "WebServer.h"
#include <vector>

class LoadBalancer {
public:
    LoadBalancer(std::vector<WebServer>& servers);
    void balanceLoad(Request& request);

private:
    std::vector<WebServer>& servers;
};

#endif
