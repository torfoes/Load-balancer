#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "RequestQueue.h"
#include "Request.h"
#include "WebServer.h"
#include <vector>

/**
 * @class LoadBalancer
 * @brief A class to manage the distribution of network requests across multiple web servers.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructs a LoadBalancer object.
     * 
     * @param servers A reference to a vector of WebServer objects.
     */
    LoadBalancer(std::vector<WebServer>& servers);

    /**
     * @brief Adds a request to the load balancer's queue.
     * 
     * @param request The request to be added.
     */
    void addRequest(const Request& request);

    /**
     * @brief Distributes the requests in the queue to the available servers.
     */
    void balanceLoad();

    /**
     * @brief Adds a server to the load balancer.
     * 
     * @param server The WebServer object to be added.
     */
    void addServer(const WebServer& server);

    /**
     * @brief Removes the last server from the load balancer.
     */
    void removeServer();

    /**
     * @brief Gets the number of requests in the queue.
     * 
     * @return The number of requests in the queue.
     */
    int getRequestQueueSize() const;

private:
    std::vector<WebServer>& servers;  ///< The list of servers managed by the load balancer.
    RequestQueue requestQueue;        ///< The queue to store incoming requests.
};

#endif
