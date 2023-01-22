#include "solution_launcher.h"
#include "manual_solver.h"

void SolutionLauncher(Task&& task) {
    ManualSolver instance(std::move(task), "Calculate the answer of the Twin equation");
}
