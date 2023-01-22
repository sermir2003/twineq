#pragma once
#include <string>
#include "task.h"
#include <stdexcept>

const std::string kTaskFileDefaultName = "TaskFile.json";

class TaskFileIO {
public:
    static void CreateFile(const std::string& path_to_file = kTaskFileDefaultName);
    static Task ParseTaskFile(const std::string& path_to_file = kTaskFileDefaultName);
};

class TaskFileParseException : public std::runtime_error {
public:
    TaskFileParseException(const std::string& error_message) : std::runtime_error(error_message) {
    }
};
