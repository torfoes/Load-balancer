#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "RequestQueue.h"
#include "Request.h"
#include "WebServer.h"
#include <vector>

class LoadBalancer {
public:
    LoadBalancer(std::vector<WebServer>& servers);
    void addRequest(const Request& request);
    void balanceLoad();
    void addServer(const WebServer& server);
    int getRequestQueueSize() const;


private:
    std::vector<WebServer>& servers;
    RequestQueue requestQueue;
};

#endif
