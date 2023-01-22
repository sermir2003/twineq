#include "solution_launcher.h"
#include "manual_solver.h"
#include "scalar_product_L2.h"
#include <cmath>

#include <iostream>

void SolutionLauncher(Task&& task) {
    if (task.GetProblem() == ProblemType::TWIN_EQUATION) {
        ManualSolver instance(task, "Solve Twin equation");
        instance.PerformCalculation();
    } else if (task.GetProblem() == ProblemType::ORIGINAL_EQUATION) {
        Task task_N0(task.b(), task.r(), task.s(), 0, task.grid_count(), task.iter_count(),
                     task.CloneKernels(), false, "",
                     task.GetIntegrationMethod(), ProblemType::TWIN_EQUATION);
        ManualSolver solver_N0(task_N0, "Solve Twin equation for N=0");
        std::vector<double> c_0 = solver_N0.PerformCalculation();
        ScalarProductL2 calc_prod_N0(task_N0, c_0);
        double N_0 = calc_prod_N0.Calculate();

        Task task_N1(task.b(), task.r(), task.s(), 1, task.grid_count(), task.iter_count(),
                     task.CloneKernels(), false, "",
                     task.GetIntegrationMethod(), ProblemType::TWIN_EQUATION);
        ManualSolver solver_N1(task_N1, "Solve Twin equation for N=1");
        std::vector<double> c_1 = solver_N1.PerformCalculation();
        ScalarProductL2 calc_prod_N1(task_N1, c_1);
        double N_1 = calc_prod_N1.Calculate();

        const double eps = 1e-9;
        if (abs(N_1 - 1 - N_0) < eps) {
            throw std::logic_error("N_1-1-N_ is equal to 0");
        }
        double N = -N_0 / (N_1 - 1 - N_0);
        std::cout << "debug: " << task.PathToResultFile() << std::endl;
        Task final_task(task.b(), task.s(), task.r(), N, task.grid_count(), task.iter_count(),
                     task.CloneKernels(), true, task.PathToResultFile(),
                     task.GetIntegrationMethod(), ProblemType::TWIN_EQUATION);
        ManualSolver final_solver(final_task, "Solve Twin equation");
        final_solver.PerformCalculation();
    }
}
