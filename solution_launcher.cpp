#include "solution_launcher.h"
#include "manual_solver.h"

void SolutionLauncher(Task&& task) {
    if (task.GetProblem() == ProblemType::TWIN_EQUATION) {
        ManualSolver instance(std::move(task), "Calculate the answer of the Twin equation");
    } else if (task.GetProblem() == ProblemType::ORIGINAL_EQUATION) {
        throw std::runtime_error("Not implemented yet");
        Task task_N0 = task;
    }
}
