#include "gtest/gtest.h"

extern "C" {
#include "benchmarks.h"
#include "covmat_mkl.h"
}

TEST(CovMatrixMKL_SP, basic) {
    benchmark_results r = covmat_mkl_benchmark_sp(1);
}

TEST(CovMatrixMKL_SP, 10Runs) {
    benchmark_results r = covmat_mkl_benchmark_sp(10);
}