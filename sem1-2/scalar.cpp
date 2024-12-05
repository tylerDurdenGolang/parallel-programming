// #include <windows.h>
#include <stdio.h>
#include <time.h>

#define N 110000000

double a[N + 1], b[N + 1];
   
int i;   
double gDotProduct = 0;

int main()
{
	// initialize vectors   
	for (i = 0; i < N; i++) 
	{
		a[i] = 1.034;
		b[i] = 1.057;
	}

	auto start = clock();
	// код, который нужно распараллелить
	for ( i = 0; i < N; i++ ) 
	{
		gDotProduct += a[i] * b[i];
	}
	// ---------
	auto stop = clock();
	
	printf("Computed value of vector sum: ");
	//print dot product  
	printf("sum = %f\n", gDotProduct);   
	//print delta time
	printf("time = %g\n", (double)(stop - start)/CLOCKS_PER_SEC); 
}

