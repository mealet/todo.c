#ifndef TODO_OBJECT_TODO_H_
#define TODO_OBJECT_TODO_H_

#include "../utils/strbuf.h"

#include <stdbool.h>
#include <stddef.h>

// Todo Object

typedef struct TodoObject {
  size_t index;
  struct TodoObject *next;
  struct TodoObject *previous;

  strBuffer title;
  strBuffer description;
  bool checked;
} todoObject;

// Todo List
typedef struct TodoList {
  size_t len;

  todoObject *head;
  todoObject *latest;
} todoList;

todoList list_new();

void list_append(todoList *list, strBuffer title, strBuffer description);
void list_pop(todoList *list);
void list_remove(todoList *list, size_t position);

todoObject *list_get(todoList *list, size_t position);

void list_setTitle(todoList *list, size_t position, strBuffer value);
void list_setDescription(todoList *list, size_t position, strBuffer value);
void list_setChecked(todoList *list, size_t position, bool value);

void list_free(todoList *list);

#endif
