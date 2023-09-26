#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>

enum Status_Create_Dir {
    DIRECTORY_CREATION_SUCCESSFUL,
    INVALID_NAME_OF_SOURCE_DIRECTORY
};

enum Status_Copy_Dir {
    DIRECTORY_COPY_SUCCESSFUL,
    ERROR_OPEN_DIRECTORY
};

void reverse_string(char *str) {
    size_t length = strlen(str);

    for (int i = 0; i < length/2; i++) {
        char temp = str[i];
        str[i] = str[length-i-1];
        str[length-i-1] = temp;
    }
}

void reverse_filename(char* file_name) {
    char* dot = strrchr(file_name, '.');  // find the last dot in the filename
    if (dot != NULL) {  // if there is a dot, reverse only the filename before it
        int i = 0;
        int j = dot - file_name - 1;
        while (i < j) {
            char temp = file_name[i];
            file_name[i] = file_name[j];
            file_name[j] = temp;
            i++;
            j--;
        }
    } else {  // if there is no dot, reverse the entire filename
        reverse_string(file_name);
    }
}

void reverse_file_contents(FILE* new_file) {
    fseek(new_file, 0, SEEK_END);
    int file_size = ftell(new_file);
    char* contents = (char*)malloc(file_size * sizeof(char));
    fseek(new_file, 0, SEEK_SET);
    fread(contents, file_size, 1, new_file);
    reverse_string(contents);
    fseek(new_file, 0, SEEK_SET);
    fwrite(contents, file_size, 1, new_file);
    fclose(new_file);
}

void copy_file(char* path_source_file, char* path_new_file) {
    char symbol;
    FILE *source_file;
    FILE *new_file;
    source_file = fopen(path_source_file, "r");
    if(source_file == NULL) {
        printf("Error in Opening the file, %s\n", path_source_file);
        return;
    }
    new_file = fopen(path_new_file, "w");
    if(new_file == NULL) {
        printf("Error in Opening the file, %s\n", path_new_file);
        return;
    }
    symbol = fgetc(source_file);
    while(symbol != EOF) {
        fputc(symbol, new_file);
        symbol = fgetc(source_file);
    }
    fclose(source_file);
    fclose(new_file);
    reverse_file_contents(new_file);
}

Status_Copy_Dir copy_directory(char* path_source_dir, char* path_new_dir) {
    DIR *dir;
    struct dirent *ent;
    struct stat st;
    char path_source_file[1024];
    char path_new_file[1024];
    char reversed_name_file[1024];
    dir = opendir(path_source_dir);
    if(dir == NULL) {
        printf("Error in Opening the directory, %s\n", path_source_dir);
        return ERROR_OPEN_DIRECTORY;
    }
    while((ent = readdir(dir)) != NULL) {
        sprintf(path_source_file, "%s/%s", path_source_dir, ent->d_name);
        sprintf(reversed_name_file, "%s", ent->d_name);
        reverse_filename(reversed_name_file);
        sprintf(path_new_file, "%s/%s", path_new_dir, reversed_name_file);
        if(stat(path_source_file, &st) == 0 && S_ISREG(st.st_mode)) {
            copy_file(path_source_file, path_new_file);
            printf("Copied file: %s\n", ent->d_name);
        }
    }
    closedir(dir);
    return DIRECTORY_COPY_SUCCESSFUL;
}

void get_name_dir(char* name_new_dir, char* ptr_last_slash, int size_dir_name) {
    for(int i=0;i<size_dir_name;i++){
        name_new_dir[i] = ptr_last_slash[i+1];
    }
}

void get_path_parent_dir(char* path_source_dir, char* path_parent_dir, int size_path_parent_dir) {
    for(int i=0;i< size_path_parent_dir; i++){
        path_parent_dir[i] = path_source_dir[i];
    }
}

Status_Create_Dir create_reversed_directory(char* path_source_dir, char* path_new_dir) {
    char* ptr_last_slash = strrchr(path_source_dir, '/');
    if (ptr_last_slash == NULL) {
        printf("Error: invalid directory\n");
        return INVALID_NAME_OF_SOURCE_DIRECTORY;
    }
    size_t size_dir_name = strlen(ptr_last_slash) - 1;
    char* name_new_dir = (char*)malloc(size_dir_name * sizeof(char));

    get_name_dir(name_new_dir, ptr_last_slash, size_dir_name);

    reverse_string(name_new_dir);
    ssize_t size_path_parent_dir = strlen(path_source_dir) - strlen(ptr_last_slash)+1;
    char* path_parent_dir = (char*)malloc(size_path_parent_dir);//////////////////////////////////////////////////////////////////
    get_path_parent_dir(path_source_dir, path_parent_dir, size_path_parent_dir);

    sprintf(path_new_dir, "%s%s", path_parent_dir, name_new_dir);
    mkdir(path_new_dir, 0777);//////////////////////////////////////////////////////////////////

    free(name_new_dir);
    free(path_parent_dir);
    return DIRECTORY_CREATION_SUCCESSFUL;
}

int main() {
    char* path_source_dir = "/home/user/CLionProjects/Osi/Dir_for_task";
    size_t size_path_source_dir = strlen(path_source_dir);

    char* path_new_dir = (char*)malloc(size_path_source_dir * sizeof(char));

    if (create_reversed_directory(path_source_dir, path_new_dir) == INVALID_NAME_OF_SOURCE_DIRECTORY) {
        return EXIT_FAILURE;
    }

    if(copy_directory(path_source_dir, path_new_dir) == ERROR_OPEN_DIRECTORY) {
        return EXIT_FAILURE;
    }
    printf("Finished copying all files.\n");
    free(path_new_dir);
    return EXIT_SUCCESS;
}
