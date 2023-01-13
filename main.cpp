#include <iostream>
#include <string>
#include "input_subsystem.h"
#include "solver.h"
#include "problem_file_io.h"
#include <memory>

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
    if (request->GetType() == InputRequestType::CREATE_PROBLEM_FILE) {
        ProblemFileIO::CreateFile(
            static_cast<RequestCreateProblemFile*>(request.get())->path_to_problem_file);
    }
    else if (request->GetType() == InputRequestType::SOLVE) {
        Solver solver_instance(std::move(
            static_cast<RequestSolve*>(request.get())->problem));
    }
    else if (request->GetType() == InputRequestType::HELP) {
        std::cout << "The developer of this program needs help himself.\n"
                     "(function --help not implemented yet)" << std::endl;
    }
    return 0;
}
