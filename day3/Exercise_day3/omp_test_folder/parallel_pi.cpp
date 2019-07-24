#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main()
{
    const int niter = 50000000;
    int count=0;
    double pi;
    double z;
    double *x = (double*)malloc(niter*sizeof(double));
    double *y = (double*)malloc(niter*sizeof(double));

    for(int i=0; i<niter; ++i)
    {
        x[i] = (double)random()/RAND_MAX;
        y[i] = (double)random()/RAND_MAX;
    }

   double time = -omp_get_wtime();

   
    #pragma omp parallel private(z)
{
    int temp_count = 0;
    #pragma omp for
    for (int i=0; i<niter; ++i){
        z = sqrt((x[i]*x[i])+(y[i]*y[i]));
        if (z<=1){
    
	   ++temp_count;
        }

    }

    #pragma omp critical
    {
	count = count + temp_count;
    }
}

    pi = ((double)count/(double)niter)*4.0;          //p = 4(m/n)

    time += omp_get_wtime();

    printf("Pi: %f\n", pi);
    printf("The solution took: %f\n seconds", time);


   return 0;
}
