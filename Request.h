#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @class Request
 * @brief A class to represent a network request with input and output IP addresses and a timestamp.
 */
class Request {
public:
    /**
     * @brief Constructs a Request object.
     * 
     * @param ipIn The input IP address.
     * @param ipOut The output IP address.
     * @param time The timestamp of the request.
     */
    Request(const std::string& ipIn, const std::string& ipOut, int time);

    /**
     * @brief Gets the input IP address.
     * 
     * @return The input IP address as a string.
     */
    std::string getIpIn() const;

    /**
     * @brief Gets the output IP address.
     * 
     * @return The output IP address as a string.
     */
    std::string getIpOut() const;

    /**
     * @brief Gets the timestamp of the request.
     * 
     * @return The timestamp of the request as an integer.
     */
    int getTime() const;

private:
    std::string ipIn;  ///< The input IP address.
    std::string ipOut; ///< The output IP address.
    int time;          ///< The timestamp of the request.
};

#endif
