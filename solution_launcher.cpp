#include "solution_launcher.h"
#include "manual_solver.h"

void SolutionLauncher(Task&& task) {
    ManualSolver(std::move(task));
}
