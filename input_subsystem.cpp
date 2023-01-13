#include "input_subsystem.h"
#include "input_request.h"
#include "problem_file_io.h"

std::vector<std::string> InputSubsystem::Tokenize(size_t argc, char *argv[]) {
    std::vector<std::string> strings(argc);
    for (size_t i = 0; i < argc; ++i) {
        strings[i] = std::string(argv[i]);
    }
    return strings;
}

std::unique_ptr<InputRequest> InputSubsystem::Parse(size_t argc, char *argv[]) {
    std::string program_name = std::string(argv[0]);
    --argc;
    argv = &argv[1];
    std::vector<std::string> tokens = InputSubsystem::Tokenize(argc, argv);
    if (tokens.empty()) {
        throw ParseException("There are no parameters, launch is impossible.");
    } else {
        if (tokens[0] == "newtask") {
            if (tokens.size() > 2) {
                throw ParseException("The '" + program_name +
                                     "' should be followed by the path to the file to be created "
                                     "or nothing to create a file with the default name. However, "
                                     "the number of parameters is not conducive to this.");
            } else if (tokens.size() == 2) {
                return std::make_unique<RequestCreateProblemFile>(tokens[1]);
            } else if (tokens.size() == 1) {
                return std::make_unique<RequestCreateProblemFile>(kProblemFileDefaultName);
            }
        } else if (tokens[0] == "solve") {
            if (tokens.size() > 2) {
                throw ParseException(
                    "The 'solve' should be followed by the path to the Problem File or nothing to "
                    "use a file with a default name. However, the number of parameters is not "
                    "conducive to this.");
            } else if (tokens.size() == 2) {
                return std::make_unique<RequestSolve>(ProblemFileIO::ParseProblemFile(tokens[1]));
            } else if (tokens.size() == 1) {
                return std::make_unique<RequestSolve>(
                    ProblemFileIO::ParseProblemFile(kProblemFileDefaultName));
            }
        } else if (tokens[0] == "-h" || tokens[0] == "--help") {
            if (tokens.size() != 1) {
                throw ParseException("There are too many parameters for the help command.");
            } else {
                return std::make_unique<RequestHelp>();
            }
        } else {
            throw ParseException("Invalid key.");
        }
    }
    return std::unique_ptr<InputRequest>(nullptr);
}
