#ifndef TODO_STORAGE_STORAGE_H_
#define TODO_STORAGE_STORAGE_H_

#include "../object/todo.h"

// I'm not gonna create some kind of binary format for this task.
// I'll just implement writing objects with separated by 0x0 byte and new line
// between objects

int storage_save(todoList *list, char *path);
int storage_load(todoList *ptr, char *path);

#endif
