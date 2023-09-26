#include <unistd.h>
#include <fstream>
#include <mpi.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

#define AMOUNT_WORK 1
#define COUNT_TASKS 20

using namespace std;

pthread_t sThread;
pthread_t rThread;
pthread_t eThread;

pthread_cond_t finishTasks;
pthread_cond_t newTasksAvail;

pthread_mutex_t mutex;
pthread_mutex_t sThreadMutex;
pthread_mutex_t eThreadMutex;

int threadR;
int threadS;
int Sum = 0;
int taskS;
int taskL;

int  exThreadTasks;
int tasks;
int exWork;

bool sThreadGetSignal = false;
bool eThreadGetSignal = false;

void collectTasks() {
    char threadRPath[5];
    for(int i=0; i<threadS;i++) {
        threadRPath[0] = i + '0';
        memcpy(threadRPath + 1, ".txt", 4);
        ifstream in(threadRPath);

        string str;
        char ch;

        while (in.get(ch)) {
            if (isdigit(ch)) {
                str += ch;
            } else {
                break;
            }
        }

        int num = stoi(str);
        Sum += num;
    }
}

void initAmountTasks(int* tasksPerProc){
    if(threadR == 0){
        *tasksPerProc = 100;
        printf("Amount Task Before %d", *tasksPerProc);
    }
    else{
        *tasksPerProc = 0;
    }

    /*
     int a = 30;
     int b = 20;

     if(threadR == 0){
        *tasksPerProc = a;
        printf("Amount Task Before %d", a+b);
    }
     else if(threadR == 1){
        *tasksPerProc = b;
    }
    else{
        *tasksPerProc = 0;
    }
    */
}

void* rRequest(void* r) {
    MPI_Status status;
    while (true) {
        bool rRequestFlag = false;
        MPI_Recv(&rRequestFlag, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        if (rRequestFlag == false) {
            pthread_exit(NULL);
        }
        pthread_mutex_lock(&mutex);
        taskS = (tasks - exThreadTasks) / 2;
        taskL = (tasks - exThreadTasks + 1) / 2;
        if (taskS != 0) {
            tasks = exThreadTasks + taskL;
        }
        pthread_mutex_unlock(&mutex);
        MPI_Send(&taskS, 1, MPI_INT, status.MPI_SOURCE, 2, MPI_COMM_WORLD);
    }
}

void* sRequest(void* r) {
    MPI_Status status;
    while (true) {
        pthread_mutex_lock(&sThreadMutex);
        pthread_cond_wait(&finishTasks, &sThreadMutex);
        sThreadGetSignal = true;
        if (exWork > AMOUNT_WORK) {
            pthread_mutex_unlock(&sThreadMutex);
            pthread_exit(NULL);
        }
        bool sRequestFlag = true;
        int recvTaskAmount;
        for (int i = 0; i < threadS; i++) {
            if (i == threadR)
                continue;
            MPI_Send(&sRequestFlag, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Recv(&recvTaskAmount, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            if (recvTaskAmount == 0)
                continue;
            break;
        }
        pthread_mutex_lock(&mutex);
        tasks = recvTaskAmount;
        exThreadTasks = 0;
        while (eThreadGetSignal == false)
            pthread_cond_signal(&newTasksAvail);
        eThreadGetSignal = false;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&sThreadMutex);
    }
}

void* ex(void* r) {
    int tasksPerProc;
   // tasksPerProc = COUNT_TASKS / threadS;
    initAmountTasks(&tasksPerProc);

    exWork = 0;
    double iterTime;
    char threadRPath[5];
    threadRPath[0] = threadR + '0';
    memcpy(threadRPath + 1, ".txt", 4);

    FILE* in = fopen(threadRPath, "w");

    for (int count = 0; count < AMOUNT_WORK; count++) {
        double start = MPI_Wtime();

        tasks = tasksPerProc;
        exThreadTasks = 0;
        int totalExTasks = 0;
        while(true) {

            for (int taskId = 0; taskId < tasks; taskId++) {
                exThreadTasks++;
                sleep(1);
            }

            totalExTasks += exThreadTasks;

            pthread_mutex_lock(&eThreadMutex);

            while (sThreadGetSignal == false)
                pthread_cond_signal(&finishTasks);

            sThreadGetSignal = false;
            pthread_cond_wait(&newTasksAvail, &eThreadMutex);
            eThreadGetSignal = true;
            pthread_mutex_unlock(&eThreadMutex);
            if (tasks == 0) {
                break;
            }
        }

        double end = MPI_Wtime();
        iterTime = end - start;

        fprintf(in, "%d - %d - %d - %f\n", totalExTasks, threadR, exWork, iterTime);
        exWork++;

        MPI_Barrier(MPI_COMM_WORLD);
    }

    int recvRequestFlag = false;
    MPI_Send(&recvRequestFlag, 1, MPI_INT, threadR, 0, MPI_COMM_WORLD);
    pthread_mutex_lock(&mutex);
    exWork++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&finishTasks);

    fclose(in);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);

    if (provided != MPI_THREAD_MULTIPLE) {
        MPI_Finalize();
        return -1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &threadR);
    MPI_Comm_size(MPI_COMM_WORLD, &threadS);

    pthread_mutex_init(&sThreadMutex, NULL);
    pthread_mutex_init(&eThreadMutex, NULL);
    pthread_mutex_init(&mutex, NULL);

    pthread_cond_init(&newTasksAvail, NULL);
    pthread_cond_init(&finishTasks, NULL);

    double startTime = MPI_Wtime();

    pthread_attr_t attrs;
    pthread_attr_init(&attrs);

    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE);

    pthread_create(&sThread, &attrs, sRequest, NULL);
    pthread_create(&rThread, &attrs, rRequest, NULL);
    pthread_create(&eThread, &attrs, ex, NULL);

    pthread_attr_destroy(&attrs);

    pthread_join(sThread, NULL);
    pthread_join(rThread, NULL);
    pthread_join(eThread, NULL);

    double finishTime = MPI_Wtime();

    if (threadR == 0) {
        printf("\nTime: %lf\n", finishTime - startTime);
        collectTasks();
        printf("Amount Tasks After: %d\n", Sum);
    }

    pthread_cond_destroy(&finishTasks);
    pthread_cond_destroy(&newTasksAvail);
    pthread_mutex_destroy(&sThreadMutex);
    pthread_mutex_destroy(&eThreadMutex);
    pthread_mutex_destroy(&mutex);

    MPI_Finalize();
    return EXIT_SUCCESS;
}