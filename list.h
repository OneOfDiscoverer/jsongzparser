#ifndef _LIST_H
#define _LIST_H

#define COMMAND_INS book bk

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define STR_SIZE        1024

struct book 
{
    char *str;
}typedef book;

struct list
{
    void *ptr;
    COMMAND_INS;
}typedef list;

static list* head = 0;

#ifdef _TEST_LIST
list* getHead(void);
#endif

list* getAt(int id);
void pushBack(void *ptr);
int remove_at(int num);
#endif