#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */
#include <stdio.h>
#include <stdlib.h>

#include "covmat_mkl.h"

//masquer les PRINTF en mode release
//addcsv donne une sortie formatee pour les csv
#ifndef RELEASE
#define PRINTF printf
#define ADDCSV
#else
#define PRINTF
#define ADDCSV printf
#endif

#ifdef CL
extern void benchCovMatEstimation_OPENCL_sp();
#endif

#ifdef CUDA
extern void benchCovMatEstimation_CUDA_dp();
extern void benchCovMatEstimation_CUDA_sp();
#endif

int main(int argc, char **argv) {

    int nbRUN = 5;

	//PRINTF("\n\n");
	//PRINTF("====================\t CovMatEstimation (x%d)\t ====================\n\n", nb_fois);

	//PRINTF("Starting MKL Double Precision...\n\n");
	//ADDCSV("CovMatEstimation;MKL_DP;FO;%d;",type_fo);
	//AutoBenchEstimation_MKL_dp();
	//PRINTF("\n\n");

	PRINTF("Starting benchmarks...\n\n");
	//ADDCSV("CovMatEstimation;MKL_SP;FO;%d;",type_fo);

	benchmark_results r = covmat_mkl_benchmark_sp(nbRUN);

	printf("*************\t%s Simple Precision\t*************\n", r.name);
	printf("Average elapsed time\t= %lf ms\n", r.avg_time * 1000);
	printf("Min time \t= %lf ms\n", r.min_time*1000);
	printf("Max time \t= %lf ms\n", r.max_time*1000);
	printf("Nb operation\t= %g Gflop\n", r.gflop);
	printf("Performance\t= %g Gflop/s\n", r.gflops);
	printf("\n\n");

#ifdef CUDA
	PRINTF("Starting CUDA Double Precision...\n\n");
	ADDCSV("CovMatEstimation;CUDA_DP;FO;%d;",type_fo);
	benchCovMatEstimation_CUDA_dp();
	PRINTF("\n\n");

	PRINTF("Starting CUDA Simple Precision...\n\n");
	ADDCSV("CovMatEstimation;CUDA_SP;FO;%d;",type_fo);
	benchCovMatEstimation_CUDA_sp();
	PRINTF("\n\n");

#endif

#ifdef CL
	PRINTF("Starting OPENCL Simple Precision...\n\n");
	ADDCSV("CovMatEstimation;CL_SP;FO;%d;",type_fo);
	benchCovMatEstimation_OPENCL_sp();
#endif
	return EXIT_SUCCESS;
}

