#include "task.h"
#include <nlohmann/json.hpp>
#include <fstream>

using Json = nlohmann::json;

Json file_content = {
    {"Problem", "Twin equation"},
    {"kernel", {{"type", "Exponential"}, {"A", 1}, {"B", 1}}},
    {"b", 1},
    {"d'", 1},
    {"r", 20},
    {"grid count", 5001},
    {"iteration count", 1000},
    {"path to result file", "plot.csv"},
    {"Integration method", "Column"},
    {"Iteration method", "Matrix"},
};

const std::string kTaskFileDefaultName = "TaskFile.json";

void Task::CreateTaskFile(std::string path_task_file) {
    if (path_task_file.empty()) {
        path_task_file = kTaskFileDefaultName;
    }
    std::ofstream file(path_task_file, std::ios::out);
    file << std::setw(4) << file_content << std::endl;
}
Task::Task(std::string path_task_file) {
    if (path_task_file.empty()) {
        path_task_file = kTaskFileDefaultName;
    }
    std::ifstream file(path_task_file, std::ios::in);
    Json data_json;
    file >> data_json;
    try {
        std::string type_of_problem_str = data_json["Problem"].get<std::string>();
        problem_ = StrToProblemType(type_of_problem_str);
        kernels_ = MakeKernels(data_json["kernel"]);
        b_ = data_json["b"].get<double>();
        s_ = data_json["d'"].get<double>();
        r_ = data_json["r"].get<double>();
        grid_count_ = data_json["grid count"].get<size_t>();
        iter_count_ = data_json["iteration count"].get<size_t>();
        path_to_result_file_ = data_json["path to result file"].get<std::string>();
        std::string int_method_str = data_json["Integration method"].get<std::string>();
        integration_method_ = StrToIntegratorType(int_method_str);
        std::string iter_method_str = data_json["Iteration method"].get<std::string>();
        iteration_method_ = StrToIterationType(iter_method_str);
        N_ = kernels_->getN();
        step_size_ = 2 * r_ / (grid_count_ - 1);
    } catch (const TaskFileParseException&) {
        throw;
    } catch (const nlohmann::json_abi_v3_11_2::detail::type_error& exception) {
        if (std::string(exception.what()) ==
            "[json.exception.type_error.302] type must be string, but is null") {
            throw TaskFileParseException("Most likely some task parameters are missing");
        } else {
            throw TaskFileParseException(
                "Unknown parsing error related to "
                "nlohmann::json_abi_v3_11_2::detail::type_error with what [" +
                std::string(exception.what()) + "]");
        }
    } catch (...) {
        throw TaskFileParseException("Unknown parsing error");
    }
}
