#include <stdio.h>
#include <string.h>
#include <unistd.h>     // getcwd()

#include "common.h"

int main() {

    char save_path[255];
    char file_path[255];
    char file_names[255][255];
    struct file_info files[255];
    

    getcwd(file_path, 255);
    strcpy(save_path, file_path);

    if (file_update(file_path, files) == -1) {
        perror("file_update");
    }
    file_show(file_path, files);

    if (history_update(save_path, file_path, files) == -1) {
        perror("history_update");
    }

    int select = 0;
    char b;
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
                    return 0;
                break;

                case 'e':
                    if(is_dir(files[select].name) == 1) {
                        path_update(file_path, files[select].name);
                        file_update(file_path, files);
                        history_update(save_path, file_path, files);
                        file_show(file_path, files);
                        select = 0;                        
                    }
                break;
            }
            printf("\rselect : %20s", files[select].name);
        }
    }

    return 0;
}