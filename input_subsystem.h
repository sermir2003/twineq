#pragma once
#include <string>
#include <vector>
#include <memory>
#include "input_request.h"

class InputSubsystem {
public:
    static std::unique_ptr<InputRequest> Input(size_t argc, char *argv[]);
private:
    static std::vector<std::string> ParseToVectorString(size_t argc, char *argv[]);
};

class ParserExceptionIncorrectParameters {
private:
    std::string error_message_;
public:
    ParserExceptionIncorrectParameters(std::string error_message) : error_message_(error_message) {}
    std::string GetErrorMessage() const {
        return error_message_;
    }
};
