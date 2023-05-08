#pragma once
#include <string>

enum class InputRequestType {
    CREATE_TASK_FILE,
    SOLVE,
    HELP,
};

struct InputRequest {
    virtual InputRequestType GetType() = 0;
    virtual ~InputRequest() {
    }
};

struct RequestCreateTaskFile : public InputRequest {
    InputRequestType GetType() override {
        return InputRequestType::CREATE_TASK_FILE;
    }
    std::string file_path;
    RequestCreateTaskFile(const std::string& file_path) : file_path(file_path) {
    }
    RequestCreateTaskFile(std::string&& file_path) : file_path(std::move(file_path)) {
    }
};

struct RequestSolve : public InputRequest {
    InputRequestType GetType() override {
        return InputRequestType::SOLVE;
    }
    std::string file_path;
    RequestSolve(const std::string& file_path) : file_path(file_path) {
    }
    RequestSolve(std::string&& file_path) : file_path(std::move(file_path)) {
    }
};

struct RequestHelp : public InputRequest {
    InputRequestType GetType() override {
        return InputRequestType::HELP;
    }
    RequestHelp() = default;
};
