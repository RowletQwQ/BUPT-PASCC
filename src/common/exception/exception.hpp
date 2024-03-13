#pragma once

#include <exception>
#include <string>

namespace common {

class Exception : public std::exception {
private:
    std::string msg_;
public:
    Exception(const std::string &msg) : msg_(msg) {}
    virtual const char *what() const noexcept override {
        return msg_.c_str();
    }
};

class IRGenException : public Exception {
public:
    IRGenException(const std::string &msg) : Exception("[IRGen]" + msg) {}
};

class OptException : public Exception {
public:
    OptException(const std::string &msg) : Exception("[Optimize]" + msg) {}
};

} // namespace common