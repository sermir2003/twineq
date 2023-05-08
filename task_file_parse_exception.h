#pragma once
#include <stdexcept>

class TaskFileParseException : public std::runtime_error {
public:
    TaskFileParseException(const std::string& error_message) : std::runtime_error(error_message) {
    }
};
