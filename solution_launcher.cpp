#include "solution_launcher.h"
#include "manual_solver.h"
#include "matrix_solver.h"
#include "scalar_product_L2.h"
#include <cmath>

#include <iostream>

void SolutionLauncher(Task&& task) {
    if (task.GetProblem() == ProblemType::TWIN_EQUATION) {
        if (task.GetIterationMethod() == IterationType::MANUAL) {
            ManualSolver instance(task, "Solve Twin equation");
            instance.PerformCalculation();
        } else if (task.GetIterationMethod() == IterationType::MATRIX) {
            SimpleMatrixSolver instance(task, "Solve Twin equation");
            instance.PerformCalculation();
        }
    } else if (task.GetProblem() == ProblemType::ORIGINAL_EQUATION) {
        Real N_0;
        {
            task.N_ = 0;
            task.save_c_to_file_ = false;
            task.problem_ = ProblemType::TWIN_EQUATION;
            SimpleMatrixSolver solver_N0(task, "Solve Twin equation for N=0");
            std::vector<Real> c_0 = solver_N0.PerformCalculation();
            ScalarProductL2 calc_prod_N0(task, c_0);
            N_0 = calc_prod_N0.Calculate();
        }
        Real N_1;
        {
            task.N_ = 1;
            SimpleMatrixSolver solver_N1(task, "Solve Twin equation for N=1");
            std::vector<Real> c_1 = solver_N1.PerformCalculation();
            ScalarProductL2 calc_prod_N1(task, c_1);
            N_1 = calc_prod_N1.Calculate();
        }
        const Real eps = 1e-9;
        if (std::abs(N_1 - 1 - N_0) < eps) {
            throw std::logic_error("N_1-1-N_0 is equal to 0");
        }
        Real N = -N_0 / (N_1 - 1 - N_0);
        task.N_ = N;
        task.save_c_to_file_ = true;
        std::cout << "debug: " << task.PathToResultFile() << std::endl;
        SimpleMatrixSolver final_solver(task, "Solve Twin equation");
        final_solver.PerformCalculation();
    }
}
