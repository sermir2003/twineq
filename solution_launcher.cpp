#include "solution_launcher.h"
#include "manual_solver.h"
#include "matrix_solver.h"

void SolutionLauncher(Task&& task) {
    if (task.SolverMethod() == "Manual") {
        ManualSolver instance(std::move(task));
    }
    else if (task.SolverMethod() == "Matrix") {
        SimpleMatrixSolver instance(std::move(task));
    }
}
