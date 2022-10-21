#include "stdio.h"
#include "locale.h"
#include "time.h"
#include "stdlib.h"
#include "pthread.h"

void func(n){
	int **a;
	int **b;
	int **c;
	
	a = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		a[i] = (int*) malloc(n * sizeof(int));
	
	b = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		b[i] = (int*) malloc(n * sizeof(int));
	
	c = (int**) malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		c[i] = (int*) malloc(n * sizeof(int));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = -1000 + rand() % (1000 + 1000 + 1);
			b[i][j] = -1000 + rand() % (1000 + 1000 + 1);
			c[i][j] = 0;
		}
	}
			
    int ii=0;
    int jj=0;
    int kk=0;
    int i=0;
    int j=0;
    int k=0;
    int blok=32;
	
	FILE* file;
	file = fopen("mat2.txt", "a");
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);

	for (ii = 0; ii < n; ii += blok)
		for (jj = 0; jj < n; jj += blok)
			for (kk = 0; kk < n; kk += blok)
				for (i = ii; i < ii + blok; i++)
					for (j = jj; j < jj + blok; j++)
						for (k = kk; k < kk + blok; k++)
								c[i][j] += a[i][k] * b[k][j];
	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	fprintf(file,"%d %f\n", n, elapsed);
	fclose(file);

	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		printf( "%d ", c[i][j]);
	//	}
	//	putchar( '\n' );
	//}
	
	for (int i = 0; i < n; i++) {
			free(a[i]);
			free(b[i]);
			free(c[i]);
		}
 	free(a);
 	free(b);
 	free(c);
	
}

int main (int argc, char* argv[]){
	
		for (int i = 2; i < 35; i++) {
			func(i*32);
		}
	}
