#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>

/**
 * @class RequestQueue
 * @brief A class to represent a queue of network requests.
 */
class RequestQueue {
public:
    /**
     * @brief Adds a request to the queue.
     * 
     * @param request The request to be added.
     */
    void addRequest(const Request& request);

    /**
     * @brief Retrieves and removes the next request from the queue.
     * 
     * @return The next request in the queue.
     */
    Request getNextRequest();

    /**
     * @brief Checks if the queue is empty.
     * 
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Gets the number of requests in the queue.
     * 
     * @return The number of requests in the queue.
     */
    int size() const;
    
private:
    std::queue<Request> queue;  ///< The queue to store requests.
};

#endif
