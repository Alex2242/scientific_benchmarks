#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <math.h>

#ifndef RELEASE
#define PRINTF printf
#define ADDCSV
#else
#define PRINTF
#define ADDCSV printf
#endif

// Includes spécifique à la librairie MKL utilisée
#ifndef OPEN
#include <mkl.h>
#endif

#ifndef USE_MKL_MALLOC
	#define MALLOC(a) malloc(a)
	#define FREE(a) free(a)
#else
	#ifdef OPEN
		#define MALLOC(a) malloc(a) //aligned_alloc(a,64)
		#define FREE(a)   free(a)
	#else
		#define MALLOC(a) mkl_malloc(a,64)
		#define FREE(a) mkl_free(a)
	#endif
#endif

#include "utils.h"
#include "benchmarks.h"
#include "covmat_mkl.h"

//extern void covmat_mkl_complex_sp(MKL_Complex8 *signal_in, MKL_Complex8 *signal_out, int N, int M, int nbMat, char transN, char transC, MKL_Complex8 norm, MKL_Complex8 beta);



benchmark_results covmat_mkl_benchmark_sp(int n_runs) {
    /* declarations */
    float duration, min_time, max_time, total_time, gflop;
	struct timespec tpdeb;
	struct timespec tpfin;
	clockid_t clock_id = CLOCK_REALTIME;
    char transN, transC;
    MKL_Complex8 norm, mkl_zero, diff;
	float error, sum;
    
    /* Loop on matrix size */
    for(size_t matrix_size = 1000 ; matrix_size <= 1000 ; matrix_size += 1000) {		

		MKL_Complex8 *signal_in = (MKL_Complex8*) MALLOC(matrix_size * matrix_size * sizeof(MKL_Complex8));
		MKL_Complex8 *signal_out = (MKL_Complex8*) MALLOC(matrix_size * matrix_size * sizeof(MKL_Complex8));

		if (signal_in == NULL || signal_out == NULL) {
			fprintf(stderr, "[Error]: memory allocation failed, occured in %s:%d : %s\n", __FILE__, __LINE__, strerror(errno));
		}

		/* Timing tools  ********************************************************************************************/
		duration = 0.0f;
		min_time = 65536.0f;
		max_time = 0.0f;
		total_time  = 0.0f;
		gflop = (float) (1e-9 * matrix_size * matrix_size * 8.0f);

		/* gemm parameters */
		transN = 'N';
		transC = 'C';
		norm.real = 1.0f/(float) matrix_size;
		norm.imag = 0.0f;
		mkl_zero.real = 0.0f;
		mkl_zero.imag = 0.0f;

		// Warmup
		memset(signal_out, 0, matrix_size * matrix_size * sizeof(MKL_Complex8));
		covmat_mkl_complex_sp(signal_out, signal_in, matrix_size, matrix_size, 1, transN, transC, norm, mkl_zero);

		// compute and mesure performance
		for (int i = 0 ; i < n_runs ; i++) {
			clock_gettime(clock_id, &tpdeb);

			covmat_mkl_complex_sp(signal_out, signal_in,  matrix_size, matrix_size, 1, transN, transC, norm, mkl_zero);

			clock_gettime(clock_id, &tpfin);

			duration = (float) (tpfin.tv_sec - tpdeb.tv_sec) + (float) ((float) (tpfin.tv_nsec - tpdeb.tv_nsec) * 1e-9);

			total_time += duration;

			max_time = fmaxf(max_time, total_time);
			min_time = fminf(min_time, total_time);
		}

		FREE(signal_in);
		FREE(signal_out);
	}

	float avg_time = total_time / n_runs;
	float gflops = gflop / avg_time;

	benchmark_results bench_results = {
		"Covariance matrix estimation MKL SP",
		n_runs,
		total_time,
		min_time,
		avg_time,
		max_time,
		gflop,
		gflops
	};

	return bench_results;
}
