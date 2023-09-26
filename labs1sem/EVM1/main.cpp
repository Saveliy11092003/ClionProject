#include <iostream>
#include <math.h>
//#include <sys/times.h>
//#include <unistd.h>
#include <time.h>


double CalculatePi(int n) {
    double result = 0;
    for (int i = 0; i <= n; ++i) {
        result += 4 * (pow(-1, i) / (double)(2 * i + 1));
    }
    return result;
}

int main(void) {
    int n;
    printf("Enter number: ");
    scanf("%d", &n);
    if(n <= 0){
        printf("Invalid number entered");
        return 0;
    }
    double result;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

//    struct tms start, end;
//    long clocks_per_sec = sysconf(_SC_CLK_TCK);
//    long clocks;
 //   times(&start);

    result = CalculatePi(n);

//    times(&end);

 //   clocks = end.tms_utime - start.tms_utime; printf("Time taken: %lf sec.\n",(double)clocks / clocks_per_sec);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken: %lf sec.\n",end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec));
    printf("The pi is: %lf", result);
}