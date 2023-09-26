#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fstream>

#define AMOUNT_WORK 1

using namespace std;

int taskSend, taskLeft;
int threadRank, threadSize;
int Sum = 0;

pthread_mutex_t mutex;
pthread_cond_t finishTasks, newTasksAvailable;
pthread_t sendThread, receiveThread, executeThread;

int executedWork, executedThreadTasks, tasks;

bool sendThreadGetSignal = false;
bool executeThreadGetSignal = false;

void collectTasks() {
    char threadRankPath[5];
    for(int i=0; i<threadSize;i++) {
        threadRankPath[0] = i + '0';
        memcpy(threadRankPath + 1, ".txt", 4);
        ifstream in(threadRankPath);

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

void initAmountTask(int* tasksPerProc){
    if(threadRank == 0){
        *tasksPerProc = 20;
        printf("Amount Task Before %d", *tasksPerProc);
    }
    else{
        *tasksPerProc = 0;
    }

    /*
     int a = 30;
     int b = 20;

     if(threadRank == 0){
        *tasksPerProc = a;
        printf("Amount Task Before %d", a+b);
    }
     else if(threadRank == 1){
        *tasksPerProc = b;
    }
    else{
        *tasksPerProc = 0;
    }
    */
}

void* sendRequest(void* r) {
    MPI_Status status;
    while (true) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&finishTasks, &mutex);
        sendThreadGetSignal = true;
        if (executedWork > AMOUNT_WORK) {
            pthread_exit(NULL);
        }
        bool sendRequestFlag = true;
        int recvTaskAmount;
        for (int i = 0; i < threadSize; i++) {
            if (i == threadRank)
                continue;
            MPI_Send(&sendRequestFlag, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Recv(&recvTaskAmount, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            if (recvTaskAmount == 0)
                continue;
            break;
        }
        tasks = recvTaskAmount;
        executedThreadTasks = 0;
        while (executeThreadGetSignal == false)
            pthread_cond_signal(&newTasksAvailable);
        executeThreadGetSignal = false;
        pthread_mutex_unlock(&mutex);
    }
}

void* recvRequest(void* r) {
    MPI_Status status;
    while (true) {
        bool recvRequestFlag = false;
        MPI_Recv(&recvRequestFlag, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        if (recvRequestFlag == false) {
            pthread_exit(NULL);
        }
        pthread_mutex_lock(&mutex);
        taskSend = (tasks - executedThreadTasks) / 2;
        taskLeft = (tasks - executedThreadTasks + 1) / 2;
        MPI_Send(&taskSend, 1, MPI_INT, status.MPI_SOURCE, 2, MPI_COMM_WORLD);
        if (taskSend != 0) {
            tasks = executedThreadTasks + taskLeft;
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* execute(void* r) {
    int tasksPerProc;
    initAmountTask(&tasksPerProc);

    executedWork = 0;
    double iterTime;
    char threadRankPath[5];
    threadRankPath[0] = threadRank + '0';
    memcpy(threadRankPath + 1, ".txt", 4);

    FILE* in = fopen(threadRankPath, "w");

    for (int count = 0; count < AMOUNT_WORK; count++) {
        double start = MPI_Wtime();

        tasks = tasksPerProc;
        executedThreadTasks = 0;
        int totalExecutedTasks = 0;
        while(true) {

            for (int taskId = 0; taskId < tasks; taskId++) {
                executedThreadTasks++;
                sleep(1);
            }

            totalExecutedTasks += executedThreadTasks;

            pthread_mutex_lock(&mutex);

            while (sendThreadGetSignal == false)
                pthread_cond_signal(&finishTasks);

            sendThreadGetSignal = false;
            pthread_cond_wait(&newTasksAvailable, &mutex);
            executeThreadGetSignal = true;
            pthread_mutex_unlock(&mutex);
            if (tasks == 0) {
                break;
            }
        }

        double end = MPI_Wtime();
        iterTime = end - start;
        int iterCounter = executedWork;

        fprintf(in, "%d - %d - %d - %f\n", totalExecutedTasks, threadRank, iterCounter, iterTime);
        executedWork++;

        MPI_Barrier(MPI_COMM_WORLD);
    }

    pthread_mutex_lock(&mutex);
    int recvRequestFlag = false;
    MPI_Send(&recvRequestFlag, 1, MPI_INT, threadRank, 0, MPI_COMM_WORLD);
    executedWork++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&finishTasks);

    fclose(in);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int providedLvl;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &providedLvl);

    if (providedLvl != MPI_THREAD_MULTIPLE) {
        MPI_Finalize();
        return -1;
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);
    MPI_Comm_size(MPI_COMM_WORLD, &threadSize);

    pthread_mutex_init(&mutex, NULL);


    pthread_cond_init(&finishTasks, NULL);
    pthread_cond_init(&newTasksAvailable, NULL);

    double start = MPI_Wtime();

    pthread_attr_t attrs;
    pthread_attr_init(&attrs);

    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE);

    pthread_create(&sendThread, &attrs, sendRequest, NULL);
    pthread_create(&receiveThread, &attrs, recvRequest, NULL);
    pthread_create(&executeThread, &attrs, execute, NULL);

    pthread_attr_destroy(&attrs);

    pthread_join(sendThread, NULL);
    pthread_join(receiveThread, NULL);
    pthread_join(executeThread, NULL);

    double end = MPI_Wtime();

    if (threadRank == 0) {
        printf("\nTime: %lf\n", end - start);
        collectTasks();
        printf("Amount Tasks After: %d\n", Sum);
    }

    pthread_mutex_destroy(&mutex);

    pthread_cond_destroy(&finishTasks);
    pthread_cond_destroy(&newTasksAvailable);

    MPI_Finalize();
    return 0;
}