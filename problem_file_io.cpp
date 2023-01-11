#include "problem_file_io.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "kernels.h"
// #include <iostream>
#include <memory>

using Json = nlohmann::json;

Json file_content = {
    {"kernel", {
                   {"type", "Exponential"},
                   {"A", "1"},
                   {"B", "1"}
               }},
    {"b", "1"},
    {"d'", "1"},
    {"r", "20"},
    {"grid count", "5001"},
    {"iteration count", "1000"},
    {"path to result file", "plot.txt"}
};

void ProblemFileIO::CreateFile(const std::string& path_to_file) {
    std::ofstream file(path_to_file, std::ios::out);
    file << std::setw(4) << file_content << std::endl;
}

Problem ProblemFileIO::ParseProblemFile(const std::string& path_to_file) {
    std::ifstream file(path_to_file, std::ios::in);
    Json data_json;
    file >> data_json;
    std::unique_ptr<Kernels> kernels = nullptr;
    if (data_json["kernel"]["type"].get<std::string>() == "Exponential") {
        double A = std::stod(data_json["kernel"]["A"].get<std::string>());
        double B = std::stod(data_json["kernel"]["A"].get<std::string>());
        kernels = std::unique_ptr<Kernels>(new ExpKernels(A, B));  // TODO: make without explicit new
        // std::cout << "Exponential A=" << A << " B=" << B << std::endl;
    }
    else if (data_json["kernel"]["type"].get<std::string>() == "Rational") {
        double A = std::stod(data_json["kernel"]["A"].get<std::string>());
        double p = std::stod(data_json["kernel"]["p"].get<std::string>());
        kernels = std::unique_ptr<Kernels>(new RationalKernels(A, p));  // TODO: make without explicit new
        // std::cout << "Rational A=" << A << " p=" << p << std::endl;
    }
    double b = std::stod(data_json["b"].get<std::string>());
    double s = std::stod(data_json["d'"].get<std::string>());
    double r = std::stod(data_json["r"].get<std::string>());
    double grid_count = std::stod(data_json["grid count"].get<std::string>());
    double iteration_count = std::stod(data_json["iteration count"].get<std::string>());
    std::string path_to_result_file = data_json["path to result file"].get<std::string>();
    // std::cout << "b=" << b << " d'=" << s << " r=" << r << " gcount=" << grid_count << " icount=" << iteration_count << std::endl;
    // std::cout << "w(-20)=" << kernels->w(-20) << std::endl;
    return Problem(std::move(kernels), b, s, r, grid_count, iteration_count, path_to_result_file);
}
