cmake_minimum_required(VERSION 3.16.3) # 3.24
project(twineq)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -O3 -ggdb")

include(FetchContent)

set(DOWNLOAD_EXTRACT_TIMESTAMP "true")
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(twineq main.cpp input_request.h task.cpp task.h kernels.cpp kernels.h manual_solver.cpp manual_solver.h integrators.cpp integrators.h integrators.h progress_counter.cpp progress_counter.h solution_launcher.cpp solution_launcher.h service_parameters_types.h scalar_product_L2.cpp scalar_product_L2.h matrix_solver.cpp matrix_solver.h real_number.h task_file_parse_exception.h cmd_args_parser.cpp cmd_args_parser.h task_file_parse_exception.cpp)

target_link_libraries(twineq PRIVATE nlohmann_json::nlohmann_json)
