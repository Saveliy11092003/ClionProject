#include <stdio.h>
#include <stdlib.h>
// #define LEVEL_1_CACHE 32768            // 32 KB
// #define LEVEL_2_CACHE 262144 * 2       // 512 KB
#define LEVEL_3_CACHE 1024 * 19 * 1024  // 4 MB
#define OFFSET 36 * 1024 * 1024        // 16 MB
double count(size_t *arr, size_t size) {
    union ticks {
        unsigned long long t64;
        struct s32 {
            long th, tl;
        } t32;
    } start, end;
    double min = -1;
    for (size_t l = 0; l < 23; l++) {
        int k = 0;
        asm volatile("rdtsc\n" : "=a"(start.t32.th), "=d"(start.t32.tl));
        for (size_t i = 0; i != size; i++) {
            k = arr[k];
        }
        asm volatile("rdtsc\n" : "=a"(end.t32.th), "=d"(end.t32.tl));
        if (!l)
            min = ((double)(end.t64 - start.t64));
        else if (min > ((double)(end.t64 - start.t64)))
            min = ((double)(end.t64 - start.t64));
    }
    return min / size;
}
int main(int argc, char **argv) {
    size_t n = 1;
    size_t size = (LEVEL_3_CACHE) / sizeof(size_t);
    size_t offset = OFFSET / sizeof(size_t);
    for (n = 1; n <= 32; n++) {
        size_t *mas = (size_t *)malloc(offset * n * sizeof(size_t));
        for (size_t i = 0; i < n - 1; i++) {
            for (size_t j = 0; j < size / n; j++) {
                mas[offset * i + j] = (i + 1) * offset + j;
            }
        }
        for (size_t j = 0; j < size / n; j++) {
            mas[offset * (n - 1) + j] = (j + 1);
        }
        printf("for %lu fragments: %d ticks \n", n, (int)count(mas, size * n));
    }
    return 0;
}