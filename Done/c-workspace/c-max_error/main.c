/* A simplified learned index implementation:
 *
 * Skeleton code written by Jianzhong Qi, April 2023
 * Edited by: [Add your name and student ID here for automatic recognition]
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STAGE_NUM_ONE 1                          /* stage numbers */
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_HEADER "Stage %d\n==========\n" /* stage header format string */

#define DATASET_SIZE 100                      /* number of input integers */
#define DATA_OUTPUT_SIZE 10                      /* output size for stage 1 */

#define BS_NOT_FOUND (-1)                      /* used by binary search */
#define BS_FOUND 0

typedef int data_t;                             /* data type */

/****************************************************************/

/* function prototypes */
void print_stage_header(int stage_num);
int cmp(data_t *x1, data_t *x2);
void swap_data(data_t *x1, data_t *x2);
void partition(data_t dataset[], int n, data_t *pivot,
               int *first_eq, int *first_gt);
void quick_sort(data_t dataset[], int n);
int binary_search(data_t dataset[], int lo, int hi,
                  data_t *key, int *locn);

void stage_one(data_t dataset[]);
void stage_two(data_t dataset[]);
void stage_three(data_t dataset[], int *max_err, data_t maximum[], int *max_len);
void stage_four(data_t dataset[], int *max_err, data_t maximum[], int *max_len);

/* add your own function prototypes here */
double mapping(data_t dataset[], int key, int idx_a, int idx_b, int index);
int binary_search_step2(data_t dataset[], int lo, int hi,
    data_t *key, int *locn);
int binary_search_step3(data_t dataset[], int lo, int hi,
    data_t *key, int *locn);
/****************************************************************/

/* main function controls all the action */
int
main(int argc, char *argv[]) {
    /* to hold all input data */
    data_t dataset[DATASET_SIZE];
    int max_err;

    /* to hold the mapping functions */
    int max_len = 0;
    data_t maximum[DATASET_SIZE];

    /* stage 1: read and sort the input */
    stage_one(dataset);

    /* stage 2: compute the first mapping function */
    stage_two(dataset);

    /* stage 3: compute more mapping functions */
    stage_three(dataset, &max_err, maximum, &max_len);

    /* stage 4: perform exact-match queries */
    stage_four(dataset, &max_err, maximum, &max_len);

    /* all done; take some rest */
    return 0;
}

/****************************************************************/

/* add your code below; you can also modify the function return type
 and parameter list
 */

/* stage 1: read and sort the input */
void
stage_one(data_t dataset[]) {
    /* add code for stage 1 */
    /* print stage header */
    print_stage_header(STAGE_NUM_ONE);

    for (int i = 0; i < DATASET_SIZE; i++)
        scanf(" %d ", &dataset[i]);

    quick_sort(dataset, DATASET_SIZE);

    printf("First 10 numbers:");

    for (int i = 0; i < 10; i++)
        printf(" %d", dataset[i]);
    printf("\n\n");
}

/* stage 2: compute the first mapping function */
void
stage_two(data_t dataset[]) {
    /* add code for stage 2 */
    /* print stage header */
    print_stage_header(STAGE_NUM_TWO);

    int index = 0, error = 0;
    int max = -1, key = -1, pos = -1;

    for (int i = 2; i < DATASET_SIZE; i++) {
        binary_search(dataset, 0, DATASET_SIZE, &dataset[i], &index);
        error = fabs(ceil(mapping(dataset, dataset[i], 0, 1, index)) - index);
        if (error > max) {
            max = error;
            key = dataset[i];
            pos = i;
        }
    }

    printf("Maximum prediction error: %d\n", max);
    printf("For key: %d\n", key);
    printf("At position: %d\n", pos);
    printf("\n");
}

/* stage 3: compute more mapping functions */
void
stage_three(data_t dataset[], int *max_err, data_t maximum[], int *max_len) {
    /* add code for stage 3 */
    /* print stage header */
    print_stage_header(STAGE_NUM_THREE);

    printf("Target maximum prediction error: ");
    scanf("%d", max_err);

    int index = 0, error = 0;

    int idx_a = 0, idx_b = 1, idx_f = 0;
    for (int i = 2; i < DATASET_SIZE; i++) {
        binary_search(dataset, 0, DATASET_SIZE, &dataset[i], &index);
        error = fabs(ceil(mapping(dataset, dataset[i], idx_a, idx_b, index)) - index);

        if (error > *max_err) {
            printf("Function %2d: a = %4d, b = %4d, max element = %3d\n", idx_f, idx_a * dataset[idx_b] - idx_b * dataset[idx_a], dataset[idx_b] - dataset[idx_a], dataset[i-1]);
            idx_a = i;
            idx_b = i+1;
            idx_f++;
            maximum[*max_len] = dataset[i-1];
            *max_len = *max_len + 1;
        }
    }
    printf("\n");
}

/* stage 4: perform exact-match queries */
void stage_four(data_t dataset[], int *max_err, data_t maximum[], int *max_len) {
    /* add code for stage 4 */
    /* print stage header */
    print_stage_header(STAGE_NUM_FOUR);

    while (1) {
        int key = 0, location = 0;
        scanf(" %d", &key);

        printf("Searching for %d:\n", key);
        if (key < dataset[0] || key > dataset[DATASET_SIZE -1])
            printf("Step 1: not found!\n");
        else {
            printf("Step 1: search key in data domain.\n");

            printf("Step 2:");
            binary_search_step2(maximum, 0, *max_len, &key, &location);
            printf("\n");

            printf("Step 3:");
            int max = 0 > (ceil(mapping(dataset, key, 0, 1, 0)) - *max_err) ? 0 : (ceil(mapping(dataset, key, 0, 1, 0)) - *max_err);
            int min = DATASET_SIZE - 1 < fabs(ceil(mapping(dataset, key, 0, 1, 0)) + *max_err) ? DATASET_SIZE - 1 : fabs(ceil(mapping(dataset, key, 0, 1, 0)) + *max_err);
            binary_search_step3(dataset, max, min+1, &key, &location);
            if (dataset[location] == key)
                printf(" @ dataset[%d]\n", location);
            else
                printf(" not found!\n");
        }
        printf("\n");
    }
}

/****************************************************************/
/* functions provided, adapt them as appropriate */
double mapping(data_t dataset[], int key, int idx_a, int idx_b, int index) {
    if (dataset[idx_b] != dataset[idx_a])
        return ((idx_b - idx_a) * key + dataset[idx_b] * idx_a - dataset[idx_a] * idx_b) / (double)(dataset[idx_b] - dataset[idx_a]);
    else if (DATASET_SIZE - 1 == index)
        return key + DATASET_SIZE - 1;
    else
        return key + idx_a;
}

/* print stage header given stage number */
void
print_stage_header(int stage_num) {
    printf(STAGE_HEADER, stage_num);
}

/* data swap function used by quick sort, adpated from
 https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/sortscaffold.c
 */
void
swap_data(data_t *x1, data_t *x2) {
    data_t t;
    t = *x1;
    *x1 = *x2;
    *x2 = t;
}

/* partition function used by quick sort, from
 https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/quicksort.c
 */
void
partition(data_t dataset[], int n, data_t *pivot,
          int *first_eq, int *first_gt) {
    int next=0, fe=0, fg=n, outcome;

    while (next<fg) {
        if ((outcome = cmp(dataset+next, pivot)) < 0) {
            swap_data(dataset+fe, dataset+next);
            fe += 1;
            next += 1;
        } else if (outcome > 0) {
            fg -= 1;
            swap_data(dataset+next, dataset+fg);
        } else {
            next += 1;
        }
    }

    *first_eq = fe;
    *first_gt = fg;
    return;
}

/* quick sort function, adapted from
 https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/quicksort.c
 */
void
quick_sort(data_t dataset[], int n) {
    data_t pivot;
    int first_eq, first_gt;
    if (n<=1) {
        return;
    }
    /* array section is non-trivial */
    pivot = dataset[n/2]; // take the middle element as the pivot
    partition(dataset, n, &pivot, &first_eq, &first_gt);
    quick_sort(dataset, first_eq);
    quick_sort(dataset + first_gt, n - first_gt);
}

/* comparison function used by binary search and quick sort, from
 https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/binarysearch.c
 */
int
cmp(data_t *x1, data_t *x2) {
    return (*x1-*x2);
}

/* binary search between dataset[lo] and dataset[hi-1], adapted from
 https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/binarysearch.c
 */
int
binary_search(data_t dataset[], int lo, int hi,
              data_t *key, int *locn) {
    int mid, outcome;
    /* if key is in dataset, it is between dataset[lo] and dataset[hi-1] */
    if (lo>=hi) {
        return BS_NOT_FOUND;
    }
    mid = (lo+hi)/2;

    if ((outcome = cmp(key, dataset+mid)) < 0) {
        return binary_search(dataset, lo, mid, key, locn);
    } else if (outcome > 0) {
        return binary_search(dataset, mid+1, hi, key, locn);
    } else {
        *locn = mid;
        return BS_FOUND;
    }
}


int
binary_search_step2(data_t dataset[], int lo, int hi,
                    data_t *key, int *locn) {
    int mid, outcome;
    /* if key is in dataset, it is between dataset[lo] and dataset[hi-1] */
    if (lo>=hi) {
        return BS_NOT_FOUND;
    }
    mid = (lo+hi)/2;

    if ((outcome = cmp(key, dataset+mid)) < 0) {
        printf(" %d", *(dataset+mid));
        return binary_search_step2(dataset, lo, mid, key, locn);
    } else if (outcome > 0) {
        printf(" %d", *(dataset+mid));
        return binary_search_step2(dataset, mid+1, hi, key, locn);
    } else {
        *locn = mid;
        printf(" %d", *(dataset+mid));
        return BS_FOUND;
    }
}

int
binary_search_step3(data_t dataset[], int lo, int hi,
                    data_t *key, int *locn) {
    int mid, outcome;
    /* if key is in dataset, it is between dataset[lo] and dataset[hi-1] */
    if (lo>=hi) {
        return BS_NOT_FOUND;
    }
    mid = (lo+hi)/2;

    if ((outcome = cmp(key, dataset+mid)) < 0) {
        printf(" %d", *(dataset+mid));
        return binary_search_step3(dataset, lo, mid, key, locn);
    } else if (outcome > 0) {
        printf(" %d", *(dataset+mid));
        return binary_search_step3(dataset, mid+1, hi, key, locn);
    } else {
        *locn = mid;
        printf(" %d", *(dataset+mid));
        return BS_FOUND;
    }
}
