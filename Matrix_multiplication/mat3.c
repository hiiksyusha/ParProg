#include "stdio.h"
#include "locale.h"
#include "time.h"
#include "stdlib.h"
#include "pthread.h"

int **a;
int **b;
int **c;
int num_threads = 16, n = 1920;

void * worker(void *arg) {
  int i, j, k, tid, portion_size, row_start, row_end;
  int sum;
  
  tid = *(int *)(arg);
  portion_size = n / num_threads;
  row_start = tid * portion_size;
  row_end = (tid+1) * portion_size;

  for (i = row_start; i < row_end; i++) { 
    for (j = 0; j < n; j++) { 
      	sum = 0;
      	for (k = 0; k < n; k++) { 
		  sum += a[i][k]*b[k][j];
	  }
      c[i][j] = sum;
    }
  }
}


int main (int argc, char* argv[]){
	
	FILE *file;
	struct timespec start, finish;
	double elapsed;
	file = fopen("mat3.txt", "a");
	int i=0,j=0;
	int sum = 0;
	pthread_t * threads;
	int size = 10;
	
	
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
	
	threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	for ( i = 0; i < num_threads; i++ ) {
	    int *tid;
	    tid = (int *) malloc( sizeof(int) );
	    *tid = i;
	    pthread_create( &threads[i], NULL, worker, (void *)tid );
	  }
	  
	  for ( i = 0; i < num_threads; i++ ) {
	    pthread_join( threads[i], NULL );
	  }
	  clock_gettime(CLOCK_MONOTONIC, &finish);
	  elapsed = (finish.tv_sec - start.tv_sec);
	  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	  fprintf(file,"%d %f\n", num_threads, elapsed);
	  fclose(file);
	  
	  for (int i = 0; i < n; i++) {
	    			free(a[i]);
	    			free(b[i]);
	    			free(c[i]);
	    		}
	  free(a);
	  free(b);
	  free(c);
	  
	
		//for (int i = 0; i < n; i++) {
		//for (int j = 0; j < n; j++) {
		//	printf( "%d, ", c[i][j]);
		//}
		//printf( "%d", c[i][j]);
		//putchar( '\n' );
	//}
    return 0;
}
