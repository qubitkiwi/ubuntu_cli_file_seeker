#ifndef __COMMON_H__
#define __COMMON_H__

#include <sys/stat.h>   // struct stat

struct file_info {
    char name[255];
    char *type;
    int size;
    char time[17];
};


// kbhit.c
int kbhit(void);

// dir.c

int file_update(char *file_path, struct file_info *files);\
int file_show(char *file_path, struct file_info *files);
int path_update(char *now_file_path, char *new_file_path);
int high_path(char *file_path);

int dir_size(struct stat *buf);
int dir_time(struct stat *buf, struct file_info *file);
char* dir_type(const struct stat *buf);

int is_dir(const char *file_name);


// history.c
int history_update(char *save_path, char *file_path, struct file_info *files);
const char* Time();

#endif