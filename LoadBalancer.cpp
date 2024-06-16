#include "LoadBalancer.h"

LoadBalancer::LoadBalancer(std::vector<WebServer>& servers) : servers(servers) {}

void LoadBalancer::addRequest(const Request& request) {
    requestQueue.addRequest(request);
}

void LoadBalancer::balanceLoad() {
    // update the status of all servers
    for (auto& server : servers) {
        server.update();
    }
    
    // assign requests to available servers
    static size_t serverIndex = 0;
    while (!requestQueue.isEmpty()) {
        if (servers[serverIndex].isAvailable()) {
            servers[serverIndex].handleRequest(requestQueue.getNextRequest());
        }
        serverIndex = (serverIndex + 1) % servers.size();
    }
}

void LoadBalancer::addServer(const WebServer& server) {
    servers.push_back(server);
}

int LoadBalancer::getRequestQueueSize() const {
    return requestQueue.size();
}