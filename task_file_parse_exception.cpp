#include "service_parameters_types.h"

ProblemType StrToProblemType(const std::string& str) {
    if (str == "Twin equation") {
        return ProblemType::TWIN_EQUATION;
    } else if (str == "Original equation") {
        return ProblemType::ORIGINAL_EQUATION;
    }
    throw TaskFileParseException("Unknown problem type");
}

IterationType StrToIterationType(const std::string& str) {
    if (str == "Manual") {
        return IterationType::MANUAL;
    } else if (str == "Matrix") {
        return IterationType::MATRIX;
    }
    throw TaskFileParseException("Unknown iteration method");
}

IntegratorType StrToIntegratorType(const std::string& str) {
    if (str == "Column") {
        return IntegratorType::COLUMN;
    } else if (str == "Trapezoid") {
        return IntegratorType::TRAPEZOID;
    } else if (str == "Simpsons") {
        return IntegratorType::SIMPSONS;
    }
    throw TaskFileParseException("Unknown integration method");
}
