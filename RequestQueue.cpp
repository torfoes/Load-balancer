#include "RequestQueue.h"

void RequestQueue::addRequest(const Request& request) {
    queue.push(request);
}

Request RequestQueue::getNextRequest() {
    Request request = queue.front();
    queue.pop();
    return request;
}

bool RequestQueue::isEmpty() const {
    return queue.empty();
}

int RequestQueue::size() const {
    return queue.size();
}
