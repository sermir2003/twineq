#include "results_saver.h"
#include <fstream>
#include <iomanip>

FileResultsSaver::FileResultsSaver(double grid_count, double r,
                                   const std::string& path_to_result_file) : ResultsSaver(grid_count, r), path_to_result_file_(path_to_result_file) {
}
void FileResultsSaver::Save(const std::vector<double>& c) const {
    std::ofstream file(path_to_result_file_, std::ios::out);
    double x = -r_;
    for (size_t i = 0; i < grid_count_; ++i) {
        file << std::fixed << std::setprecision(9) << x << " " << c[i] << std::endl;
        x += step_size_;
    }
}
NopResultsSaver::NopResultsSaver(double grid_count, double r)
    : ResultsSaver(grid_count, r) {
}
void NopResultsSaver::Save(const std::vector<double>& c) const {
}
