#include <iostream>
#include <climits>
#include <cstdint>

using namespace std;

const int N = 100000000 * 2;
const int COUNT = 3;


static uint64_t rdtsc()
{
    uint64_t hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return  lo |  (hi << 32ull);
}

void PrintArray(int* array) {
    for(int i=0;i<N;i++){
        cout << array[i] << " " ;
    }
}

uint64_t Timing(int *Array) {
    uint64_t Time1;
    uint64_t Time2;
    uint64_t TimeMin = ULLONG_MAX;

    for(int j = 0; j < COUNT; j++) {
        Time1 = rdtsc();

        for(int k = 0, i = 0; i < N; i++) {
            k = Array[k];
        }

        Time2 = rdtsc();

        if(TimeMin > Time2 - Time1) {
            TimeMin = Time2 - Time1;
        }
    }

    return TimeMin;
}

void FillArray(int *array, int fragments, int offset, int size){
    int i = 0;
    int j = 1;

    for(i = 0; i < size; i++){
        for(j = 1; j < fragments; j++) {
            array[i + (j - 1) * offset] = i + j * offset;
        }
        array[i + (j - 1) * offset] = i + 1;
    }

    array[i - 1 + (j - 1) * offset] = 0;
}

void RunArray(int *array, int fragments, int offset, int size){
    FillArray(array, fragments, offset, size);
    printf("fragments: %d\t tacts: %lu\n", fragments, Timing(array) / N);
}

int main()
{
    int* Array = new int[N];

    for(int n = 1; n <= 32; n++) {
        RunArray(Array, n, 24 * 1024 * 1024 / sizeof(int), 24 * 1024 * 1024 / sizeof(int));
    }

    delete[] Array;
    return 0;
}