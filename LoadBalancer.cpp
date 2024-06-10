#include "LoadBalancer.h"

LoadBalancer::LoadBalancer(std::vector<WebServer>& servers) : servers(servers) {}

void LoadBalancer::balanceLoad(Request& request) {
    // Simple round-robin load balancing for example
    static size_t serverIndex = 0;
    servers[serverIndex].handleRequest(request);
    serverIndex = (serverIndex + 1) % servers.size();
}
