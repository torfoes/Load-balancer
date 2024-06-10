#include "Request.h"

Request::Request(const std::string& content) : content(content) {}

std::string Request::getContent() const {
    return content;
}
