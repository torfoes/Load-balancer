#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
public:
    Request(const std::string& content);
    std::string getContent() const;

private:
    std::string content;
};

#endif
