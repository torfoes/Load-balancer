#include "LoadBalancer.h"
#include "Request.h"
#include "WebServer.h"
#include <vector>

int main() {
    // Create a few web servers
    WebServer server1;
    WebServer server2;
    WebServer server3;

    // Add them to a vector
    std::vector<WebServer> servers = {server1, server2, server3};

    // Create a LoadBalancer with the servers
    LoadBalancer loadBalancer(servers);

    // Create a few requests
    Request request1("Request 1");
    Request request2("Request 2");
    Request request3("Request 3");
    Request request4("Request 4");

    // Balance the load for each request
    loadBalancer.balanceLoad(request1);
    loadBalancer.balanceLoad(request2);
    loadBalancer.balanceLoad(request3);
    loadBalancer.balanceLoad(request4);

    return 0;
}
