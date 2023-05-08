#include <iostream>
#include <string>
#include <memory>
#include "cmd_args_parser.h"
#include "task.h"
#include "solution_launcher.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<InputRequest> request;
    try {
        request = CMDArgsParser::Parse(argc, argv);
    } catch (const ParseException& exception) {
        std::cout << "ERROR: incorrect parameters\n"
                  << exception.what()
                  << "\nYou can get more information using the command 'twineq --help'"
                  << std::endl;
        return 0;
    }
    if (request->GetType() == InputRequestType::CREATE_TASK_FILE) {
        std::string file_path = static_cast<RequestCreateTaskFile*>(request.get())->file_path;
        Task::CreateTaskFile(file_path);
    } else if (request->GetType() == InputRequestType::SOLVE) {
        std::string file_path = static_cast<RequestCreateTaskFile*>(request.get())->file_path;
        Task task(file_path);
        SolutionLauncher(std::move(task));
    } else if (request->GetType() == InputRequestType::HELP) {
        std::cout << "Instructions for compiling and running are in README.md on the website\n"
                     "https://github.com/sermir2003/twineq\n"
                  << std::endl;
    }
    return 0;
}
