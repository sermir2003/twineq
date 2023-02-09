#include <nlohmann/json.hpp>
#include <fstream>
#include <memory>
#include "task_file_io.h"
#include "kernels.h"
#include "real_number.h"
#include <iostream>

using Json = nlohmann::json;

Json file_content = {
    {"Problem", "Twin equation"},
    {"kernel", {
        {"type", "Exponential"},
        {"A", "1"},
        {"B", "1"}}
    },
    {"b", "1"},
    {"d'", "1"},
    {"r", "20"},
    {"grid count", "5001"},
    {"iteration count", "1000"},
    {"path to result file", "plot.txt"},
    {"Integration method", "Column"},
    {"Iteration method", "Matrix"},
};

void TaskFileIO::CreateFile(const std::string& path_to_file) {
    std::ofstream file(path_to_file, std::ios::out);
    file << std::setw(4) << file_content << std::endl;
}

Task TaskFileIO::ParseTaskFile(const std::string& path_to_file) {
    std::ifstream file(path_to_file, std::ios::in);
    Json data_json;
    file >> data_json;
    try {
        Task task;
        std::string type_of_problem_str = data_json["Problem"].get<std::string>();
        if (type_of_problem_str == "Twin equation") {
            task.problem_ = ProblemType::TWIN_EQUATION;
        } else if (type_of_problem_str == "Original equation") {
            task.problem_ = ProblemType::ORIGINAL_EQUATION;
        } else {
            throw TaskFileParseException("Unknown problem type.");
        }
        if (data_json["kernel"]["type"].get<std::string>() == "Exponential") {
            Real A, B;
            try {
                A = std::stod(data_json["kernel"]["A"].get<std::string>());
                B = std::stod(data_json["kernel"]["B"].get<std::string>());
            } catch (...) {
                throw TaskFileParseException("Incorrect Exponential Kernel parameters.");
            }
            task.kernels_ = std::make_unique<DanchenkoExpKernels>(A, B);
        } else if (data_json["kernel"]["type"].get<std::string>() == "Rational") {
            Real A, p;
            try {
                A = std::stod(data_json["kernel"]["A"].get<std::string>());
                p = std::stod(data_json["kernel"]["p"].get<std::string>());
            } catch (...) {
                throw TaskFileParseException("Incorrect Exponential Kernel parameters.");
            }
            task.kernels_ = std::make_unique<DanchenkoRationalKernels>(A, p);
        } else {
            throw TaskFileParseException("Unknown kernel type.");
        }
        task.b_ = std::stod(data_json["b"].get<std::string>());
        task.s_ = std::stod(data_json["d'"].get<std::string>());
        task.r_ = std::stod(data_json["r"].get<std::string>());
        task.grid_count_ = std::stoi(data_json["grid count"].get<std::string>());
        task.iter_count_ = std::stoi(data_json["iteration count"].get<std::string>());
        task.path_to_result_file_ = data_json["path to result file"].get<std::string>();
        std::string int_method = data_json["Integration method"].get<std::string>();
        if (int_method == "Column") {
            task.integration_method_ = IntegratorType::COLUMN;
        } else if (int_method == "Trapezoid") {
            task.integration_method_ = IntegratorType::TRAPEZOID;
        } else if (int_method == "Simpsons") {
            task.integration_method_ = IntegratorType::SIMPSONS;
        } else {
            throw TaskFileParseException("Unknown integration method.");
        }
        std::string iter_method = data_json["Iteration method"].get<std::string>();
        if (iter_method == "Manual") {
            task.iteration_method_ = IterationType::MANUAL;
        } else if (iter_method == "Matrix") {
            task.iteration_method_ = IterationType::MATRIX;
        } else {
            throw TaskFileParseException("Unknown iteration method.");
        }
        task.N_ = task.kernels_->getN();
        task.step_size_ = 2 * task.r_ / (task.grid_count_ - 1);
        return task;
    } catch (const nlohmann::json_abi_v3_11_2::detail::type_error& exception) {
        if (std::string(exception.what()) ==
            "[json.exception.type_error.302] type must be string, but is null") {
            throw TaskFileParseException("Some task parameters are missing");
        } else {
            throw TaskFileParseException(
                "Unknown parsing error related to "
                "nlohmann::json_abi_v3_11_2::detail::type_error with what [" +
                std::string(exception.what()) + "]");
        }
    } catch (...) {
        throw TaskFileParseException("Unknown parsing error.");
    }
}
