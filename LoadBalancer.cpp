#include "LoadBalancer.h"

LoadBalancer::LoadBalancer(std::vector<WebServer>& servers) : servers(servers) {}

void LoadBalancer::addRequest(const Request& request) {
    requestQueue.addRequest(request);
}

void LoadBalancer::balanceLoad() {
    // Update the status of all servers
    for (auto& server : servers) {
        server.update();
    }

    // Assign requests to available servers
    for (auto& server : servers) {
        if (!requestQueue.isEmpty() && server.isAvailable()) {
            server.handleRequest(requestQueue.getNextRequest());
        }
    }
}

void LoadBalancer::addServer(const WebServer& server) {
    servers.push_back(server);
}

int LoadBalancer::getRequestQueueSize() const {
    return requestQueue.size();
}

void LoadBalancer::removeServer() {
    if (!servers.empty()) {
        servers.pop_back();
    }
}