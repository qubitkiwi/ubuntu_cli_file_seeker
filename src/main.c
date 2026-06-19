#include <ncurses.h>
#include <locale.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>     // getcwd()

#include "common.h"
#include "kbhit.h"

int main()
{
    char save_path[255];
    char file_path[255];
    struct file_info files[255];
    
    setlocale(LC_ALL, "");
    initscr();
    kbhit_init();

    getcwd(file_path, 255);
    strcpy(save_path, file_path);

    if (file_update(file_path, files) == -1) {
        perror("file_update");
    }
    file_show(file_path, files);
    refresh();

    if (history_update(save_path, file_path, files) == -1) {
        perror("history_update");
    }

    

    int select = 0;
    while (1) {
        if(kbhit())
        {
            switch(getchar()) {
                case 's':
                    if(strcmp(files[select + 1].name, "")) select++;
                break;
                
                case 'w':
                    if (select > 0) select--;
                break;

                case 'q':
                    kbhit_uninit();
                    endwin();
                    return 0;
                break;

                case 'e':
                    if(is_dir(files[select].name) == 1) {
                        clear();
                        path_update(file_path, files[select].name);
                        file_update(file_path, files);
                        history_update(save_path, file_path, files);
                        file_show(file_path, files);
                        select = 0;                  
                    }
                break;
            }
            int y, x;
            getyx(stdscr, y, x);   // 현재 커서 위치 얻기

            move(y, 0);            // 같은 줄의 맨 앞으로 이동
            clrtoeol();            // 현재 위치부터 줄 끝까지 지우기
            printw("select : %20s", files[select].name);
            refresh();
        }
    }

    endwin();
    kbhit_uninit();

    return 0;
}