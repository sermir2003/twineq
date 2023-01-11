#pragma once
#include <string>
#include "problem.h"

const std::string kProblemFileDefaultName = "ProblemFile.json";

class ProblemFileIO {
public:
    static void CreateFile(const std::string& path_to_file=kProblemFileDefaultName);
    static Problem ParseProblemFile(const std::string& path_to_file=kProblemFileDefaultName);
};
