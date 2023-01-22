#include "solution_launcher.h"
#include "manual_solver.h"
#include <cmath>

void SolutionLauncher(Task&& task) {
    if (task.GetProblem() == ProblemType::TWIN_EQUATION) {
        ManualSolver instance(std::move(task), "Solve Twin equation");
        instance.PerformCalculation();
    } else if (task.GetProblem() == ProblemType::ORIGINAL_EQUATION) {
        throw std::runtime_error("Not implemented yet");
//        std::unique_ptr<ResultsSaver> saver_c0 =
//            std::make_unique<NopResultsSaver>(task.grid_count(), task.r());
//        Task task_N0(task.b(), task.r(), task.s(), 0, task.grid_count(), task.iter_count(),
//                     task.CloneKernels(), std::move(saver_c0),
//                     task.GetIntegrationMethod(), ProblemType::TWIN_EQUATION);
//        ManualSolver solver_N0(std::move(task_N0), "Solve Twin equation for N=0");
//        std::vector<double> c_0 = solver_N0.PerformCalculation();
//        std::unique_ptr<ResultsSaver> saver_c1 =
//            std::make_unique<NopResultsSaver>(task.grid_count(), task.r());
//        Task task_N1(task.b(), task.r(), task.s(), 1, task.grid_count(), task.iter_count(),
//                     task.CloneKernels(), std::move(saver_c1),
//                     task.GetIntegrationMethod(), ProblemType::TWIN_EQUATION);
//        ManualSolver solver_N1(std::move(task_N1), "Solve Twin equation for N=1");
//        std::vector<double> c_1 = solver_N0.PerformCalculation();
//        const double eps = 1e-9;
//        if (abs(N_1 - 1 - N_0) < eps) {
//            throw std::logic_error("N_1-1-N_ is equal to 0");
//        }
//        double N = -N_0 / (N_1 - 1 - N_0);
//        Task final_task(task.b(), task.r(), task.s(), N, task.grid_count(), task.iter_count(),
//                     task.CloneKernels(), std::move(saver_c1),
//                     task.GetIntegrationMethod(), ProblemType::TWIN_EQUATION);
//        ManualSolver final_solver(std::move(task_N1), "Solve Twin equation for N=1");
//        final_solver.PerformCalculation();
    }
}
