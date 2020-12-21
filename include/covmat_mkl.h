
#include "benchmarks.h"
#ifndef OPEN
#include <mkl.h>
#endif


#ifndef COVMAT_MKL_H
#define COVMAT_MKL_H


benchmark_results covmat_mkl_benchmark_sp(int nbRUN);
void covmat_mkl_complex_sp(MKL_Complex8 *signal_in, MKL_Complex8 *signal_out, int N, int M, int nbMat, char transN, char transC, MKL_Complex8 norm, MKL_Complex8 beta);

#endif