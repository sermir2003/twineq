#pragma once
#include <string>
#include "problem.h"

enum class InputRequestType {
    CREATE_PROBLEM_FILE,
    SOLVE,
    HELP,
};

struct InputRequest {
    virtual InputRequestType GetType() = 0;
    virtual ~InputRequest() {
    }
};

struct RequestCreateProblemFile : public InputRequest {
    InputRequestType GetType() override {
        return InputRequestType::CREATE_PROBLEM_FILE;
    }
    std::string path_to_problem_file;
    RequestCreateProblemFile(const std::string& in_path_to_problem_file)
        : path_to_problem_file(in_path_to_problem_file) {
    }
    RequestCreateProblemFile(std::string&& in_path_to_problem_file)
        : path_to_problem_file(std::move(in_path_to_problem_file)) {
    }
};

struct RequestSolve : public InputRequest {
    InputRequestType GetType() override {
        return InputRequestType::SOLVE;
    }
    Problem problem;
    RequestSolve(Problem&& in_problem) : problem(std::move(in_problem)) {
    }
};

struct RequestHelp : public InputRequest {
    InputRequestType GetType() override {
        return InputRequestType::HELP;
    }
    RequestHelp() = default;
};
