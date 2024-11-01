#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_RANGE 10
#define UNIT_RANGE 20
#define RANDOM_INPUT 0

void detection(int **allocate, int **request, int *r_unit, int *finish, int n, int m);
void find_deadlock(int *finish, int n);
void matrix_print(int **matrix, int n, int m);
int *create_finish(int n);
int *R_info(FILE *infile, int *n, int *m);
void get_input(FILE *infile, int n, int m, int **request, int **allocate);
int **create_matrix(int row, int column);
void free_matrix(int row, int column, int **matrix);
void get_R_remain(int *r_unit, int **allocate, int n, int m);
FILE *rand_input(void);

int main(){
    srand(time(NULL));
    int n, m;
    FILE *infile;

    if(RANDOM_INPUT == 0){
        printf("--Not random input (default: input1.txt)--\n\n");
        infile = fopen("input1.txt", "r");
    }else{
        printf("--Random input file--\n\n");
        infile = rand_input();
    }

    if(infile == NULL){
        printf("file opening failed\n");
        exit(-2);
    }

    int *r_unit = R_info(infile, &n, &m);
    int *finish = create_finish(n);

    int **request = create_matrix(n, m);
    int **allocate = create_matrix(n, m);

    get_input(infile, n, m, request, allocate);

    printf("request\n");
    matrix_print(request, n, m);

    printf("allocate\n");
    matrix_print(allocate, n, m);
    get_R_remain(r_unit, allocate, n, m);
    detection(allocate, request, r_unit, finish, n, m);

    printf("result: final allocation\n");
    matrix_print(allocate, n, m);

    printf("result: remain request\n");
    matrix_print(request, n, m);
    find_deadlock(finish, n);

    free_matrix(n, m, request);
    free_matrix(n, m, allocate);
    free(finish);
    free(r_unit);

    fclose(infile);

    return 0;
}

void detection(int **allocate, int **request, int *r_unit, int *finish, int n, int m){
    int impossible = 0;
    int change = 0;
    while(1){
        change = 0;
        for(int i = 0; i < n; i++){
            if(finish[i] != 1){
                for(int j = 0; j < m; j++){
                    if(r_unit[j] < request[i][j]){
                        impossible = 1;
                    }
                }
                if(impossible == 0){
                    finish[i] = 1;
                    for(int j = 0; j < m; j++){
                        r_unit[j] += allocate[i][j];
                        request[i][j] = 0;
                        allocate[i][j] = 0;
                    }
                    change = 1;
                }
            }
            impossible = 0;
            if(change == 1){
                break;
            }
        }
        if(change == 0){
            break;
        }
    }
}

FILE *rand_input(void){
    FILE *infile = fopen("input.txt", "w+");
    if(infile == NULL){
        printf("file opening failed\n");
        exit(-2);
    }

    int n = rand() % (RAND_RANGE + 1);
    int m = rand() % (RAND_RANGE + 1);
    int unit[m];
    int remain[m];
    int **allocate = create_matrix(n, m);
    fprintf(infile, "%d, %d, ", n, m);

    for(int i = 0; i < m; i++){
        if(i == m - 1){
            unit[i] = rand() % (UNIT_RANGE + 1);
            remain[i] = unit[i];
            fprintf(infile, "%d\n", unit[i]);
        }else{
            unit[i] = rand() % (UNIT_RANGE + 1);
            remain[i] = unit[i];
            fprintf(infile, "%d, ", unit[i]);
        }
    }

    int r;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            r = rand() % (remain[j] + 1);
            allocate[i][j] = r;
            if(j == m - 1){
                fprintf(infile,"%d\n", r);
            }else{
                fprintf(infile,"%d, ", r);
            }
            remain[j] -= r;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(j == m - 1){
                fprintf(infile,"%d\n", rand() % (unit[j] - allocate[i][j]+ 1));
            }else{
                fprintf(infile,"%d, ", rand() % (unit[j] - allocate[i][j] + 1));
            }
        }
    }

    free_matrix(n, m, allocate);
    fseek(infile, 0, SEEK_SET);

    return infile;
}

void find_deadlock(int *finish, int n){
    int num_deadlock = 0;
    printf("Deadlocked process: \n");
    for(int i = 0; i < n; i++){
        if(finish[i] != 1){
            num_deadlock++;
            printf("P%d ", i);
        }
    }

    if(num_deadlock == 0){
        printf("none\n");
        printf("Not in Deadlock state\n");
    }else{
        printf("\n");
        printf("The system is in Deadlock state\n");
    }
}

void get_R_remain(int *r_unit, int **allocate, int n, int m){
    printf("Available resource \n");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            r_unit[i] -= allocate[j][i];
        }
        if(r_unit[i] < 0){
            printf("cannot allocate more than total unit number\n");
            exit(-4);
        }
        printf("%d ", r_unit[i]);
    }
    printf("\n\n");
}

void matrix_print(int **matrix, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int *create_finish(int n){
    int *finish = (int *)malloc(sizeof(int) * n);
    if(finish == NULL){
        printf("dynamic memory allocation failed\n");
        exit(-1);
    }
    for(int i = 0; i < n; i++){
        finish[i] = 0;
    }
    return finish;
}

int *R_info(FILE *infile, int *n, int *m){
    fscanf(infile, "%d, %d, ", n, m);
    printf("# of P: %d # of R: %d\n", *n, *m);

    int *resource = (int *)malloc(sizeof(int) * (*m));
    if(resource == NULL){
        printf("dynamic memory allocation failed\n");
        exit(-1);
    }

    int num = 0;
    printf("number of resource unit\n");
    for(int i = 0; i < *m; i++){
        if(i == *m - 1){
            num += fscanf(infile, "%d\n", (&resource[i]));
        }else{
            num += fscanf(infile, "%d, ", (&resource[i]));
        }
        printf("%d ", resource[i]);
    }
    printf("\n");

    if(num != *m){
        printf("reading the number of resource unit failed\n");
        exit(-3);
    }

    return resource;
}

void get_input(FILE *infile, int n, int m, int **request, int **allocate){
    int read = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(j == m - 1){
                read += fscanf(infile, "%d\n", &(allocate[i][j]));
            }else{
                read += fscanf(infile, "%d, ", &(allocate[i][j]));
            }
        }
        if(read != m){
            printf("reading allocation data failed\n");
            exit(-3);
        }
        read = 0;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(j == m - 1){
                read += fscanf(infile, "%d\n", &(request[i][j]));
            }else{
                read += fscanf(infile, "%d, ", &(request[i][j]));
            }
        }
        if(read != m){
            printf("reading request data failed\n");
            exit(-3);
        }
        read = 0;
    }
}

int **create_matrix(int row, int column){
    int **matrix = (int **)malloc(sizeof(int *)* row);
    if(matrix == NULL){
        printf("dynamic memory allocation failed\n");
        exit(-1);
    }

    for(int i = 0; i < row; i++){
        matrix[i] = (int *)malloc(sizeof(int) * column);
        if(matrix[i] == NULL){
            printf("dynamic memory allocation failed\n");
            exit(-1);
        }
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

void free_matrix(int row, int column, int **matrix){
    for(int i = 0; i < row; i++){
        free(matrix[i]);
    }
    free(matrix);
}
