/** @file log.c */
#include <stdlib.h>
#include <string.h>
#include "log.h"

/**
对log进行初始化，log的“构造函数”
 */

void log_init(log_t *l) {

}

/**
销毁一个log，释放所有内存空间，log的“析构函数”
 */

void log_destroy(log_t* l) {

}

/**
向log中推入一个字符串，你可以将log视为一个由链表组成的栈
 */

void log_push(log_t* l, const char *item) {

}


/**
搜索log中是否含有对应前缀的字符串
 */

char *log_search(log_t* l, const char *prefix) {
    
}
