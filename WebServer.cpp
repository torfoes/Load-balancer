#include "WebServer.h"
#include <iostream>
#include <fstream>

WebServer::WebServer(int id) : id(id), available(true) {}

void WebServer::handleRequest(const Request& request) {
    if (available) {
        std::ofstream logFile("server_log.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "Server " << id << " handling request from " 
                    << request.getIpIn() << " to " << request.getIpOut() 
                    << " for " << request.getTime() << " ms." << std::endl;
            logFile.close();
        } else {
            std::cerr << "Unable to open log file." << std::endl;
        }
        
        std::cout << "Server " << id << " handling request from " 
                  << request.getIpIn() << " to " << request.getIpOut() 
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

int WebServer::getId() const {
    return id;
}
