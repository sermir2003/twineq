#include "input_subsystem.h"
#include "input_request.h"
#include "problem_file_io.h"

std::vector<std::string> InputSubsystem::ParseToVectorString(size_t argc, char **argv) {
    std::vector<std::string> strings(argc);
    for (size_t i = 0; i < argc; ++i) {
        strings[i] = std::string(argv[i]);
    }
    return strings;
}

std::unique_ptr<InputRequest> InputSubsystem::Input(size_t argc, char **argv) {
    std::string program_name = std::string(argv[0]);
    --argc;
    argv = &argv[1];
    std::vector<std::string> tokens = InputSubsystem::ParseToVectorString(argc, argv);
    if (tokens.empty()) {
        throw ParserExceptionIncorrectParameters("There are no parameters, launch is impossible.");
    }
    else {
        if (tokens[0] == "newtask") {
            if (tokens.size() > 2) {
                throw ParserExceptionIncorrectParameters("The '" + program_name + "' should be followed by the path to the file to be created or nothing to create a file with the default name. However, the number of parameters is not conducive to this.");
            }
            else if (tokens.size() == 2) {
                return std::unique_ptr<InputRequest>(new RequestCreateProblemFile(tokens[1]));
            }
            else if (tokens.size() == 1) {
                return std::unique_ptr<InputRequest>(new RequestCreateProblemFile(kProblemFileDefaultName));
            }
        }
        else if (tokens[0] == "solve") {
            if (tokens.size() > 2) {
                throw ParserExceptionIncorrectParameters("The 'solve' should be followed by the path to the Problem File or nothing to use a file with a default name. However, the number of parameters is not conducive to this.");
            }
            else if (tokens.size() == 2) {
                return std::unique_ptr<InputRequest>(new RequestSolve(ProblemFileIO::ParseProblemFile(tokens[1])));
            }
            else if (tokens.size() == 1) {
                return std::unique_ptr<InputRequest>(new RequestSolve(ProblemFileIO::ParseProblemFile(kProblemFileDefaultName)));
            }
        }
        else if (tokens[0] == "-h" || tokens[0] == "--help") {
            if (tokens.size() != 1) {
                throw ParserExceptionIncorrectParameters("There are too many parameters for the help command.");
            } else {
                return std::unique_ptr<InputRequest>(new RequestHelp());
            }
        }
        else {
            throw ParserExceptionIncorrectParameters("Invalid key.");
        }
    }
    return std::unique_ptr<InputRequest>(nullptr);
}
