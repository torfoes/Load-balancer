#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>

class RequestQueue {
public:
    void addRequest(const Request& request);
    Request getNextRequest();
    bool isEmpty() const;

private:
    std::queue<Request> queue;
};

#endif
