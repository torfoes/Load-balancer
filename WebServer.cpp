#include "WebServer.h"
#include <iostream>

WebServer::WebServer() : available(true) {}

void WebServer::handleRequest(const Request& request) {
    if (available) {
        std::cout << "Handling request from " << request.getIpIn() 
                  << " to " << request.getIpOut() 
                  << " for " << request.getTime() << " ms." << std::endl;
        available = false;
        finishTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(request.getTime());
    }
}

bool WebServer::isAvailable() {
    update();
    return available;
}

void WebServer::update() {
    if (!available && std::chrono::steady_clock::now() >= finishTime) {
        available = true;
    }
}
