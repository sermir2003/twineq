#include "cmd_args_parser.h"
#include <iostream>
#include "task_file_parse_exception.h"

std::vector<std::string> CMDArgsParser::Tokenize(size_t argc, char* argv[]) {
    std::vector<std::string> strings(argc);
    for (size_t i = 0; i < argc; ++i) {
        strings[i] = std::string(argv[i]);
    }
    return strings;
}

std::unique_ptr<InputRequest> CMDArgsParser::Parse(size_t argc, char* argv[]) {
    std::string program_name = std::string(argv[0]);
    --argc;
    argv = &argv[1];
    std::vector<std::string> tokens = CMDArgsParser::Tokenize(argc, argv);
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
                return std::make_unique<RequestCreateTaskFile>(tokens[1]);
            } else if (tokens.size() == 1) {
                return std::make_unique<RequestCreateTaskFile>("");
            }
        } else if (tokens[0] == "solve") {
            if (tokens.size() > 2) {
                throw ParseException(
                    "The 'solve' should be followed by the path to the Task File or nothing to "
                    "use a file with a default name. However, the number of parameters is not "
                    "conducive to this.");
            } else if (tokens.size() == 2) {
                try {
                    return std::make_unique<RequestSolve>(tokens[1]);
                } catch (const TaskFileParseException& exception) {
                    std::cout << "ERROR: incorrect task file\n" << exception.what() << std::endl;
                    exit(0);
                }
            } else if (tokens.size() == 1) {
                try {
                    return std::make_unique<RequestSolve>("");
                } catch (const TaskFileParseException& exception) {
                    std::cout << "ERROR: incorrect task file\n" << exception.what() << std::endl;
                    exit(0);
                }
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
