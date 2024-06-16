#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <chrono>

/**
 * @class WebServer
 * @brief A class to represent a web server that handles network requests.
 */
class WebServer {
public:
    /**
     * @brief Constructs a WebServer object.
     * 
     * @param id The identifier for the server.
     */
    WebServer(int id);

    /**
     * @brief Handles a network request.
     * 
     * @param request The request to be handled.
     */
    void handleRequest(const Request& request);

    /**
     * @brief Checks if the server is available to handle a request.
     * 
     * @return True if the server is available, false otherwise.
     */
    bool isAvailable();

    /**
     * @brief Updates the server's status based on the current time.
     */
    void update();

    /**
     * @brief Gets the server's identifier.
     * 
     * @return The server's identifier.
     */
    int getId() const;

private:
    int id;  ///< The identifier for the server.
    bool available;  ///< The availability status of the server.
    std::chrono::steady_clock::time_point finishTime;  ///< The time when the server will become available.
};

#endif
