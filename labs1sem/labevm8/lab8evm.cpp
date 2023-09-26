#include <iostream>
#include <set>
#include <x86intrin.h>
#include <cstdint>
#include <random>

using namespace std;

void printArray(int* Array, int n){
    for(int i=0;i<n;i++) {
        cout << Array[i] << "    index: " << i << endl;
    }
    cout << endl;
}

void Straight(int *Array, int n){
    for(int i = 0; i < n - 1; ++i) {
        Array[i] = i + 1;
    }

    Array[n - 1] = 0;
}

void Revers(int *Array, int n){
    for(int i = n - 1; i > 0; --i) {
        Array[i] = i - 1;
    }

    Array[0] = n - 1;
}

void Random(int *Array, unsigned int N) {
    set<int> UsedNumbers;
    UsedNumbers.insert(0);
    mt19937 rnd(4322);
    int PreviousNumber = 0;
    for(int i=0,number;i<N-1;i++) {
        do{
            number = rnd() % N;
        }while(UsedNumbers.find(number) != UsedNumbers.end());
        Array[PreviousNumber] = number;
        PreviousNumber = number;
        UsedNumbers.insert(PreviousNumber);
    }
    Array[PreviousNumber] = 0;
}

void CheckRandom(int* Array, int N){
    bool* arrayCheck = new bool[N];
    for(int i=0;i<N;i++){
        arrayCheck[i] = false;
    }

    int count =0;

    for (int i = 0, k=0; i < N; ++i) {
       if(arrayCheck[k] == true){
           break;
       }
       count++;
       arrayCheck[k] = true;
       k = Array[k];
    }
    cout << count << " " << N << endl;
    printArray(Array, N);
    delete []arrayCheck;
}


int CheckK(int k){
    if(k == 12345){
        cout << "wow" <<endl;
    }
    return 0;
}

const int MaxN = 32 * 1024 * 256;
const int MinN = 256;

int main(int argc, char **argv) {
    int i,k;
    uint64_t Begin,Ticks;
    int *Array = new int[MaxN];

 for(float K=1, N = MinN; N<=MaxN; K *= 1.2, N = K * MinN) {
        Straight(Array, N);

        for (i = 0, k = 0; i < N; i++) {
            k = Array[k];
        }

        CheckK(k);

        Begin = __rdtsc();

        for (i = 0, k = 0; i < N; i++) {
            k = Array[k];
        }

        Ticks = (__rdtsc() - Begin) / i;
        CheckK(k);
        cout << Ticks << " " << N << endl;
    }
    cout << endl;
    for(float K=1, N = MinN; N<=MaxN; K *= 1.2, N = K * MinN) {
        Revers(Array, N);

        for (k = i-1, i = 0; i < N; i++) {
            k = Array[k];
        }

        CheckK(k);

        Begin = __rdtsc();

        for (k = i-1, i = 0; i < N; i++) {
            k = Array[k];
        }

        Ticks = (__rdtsc() - Begin) / i;
        CheckK(k);
        cout << Ticks << " " << N << endl;
    }
    cout << endl;
    for(float K=1, N = MinN; N<=MaxN; K *= 1.2, N = K * MinN) {
        Random(Array, N);
        for (i = 0, k = 0; i < N; i++) {
            k = Array[k];
        }

        CheckK(k);

        Begin = __rdtsc();

        for (i = 0, k = 0; i < N; i++) {
            k = Array[k];
        }
        Ticks = (__rdtsc() - Begin) / i;
        CheckK(k);
        cout << Ticks << " " << N << endl;
    }
    cout << endl;

    delete[] Array;

    return 0;
}