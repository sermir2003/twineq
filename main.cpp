#include <iostream>
#include <string>
#include <memory>
#include "input_subsystem.h"
#include "task_file_io.h"
#include "solution_launcher.h"

int main(int argc, char* argv[]) {
    std::unique_ptr<InputRequest> request;
    try {
        request = InputSubsystem::Parse(argc, argv);
    } catch (const ParseException& exception) {
        std::cout << "ERROR: incorrect parameters\n"
                  << exception.what()
                  << "\nYou can get more information using the command 'twineq --help'"
                  << std::endl;
        return 0;
    }
    if (request->GetType() == InputRequestType::CREATE_TASK_FILE) {
        TaskFileIO::CreateFile(
            static_cast<RequestCreateTaskFile*>(request.get())->path_to_task_file);
    }
    else if (request->GetType() == InputRequestType::SOLVE) {
        SolutionLauncher(std::move(static_cast<RequestSolve*>(request.get())->task));
    }
    else if (request->GetType() == InputRequestType::HELP) {
        std::cout << "The developer of this program needs help himself.\n"
                     "(function --help not implemented yet)" << std::endl;
    }
    return 0;
}
