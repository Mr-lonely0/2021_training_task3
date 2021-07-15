/** @file log.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

/**
对log进行初始化，log的“构造函数”
 */

void log_init(log_t *l) {
    l->head = NULL;
}

/**
销毁一个log，释放所有内存空间，log的“析构函数”
 */

void log_destroy(log_t* l) {
    if (l->head == NULL) return;
    node *head = l->head;
    while (head->next != NULL) {
        node *p = head->next;
        head->next = p->next;
        free(p->cmd);
        p->cmd = NULL;
        free(p);
        p = NULL;
    }
    free(head->cmd);
    head->cmd = NULL;
    free(head);
    head = NULL;
}

/**
向log中推入一个字符串，你可以将log视为一个由链表组成的栈
 */

void log_push(log_t* l, const char *item) {
    node *new = (node *)malloc(sizeof(node));
    new->cmd = (char *)malloc(sizeof(char) * 25);
    memset(new->cmd, 0, sizeof(new->cmd));
    new->next = NULL;
    strcpy(new->cmd, item);
    if (l->head == NULL) {
        l->head = (node *)malloc(sizeof(node));
        l->head->cmd = (char *)malloc(sizeof(char) * 25);
        memset(l->head->cmd, 0, sizeof(l->head->cmd));
        l->head->next = new;
    }else {
        node *p = l->head->next;
        while (p->next != NULL) p = p->next;
        new->next = p->next;
        p->next = new;
    }
}


/**
搜索log中是否含有对应前缀的字符串
 */

char *log_search(log_t* l, const char *prefix) {
    if (l->head == NULL) return NULL;
    node *p = l->head->next;
    while (p) {
        if (strstr(p->cmd, prefix)) break;
        else p = p->next;
    }
    if (p) return p->cmd;
    else return NULL;
}
