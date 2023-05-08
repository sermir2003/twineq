#pragma once
#include <string>
#include <vector>
#include <memory>
#include "input_request.h"
#include <stdexcept>

class CMDArgsParser {
public:
    static std::unique_ptr<InputRequest> Parse(size_t argc, char *argv[]);

private:
    static std::vector<std::string> Tokenize(size_t argc, char *argv[]);
};

class ParseException : public std::runtime_error {
public:
    ParseException(const std::string &error_message) : std::runtime_error(error_message) {
    }
};
