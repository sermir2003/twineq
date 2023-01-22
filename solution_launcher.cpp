#include "solution_launcher.h"
#include "manual_solver.h"

void SolutionLauncher(Task&& task) {
    if (task.GetProblem() == ProblemType::TWIN_EQUATION) {
        ManualSolver instance(std::move(task), "Calculate the answer of the Twin equation");
    }
}
