#ifndef BENCHMARKS_H
#define BENCHMARKS_H

/**
 * @brief Struct containing the results of a benchmark
 * 
 * @var nflop Number of floating point operations performed by the benchmark 
 */
typedef struct benchmark_results {
    char name[64];
    int n_runs;
    float total_time;
    float min_time;
    float avg_time;
    float max_time;
    int gflop;
    float gflops;
} benchmark_results;

#endif