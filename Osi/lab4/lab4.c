#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define TIME_SLEEP 180
#define CREATE_OR_CHANGE_VALUE 1
#define ERROR -1
#define SUCCESS 0


int main() {
    char *environment_variable = getenv("MY_ENV_VAR");
    printf("Environment variable value: %s\n", environment_variable);
    int return_value_setenv = setenv("MY_ENV_VAR", "new value", CREATE_OR_CHANGE_VALUE);
    if(return_value_setenv == -1){
        return ERROR;
    }
    environment_variable = getenv("MY_ENV_VAR");
    printf("Changed environment variable value: %s\n", environment_variable);
    int return_value_sleep = sleep(TIME_SLEEP);
    if(return_value_sleep != 0){
        fprintf(stderr,  "Error in function sleep %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
