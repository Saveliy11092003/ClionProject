#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
void reverse(char *str) {
    int len = strlen(str);
    for(int i = 0; i < len/2; i++) {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

void reverse_file(char *filename) {
    FILE *f = fopen(filename, "rb+");
    if(f == NULL) {
        printf("Error opening file %s", filename);
        return;
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    char *buffer = (char*)malloc(size);
    fseek(f, 0, SEEK_SET);
    fread(buffer, size, 1, f);
    for(int i = 0; i < size/2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[size-i-1];
        buffer[size-i-1] = temp;
    }
    fseek(f, 0, SEEK_SET);
    fwrite(buffer, size, 1, f);
    fclose(f);
}

void copy_directory(char *source_dir, char *dest_dir) {
    DIR *dir = opendir(source_dir);
    if(dir == NULL) {
        printf("Error opening directory %s", source_dir);
        return;
    }
    mkdir(dest_dir, 0777);
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char source_path[1000];
        sprintf(source_path, "%s/%s", source_dir, entry->d_name);
        char dest_path[1000];
        sprintf(dest_path, "%s/%s", dest_dir, entry->d_name);
        if(entry->d_type == DT_DIR) {
            reverse(entry->d_name);
            copy_directory(source_path, dest_path);
        } else if(entry->d_type == DT_REG) {
            reverse(entry->d_name);
            reverse_file(source_path);
            FILE *source_file = fopen(source_path, "r");
            FILE *dest_file = fopen(dest_path, "w");
            char buffer[1000];
            int read;
            while((read = fread(buffer, 1, 1000, source_file)) > 0) {
                for(int i = 0; i < read/2; i++) {
                    char temp = buffer[i];
                    buffer[i] = buffer[read-i-1];
                    buffer[read-i-1] = temp;
                }
                fwrite(buffer, read, 1, dest_file);
            }
            fclose(source_file);
            fclose(dest_file);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 0;
    }
    char *source_dir = argv[1];
    char dest_dir[1000];
    strcpy(dest_dir, source_dir);
    reverse(dest_dir);
    copy_directory(source_dir, dest_dir);
    return 0;
}