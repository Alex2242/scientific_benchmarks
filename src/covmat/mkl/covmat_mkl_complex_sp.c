#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <omp.h>
#include <mkl.h>


void covmat_mkl_complex_sp(
	MKL_Complex8 *signal_in, MKL_Complex8 *signal_out, int N, int M, int nbMat,
	char transN, char transC, MKL_Complex8 norm, MKL_Complex8 beta) {
	
    for(int i = 0 ; i < nbMat ; i++){
        cgemm(&transN, &transC, &N, &N, &M, &norm, signal_in, &N, signal_in, &N, &beta, signal_out, &N);
    }
}