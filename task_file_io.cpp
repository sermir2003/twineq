#include <nlohmann/json.hpp>
#include <fstream>
#include <memory>
#include "task_file_io.h"
#include "kernels.h"

using Json = nlohmann::json;

Json file_content = {{"Problem", "Twin equation"},
                     {"kernel", {{"type", "Exponential"}, {"A", "1"}, {"B", "1"}}},
                     {"b", "1"},
                     {"d'", "1"},
                     {"r", "20"},
                     {"grid count", "5001"},
                     {"iteration count", "1000"},
                     {"path to result file", "plot.txt"},
                     {"Integration method", "Column"}};

void TaskFileIO::CreateFile(const std::string& path_to_file) {
    std::ofstream file(path_to_file, std::ios::out);
    file << std::setw(4) << file_content << std::endl;
}

Task TaskFileIO::ParseTaskFile(const std::string& path_to_file) {
    std::ifstream file(path_to_file, std::ios::in);
    Json data_json;
    file >> data_json;
    try {
        std::string type_of_problem_str = data_json["Problem"].get<std::string>();
        ProblemType type_of_problem;
        if (type_of_problem_str == "Twin equation") {
            type_of_problem = ProblemType::TWIN_EQUATION;
        } else if (type_of_problem_str == "Original equation") {
            type_of_problem = ProblemType::ORIGINAL_EQUATION;
        } else {
            throw TaskFileParseException("Unknown integration method.");
        }
        std::unique_ptr<Kernels> kernels = nullptr;
        if (data_json["kernel"]["type"].get<std::string>() == "Exponential") {
            double A, B;
            try {
                A = std::stod(data_json["kernel"]["A"].get<std::string>());
                B = std::stod(data_json["kernel"]["A"].get<std::string>());
            } catch (...) {
                throw TaskFileParseException("Incorrect Exponential Kernel parameters.");
            }
            kernels = std::make_unique<DanchenkoExpKernels>(A, B);
        } else if (data_json["kernel"]["type"].get<std::string>() == "Rational") {
            double A, p;
            try {
                A = std::stod(data_json["kernel"]["A"].get<std::string>());
                p = std::stod(data_json["kernel"]["p"].get<std::string>());
            } catch (...) {
                throw TaskFileParseException("Incorrect Exponential Kernel parameters.");
            }
            kernels = std::make_unique<DanchenkoRationalKernels>(A, p);
        } else {
            throw TaskFileParseException("Unknown kernel type.");
        }
        double b = std::stod(data_json["b"].get<std::string>());
        double s = std::stod(data_json["d'"].get<std::string>());
        double r = std::stod(data_json["r"].get<std::string>());
        double grid_count = std::stod(data_json["grid count"].get<std::string>());
        double iteration_count = std::stod(data_json["iteration count"].get<std::string>());
        std::string path_to_result_file = data_json["path to result file"].get<std::string>();
        std::string int_method = data_json["Integration method"].get<std::string>();
        IntegratorType type_of_integrator;
        if (int_method == "Column") {
            type_of_integrator = IntegratorType::COLUMN;
        } else if (int_method == "Trapezoid") {
            type_of_integrator = IntegratorType::TRAPEZOID;
        } else if (int_method == "Simpsons") {
            type_of_integrator = IntegratorType::SIMPSONS;
        } else {
            throw TaskFileParseException("Unknown integration method.");
        }
        double N = kernels->getN();
        return Task(b, s, r, N, grid_count, iteration_count, std::move(kernels),
                    true, path_to_result_file, type_of_integrator, type_of_problem);
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
