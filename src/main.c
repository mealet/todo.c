#include <stdio.h>

#include "object/todo.h"
#include "storage/storage.h"

#define STORAGE_PATH "todo"

int main() {
  todoList list = list_new();
  storage_load(&list, STORAGE_PATH);

  for (size_t i = 0; i < list.len; i++) {
    todoObject *ptr = list_get(&list, i);

    printf("%ld | %s | %s | %s\n", ptr->index, strbuf_get(&ptr->title),
           strbuf_get(&ptr->description), ptr->checked ? "✅" : "❌");
  }

  // int res = storage_save(&list, STORAGE_PATH);
  // printf("Result is: %d\n", res);

  list_free(&list);

  return 0;
}
