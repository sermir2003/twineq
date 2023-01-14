#pragma once
#include <string>
#include "task.h"

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
    std::string path_to_task_file;
    RequestCreateTaskFile(const std::string& path_to_task_file)
        : path_to_task_file(path_to_task_file) {
    }
    RequestCreateTaskFile(std::string&& path_to_task_file)
        : path_to_task_file(std::move(path_to_task_file)) {
    }
};

struct RequestSolve : public InputRequest {
    InputRequestType GetType() override {
        return InputRequestType::SOLVE;
    }
    Task task;
    RequestSolve(Task&& in_task) : task(std::move(in_task)) {
    }
};

struct RequestHelp : public InputRequest {
    InputRequestType GetType() override {
        return InputRequestType::HELP;
    }
    RequestHelp() = default;
};
