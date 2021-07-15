#include "shell.h"
#include <unistd.h>
/**
 * shell的入口
 */
void prefix() {
    char cwd[100];
    getcwd(cwd, sizeof(cwd));
    printf("%s$ ", cwd);
}

int execute(char* buffer) {
    if (strstr(buffer, "cd ")) {
        char *path = buffer + 3;
        if (chdir(path)) printf("%s: No such file or directory\n", path);
    } else if (!strcmp(buffer, "exit")) {
        return 0;
    } else if (!strcmp(buffer, "!#")) {
        node *p = Log.head;
        if (p) {
            p = p->next;
            while (p) {
                puts(p->cmd);
                p = p->next;
            }
        }
    } else if (strstr(buffer, "!")) {
        char *pre = log_search(&Log, buffer + 1);
        if (pre) execute(pre);
        else puts("No Match");
    } else if (!strcmp(buffer, "ls")) {
        system(buffer);
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            int space = 0;
            for (int i = 0; i < strlen(buffer); i++) {
                if (buffer[i] == ' ') space++;
            }
            char **strs = (char **)malloc(sizeof(char *) * (space + 2));
            for (int i = 0; i < (space + 2); i++) {
                strs[i] = (char *)malloc(sizeof(char) * 20);
                memset(strs[i], 0, sizeof(strs[i]));
            }
            strs[space + 1] = NULL;
            char *p;
            int cnt = 0;
            p = strtok(buffer, " ");
            strcpy(strs[cnt++], p);
            while (p) {
                p = strtok(NULL, " ");
                if (p) strcpy(strs[cnt++], p);
            }
            //for (int i = 0; i < cnt; i++) puts(strs[i]);
            char *tmp = (char *)malloc(sizeof(char) * 100);
            strcpy(tmp, "./");
            strcat(tmp, strs[0]);
            if (execvp(tmp, strs) == -1) {
                printf("%s: no such command\n", strs[0]);
            }
            free(tmp);
            tmp = NULL;
            for (int i = 0; i < 10; i++) {
                free(strs[i]);
                strs[i] = NULL;
            }
            free(strs);
            strs = NULL;
            exit(0);
        } else {
            wait(NULL);
        }
    }
    if (buffer[0] != '!') {
        log_push(&Log, buffer);
    }
    return 1;
}
