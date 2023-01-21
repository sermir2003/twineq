#include "task_file_io.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "kernels.h"
#include <memory>
#include "results_saver.h"

using Json = nlohmann::json;

Json file_content = {
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
    {"Solver method", "Manual"}
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
        std::unique_ptr<Kernels> kernels = nullptr;
        if (data_json["kernel"]["type"].get<std::string>() == "Exponential") {
            double A = std::stod(data_json["kernel"]["A"].get<std::string>());
            double B = std::stod(data_json["kernel"]["A"].get<std::string>());
            kernels = std::make_unique<ExpKernels>(A, B);
        } else if (data_json["kernel"]["type"].get<std::string>() == "Rational") {
            double A = std::stod(data_json["kernel"]["A"].get<std::string>());
            double p = std::stod(data_json["kernel"]["p"].get<std::string>());
            kernels = std::make_unique<RationalKernels>(A, p);
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
        if (int_method != "Column" && int_method != "Trapezoid" && int_method != "Simpsons") {
            throw TaskFileParseException("Unknown integration method.");
        }
        std::string solver_method = data_json["Solver method"].get<std::string>();
        if (solver_method != "Manual" && solver_method != "Matrix") {
            throw TaskFileParseException("Unknown solver.");
        }
        std::unique_ptr<ResultsSaver> res_saver = std::make_unique<FileResultsSaver>(grid_count, r, path_to_result_file);
        return Task(std::move(kernels), b, s, r, grid_count, iteration_count, std::move(res_saver),
                    int_method, solver_method);
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
