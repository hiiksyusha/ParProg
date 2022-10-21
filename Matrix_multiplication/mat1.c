#include "stdio.h"
#include "locale.h"
#include "time.h"
#include "stdlib.h"
#include "pthread.h"
#include "time.h"

 void func(n){
 	int **a;
 	int **b;
 	int **c;
	FILE* file;
	file = fopen("mat1.txt", "a");
    struct timespec start, finish;
    double elapsed;
	
 	a = (int**) malloc(n*sizeof(int*));
 	for (int i = 0; i < n; i++)
 		a[i] = (int*) malloc(n*sizeof(int));
	
 	b = (int**) malloc(n*sizeof(int*));
 	for (int i = 0; i < n; i++)
 		b[i] = (int*) malloc(n*sizeof(int));
	
 	c = (int**) malloc(n*sizeof(int*));
 	for (int i = 0; i < n; i++)
 		c[i] = (int*) malloc(n*sizeof(int));
	
 	for (int i = 0; i < n; i++) {
 		for (int j = 0; j < n; j++) {
 			a[i][j] = -1000 + rand() % (1000 + 1000 + 1);
 			b[i][j] = -1000 + rand() % (1000 + 1000 + 1);
 			c[i][j] = 0;
 		}
 	}
	clock_gettime(CLOCK_MONOTONIC, &start);		
 	for (int i = 0; i < n; ++i) {
 		for (int j = 0; j < n; ++j) {
 			for (int k = 0; k < n; ++k) {
 				c[i][j] += a[i][k] * b[k][j];
 			}
 		}
 	}
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
 	//int i = 0, j = 0;
 	//for (int i = 0; i < n; i++) {
 	//	for (int j = 0; j < n; j++) {
 	//		printf( "%d ", c[i][j]);
 	//	}
 	//	putchar( '\n' );
 	//}
	fprintf(file,"%d %f\n", n, elapsed);
	fclose(file);
	
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
	
	for (int i = 2; i < 35; i++){
		func(i*32);
	}
}
