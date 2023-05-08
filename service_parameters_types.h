#pragma once
#include "task_file_parse_exception.h"

enum class ProblemType {
    TWIN_EQUATION,
    ORIGINAL_EQUATION,
};

ProblemType StrToProblemType(const std::string& str);

enum class IterationType {
    MANUAL,
    MATRIX,
};

IterationType StrToIterationType(const std::string& str);

enum class IntegratorType {
    COLUMN,
    TRAPEZOID,
    SIMPSONS,
};

IntegratorType StrToIntegratorType(const std::string& str);
