#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Markers used to bound trace regions of interest */
volatile char MARKER_START, MARKER_END;

int main(int argc, char* argv[])
{

    /* Record marker addresses */
    FILE* marker_fp = fopen(".marker","w");
    assert(marker_fp);
    fprintf(marker_fp, "%llx\n%llx",
        (unsigned long long int) &MARKER_START,
        (unsigned long long int) &MARKER_END );
    fclose(marker_fp);

    if (argc!=3) {
        printf("Usage: ./cacheBlocking <matrix_a_file> <matrix_b_file>\n");
        exit(EXIT_FAILURE);
    }

    FILE* matrix_a_fp = fopen(argv[1], "r");
    if (!matrix_a_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    size_t n;
    int ret = fscanf(matrix_a_fp, "%ld\n", &n);
    assert (ret==1);
    int* a = calloc( n*n, sizeof(int) );
    for ( size_t i=0; i<n; i++ ) {
        for ( size_t k=0; k<n; k++ ) {
            ret = fscanf(matrix_a_fp, "%d ", &a[i*n+k]);
            assert (ret==1);
        }
        ret = fscanf(matrix_a_fp, "\n");
    }
    fclose(matrix_a_fp);

    FILE* matrix_b_fp = fopen(argv[2], "r");
    if (!matrix_b_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    size_t m;
    ret = fscanf(matrix_b_fp, "%ld\n", &m);
    assert (ret==1);
    assert( n==m );
    int* b = calloc( n*n, sizeof(int) );
    for ( size_t k=0; k<n; k++ ) {
        for ( size_t j=0; j<n; j++ ) {
            ret = fscanf(matrix_b_fp, "%d ", &b[k*n+j]);
            assert (ret==1);
        }
        ret = fscanf(matrix_b_fp, "\n");
    }
    fclose(matrix_b_fp);

    int* c = calloc( n*n, sizeof(int) );
    MARKER_START = 211;

    int i, j ,k;
    int i1, j1, k1;
    
    int B = 2;
    
    for(k=0; k < n; k+=B){
        for(i=0; i < n; i+=B){
            for(j=0; j < n; j+=B){
                for(i1=i; i1 < i+B; i1++){
                    for(j1=j; j1 < j+B; j1++){
                        for(k1=k; k1 < k+B; k1++){
                            c[i1*n+j1] += a[i1*n+k1] * b[k1*n+j1];
                        }
                    }
                }
            }
        }
    }
    MARKER_END = 211;
    
    for ( size_t i=0; i<n; i++ ) {
        for ( size_t j=0; j<n; j++ ) {
            printf( "%d ", c[i*n+j] );
        }
        printf( "\n" );
    }

    free(c);
    free(b);
    free(a);
    exit(EXIT_SUCCESS);

}
