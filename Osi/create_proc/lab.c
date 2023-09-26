#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define ERROR -1
#define SUCCESS 0

int global_var = 10;

int work_with_proc(){
    int return_value_sleep;
    int local_var = 20;
    printf("Адрес глобальной переменной: %p Значение глобальной переменной: %d\n", &global_var, global_var);
    printf("Адрес локальной переменной: %p Значение локальной переменной: %d\n", &local_var, local_var);
    printf("pid процесса: %d\n", getpid());
    int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "ERROR in fork() from work_with_proc %s\n", strerror(errno));
        return ERROR;
    }
    if (pid == 0) {
        printf("Это дочерний процесс: pid %d\n", getpid());
        return_value_sleep = sleep(20);
        if(return_value_sleep != 0){
            fprintf(stderr,  "Error in function sleep %s\n", strerror(errno));
            return ERROR;
        }

        printf("parent pid %d\n", getppid());
        printf("Адрес глобальной переменной в дочернем процессе: %p Значение глобальной переменной в дочернем процессе: %d\n", &global_var, global_var);
        printf("Адрес локальной переменной в дочернем процессе: %p Значение локальной переменной в дочернем процессе: %d\n", &local_var, local_var);
        global_var = 30;
        local_var = 40;
        printf("Адрес глобальной переменной в дочернем процессе: %p Значение глобальной переменной в дочернем процессе: %d\n", &global_var, global_var);
        printf("Адрес локальной переменной в дочернем процессе: %p Значение локальной переменной в дочернем процессе: %d\n", &local_var, local_var);
        return_value_sleep = sleep(10);
        if(return_value_sleep != 0){
            fprintf(stderr,  "Error in function sleep %s\n", strerror(errno));
            return ERROR;
        }
        exit(5);
    } else {
        printf("Это родительский процесс: pid %d\n", getpid());
        printf("Адрес глобальной переменной в родительском процессе: %p Значение глобальной переменной в родительском процессе: %d\n", &global_var, global_var);
        printf("Адрес локальной переменной в родительском процессе: %p Значение локальной переменной в родительском процессе: %d\n", &local_var, local_var);
        return_value_sleep =sleep(40);
        if(return_value_sleep != 0){
            fprintf(stderr,  "Error in function sleep %s\n", strerror(errno));
            return ERROR;
        }
        int status;
        int child_pid = wait(&status);
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Дочерний процесс %d завершился с кодом %d\n", child_pid, exit_code);
        } else {
            printf("Дочерний процесс %d завершился нормально\n", child_pid);
        }
    }
    return SUCCESS;
}

int main() {
    if(work_with_proc() == ERROR){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

