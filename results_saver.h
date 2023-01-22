#pragma once
#include <vector>
#include <string>

enum class ResultsSaverType {
    FILE,
    NOP,
};

class ResultsSaver {
protected:
    double grid_count_;
    double r_;
    double step_size_;
public:
    ResultsSaver(double grid_count, double r) : grid_count_(grid_count), r_(r) {
        step_size_ = 2 * r_ / (grid_count_ - 1);
    }
    virtual void Save(const std::vector<double>& c) const = 0;
    virtual ~ResultsSaver() {
    }
};

class FileResultsSaver : public ResultsSaver {
protected:
    std::string path_to_result_file_;
public:
    FileResultsSaver(double grid_count, double r, const std::string& path_to_result_file);
    void Save(const std::vector<double>& c) const override;
};

class NopResultsSaver : public ResultsSaver {
public:
    NopResultsSaver(double grid_count, double r);
    void Save(const std::vector<double>& c) const override;
};
