#include "WebServer.h"
#include <iostream>

void WebServer::handleRequest(const Request& request) {
    std::cout << "Handling request: " << request.getContent() << std::endl;
}
