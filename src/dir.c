#include "common.h"

#include <stdio.h>
#include <string.h>

#include <unistd.h>     // lstat
#include <sys/types.h>

#include <dirent.h>     // DIR
#include <time.h>

int file_update(char *file_path, struct file_info *files) {

    DIR *dp;                //디렉터리 조작을 위한 스트림
    struct dirent *dirt;    //디렉터리의 항목을 위한 구조체
    struct stat dir;        //각 디렉터리 구조체

    if((dp = opendir(file_path)) == NULL) {
        perror("directory open error\n");
        return -1;
  	}

    int idx=0;

    while((dirt = readdir(dp)) != NULL) {
        if(dirt->d_ino == 0) continue;

        lstat(dirt->d_name, &dir);

        strcpy(files[idx].name, dirt->d_name);
        files[idx].size = dir_size(&dir);
        dir_time(&dir, &files[idx]);
        files[idx].type = dir_type(&dir);
        idx++;
    }
    strcpy(files[idx].name, "");

    closedir(dp);
    return 0;
}

int file_show(char *file_path, struct file_info *files) {
    printf("%s\n", file_path);
    printf("%-16s %-10s %15s %17s\n", "이름", "타입", "크기", "수정날짜");
    for (int idx=0; strcmp(files[idx].name, "") != 0; idx++) {
        printf("%-15s %-10s %10d %s\n",files[idx].name, files[idx].type, files[idx].size, files[idx].time);
    }
    printf("========================================================\n");
}

int is_dir(const char *file_name){
    struct stat dir;
    lstat(file_name, &dir);
    if(S_ISDIR(dir.st_mode)) 
        return 1;
    return 0;
}

char* dir_type(const struct stat *buf) {         
    if(S_ISDIR(buf->st_mode)) 
        return "DIR";
    else if(S_ISREG(buf->st_mode)) 
        return "FILE"; 
    else if(S_ISSOCK(buf->st_mode)) 
        return "SOCKET";
    else if(S_ISCHR(buf->st_mode))
        return "CHARACTER DEVICE";
    else if(S_ISFIFO(buf->st_mode))
        return "FIFO";
    else if(S_ISBLK(buf->st_mode))
        return "BLOCK DEVICE";
    else if(S_ISLNK(buf->st_mode))
        return "LINK";
    // else
    //     return "none";
}

int dir_time(struct stat *buf, struct file_info *file) { 
    struct tm *mtime; 

    mtime=localtime(&buf->st_mtime); 
    sprintf(file->time ,"%04d-%02d-%02d %02d:%02d", 
            mtime->tm_year+1900, mtime->tm_mon+1, 
            mtime->tm_mday, mtime->tm_hour, 
            mtime->tm_min); 
    return 0;
}

int dir_size(struct stat *buf) {
    return buf->st_size;
}

int path_update(char *now_file_path, char *new_file_path) {
    
    if (strcmp(new_file_path, "..") == 0) {
        high_path(now_file_path);
    } else {
        strcat(now_file_path, "/");
        strcat(now_file_path, new_file_path);
    }
    chdir(now_file_path);

    return 1;    
}

int high_path(char *file_path) {
    int len = strlen(file_path);
    for( ; len>=0 ; len--) {
        if (file_path[len] == '/') {
            file_path[len] = '\0';
            return 0;
        }
    }
    return -1;
}