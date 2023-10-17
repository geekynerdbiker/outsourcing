//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <string.h>
//#include <time.h>
//#include <limits.h>
//
///******************************************************************************************************/
//#include <Windows.h>
//#define CHECK_TIME_START(start,freq) QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
//#define CHECK_TIME_END(start,end,freq,time) QueryPerformanceCounter((LARGE_INTEGER*)&end); time = (float)((float)(end - start) / (freq * 1.0e-3f))
//
//__int64 _start, _freq, _end;
//float compute_time;
///******************************************************************************************************/
//
//
//#define CHECK_GENERATED_DATA
//#undef CHECK_GENERATED_DATA
//
//#define N_ELEMENTS 1024
//#define FILE_NAME_PREFIX  "input_data"
//
//int Validation(int* data, int left, int right);
//int Insertion_Sort(int *data, int left, int right);
//int partition(int *data, int left, int right);
//void Quick_Sort_PISTRO(int *data, int left, int right);
//
//int main(int argc, char **arvgv) {
//    unsigned scale_factor_uint = UINT_MAX >> 2;
//    char file_name[128];
//    FILE *fp;
// 
//    int n = N_ELEMENTS; // n is the number of data elements to be written
//    sprintf(file_name, "%s_%d.bin", FILE_NAME_PREFIX, n);
//
//    fprintf(stdout, "^^^ UNIT_MAX = %u\n", UINT_MAX);
//    fprintf(stdout, "^^^ RAND_MAX = %u\n\n", RAND_MAX);
//
//    if ((fp = fopen(file_name, "wb")) == NULL) {
//        fprintf(stderr, "Error: cannot open the binary file %s for writing...\n", file_name);
//        exit(-1);
//    }
//
//    fwrite(&n, sizeof(unsigned int), 1, fp);
//    srand((unsigned int)time(NULL));
//
//    CHECK_TIME_START(_start, _freq);
//    for (int i = 0; i < n; i++) {
//        //
//        // For more efficient read/write operations, use a buffer of proper size!!!
//        //
//        unsigned int key = (unsigned int)((((float)rand()) / RAND_MAX) * (((float)rand()) / RAND_MAX) * (((float)rand()) / RAND_MAX) *
//            (((float)rand()) / RAND_MAX) * (float)scale_factor_uint);
//
//        fwrite(&key, sizeof(unsigned int), 1, fp);
//    }
//    CHECK_TIME_END(_start, _end, _freq, compute_time);
//    fprintf(stdout, "\n^^^ Time for generating %d elements = %.3fms\n\n", n, compute_time);
//
//    fclose(fp);
//
//#ifdef CHECK_GENERATED_DATA
//    if ((fp = fopen(file_name, "rb")) == NULL) {
//        fprintf(stderr, "Error: can not open the binary file %s for reading...\n", file_name);
//        exit(-1);
//    }
//    fread(&n, sizeof(int), 1, fp);
//    fprintf(stdout, "*** Number of elements = %d\n", n);
//
//    for (int i = 0; i < n; i++) {
//        unsigned int key;
//        fread(&key, sizeof(unsigned int), 1, fp);
//        fprintf(stdout, " [%d] %11u\n", i, key);
//    }
//    fclose(fp);
//#endif
//}
//
//int Validation(int* data, int left, int right) {
//    for (int i = left; i < right - 1; i++) {
//        if (data[i] > data[i + 1])
//            return -1;
//    }
//    return 0;
//}
//
//int Insertion_Sort(int *data, int left, int right)
//{
//    int x, i = left+1, j;
//    while (i < right + 1) {
//        x = data[i];
//        j = i - 1;
//        while (j >= left && data[j] > x) {
//            data[j + 1] = data[j];
//            j--;
//        }
//        data[j + 1] = x;
//        i++;
//    }
//    return 0;
//}
//
//int partition(int *data, int left, int right)
//{
//    int pivot, temp;
//    int i, j;
//
//    i = left;
//    temp = data[left];
//    for (j = left + 1;j <= right;j++)
//    {
//        if (data[j] < temp)
//        {
//            i++;
//            SWAP(data[j], data[i]);
//        }
//    }
//    pivot = i;
//    SWAP(data[left], data[pivot]);
//
//    return pivot;
//}
//
//void Quick_Sort_PISTRO(int *data, int left, int right)
//{
//    if (left >= right)
//        return 0;
//
//    if (left == 0 && right == N - 1)
//    {
//        CHECK_TIME_START;
//    }
//
//    while (left < right)
//    {
//        int pivot = partition(data, left, right);
//
//        if (pivot - left < right - pivot)
//        {
//            Quick_Sort_PISTRO(data, left, pivot - 1);
//            left = pivot + 1;
//        }
//
//        else
//        {
//            Quick_Sort_PISTRO(data, pivot + 1, right);
//            right = pivot - 1;
//        }
//    }
//
//    if (left == 0 && right == N - 1)
//    {
//        Insertion_Sort(data, left, right);
//        CHECK_TIME_END(resultTime);
//    }
//}
