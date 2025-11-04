#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <stdexcept>
#include <string>

class KeeperException : public std::runtime_error {
public:
    KeeperException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif