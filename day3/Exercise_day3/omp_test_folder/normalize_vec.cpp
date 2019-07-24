#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// function to compute the 2-norm of a vector v of length n
double norm(double *v, int n){
    double norm = 0.;

    for(int i=0; i<n; i++)
        norm += v[i]*v[i];

    return sqrt(norm);
}

// initialise v to values between -10 and 10
void initialize(double *v, int n){
    for(int i=0; i<n; i++)
        v[i] = cos(double(i)) * 10.;
}

// This is the non-parallel version
void normalize_vector(double *v, int n){
    double norm = 0.;

    // compute the norm of v
    for(int i=0; i<n; i++)
        norm += v[i]*v[i];
    norm = sqrt(norm);

    // normalize v
    for(int i=0; i<n; i++)
        v[i] /= norm;
}

void normalize_vector_omp(double *v, int n)
{

    double norm = 0.;
    double temp_norm = 0.; 
    int th_id;
    #pragma omp parallel private(temp_norm)
    {
	th_id = omp_get_thread_num();

    	#pragma omp for
    	for(int i=0; i<n; i++){
          temp_norm += v[i]*v[i];
	}

	#pragma omp critical
	{
	norm = norm + temp_norm;
   	} 
    }

    norm = sqrt(norm);

    #pragma omp parallel
    {
	#pragma omp for
	for (int i=0;i<n;i++){
		v[i]/=norm;
	}

    } 
}

int main( void ){

//for(int i=0;i<4;i++){

    const int N = 200000000;
    double *v = (double*)malloc(N*sizeof(double));
    bool validated = false;
    
    //Output N
    std::cout<<"N : "<< N << std::endl;

    initialize(v, N);
    // Calling the first omp function
    double time_serial = -omp_get_wtime();
    normalize_vector(v, N);
    time_serial += omp_get_wtime();

    // chck the answer
    std::cout << "serial error   : " << fabs(norm(v,N) - 1.) << std::endl;

    int max_threads = omp_get_max_threads();
    initialize(v, N);
    double time_parallel = -omp_get_wtime();
    normalize_vector_omp(v, N);
    time_parallel += omp_get_wtime();

    // chck the answer
    std::cout << "parallel error : " << fabs(norm(v,N) - 1.) << std::endl;

    std::cout << max_threads     << " threads" << std::endl;
    std::cout << "serial     : " << time_serial << " seconds\t"
              << "parallel   : " << time_parallel <<  " seconds" << std::endl;
    std::cout << "speedup    : " << time_serial/time_parallel << std::endl;
    std::cout << "efficiency : " << (time_serial/time_parallel)/double(max_threads) << std::endl;

    free(v);

//}
    return 0;
}


