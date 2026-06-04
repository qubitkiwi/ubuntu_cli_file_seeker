#include "common.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

int history_update(char *save_path, char *file_path, struct file_info *files) {

    char save_dir[255];

    strcpy(save_dir, save_path);
    strcat(save_dir, "/dir_history.txt");

    FILE* fp = fopen(save_dir,"a");   // dir_history파일을 a(쓰기) 모드로 열기
    
    fprintf(fp, "\n검색시간 : %s\n",Time());
    fprintf(fp, "%s\n", file_path);
    fprintf(fp, "%-16s %-10s %15s %17s\n", "이름", "타입", "크기", "수정날짜");
    for (int idx=0; strcmp(files[idx].name, "") != 0; idx++) {
        fprintf(fp, "%-15s %-10s %10d %s\n",files[idx].name, files[idx].type, files[idx].size, files[idx].time);
    }
    fprintf(fp, "========================================================\n");

    fclose(fp); //파일 포인터 닫기
}


const char* Time() { 
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); 
    static char str[17];      
    
    sprintf(str,"%04d-%02d-%02d %02d:%02d", 
            tm.tm_year+1900, tm.tm_mon+1, 
            tm.tm_mday, tm.tm_hour, 
            tm.tm_min); 
    return str;
} 