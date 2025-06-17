#include <stdio.h>

#include "object/todo.h"

int main() {
  todoList list = list_new();

  list_append(&list, strbuf_from("Something"), strbuf_from("Hello fellas"));
  list_append(&list, strbuf_from("Aasd"), strbuf_from("Hello"));

  list_setChecked(&list, 0, true);
  list_setTitle(&list, 1, strbuf_from("Say hello"));

  for (size_t i = 0; i < list.len; i++) {
    todoObject *ptr = list_get(&list, i);

    printf("%ld | %s | %s | %s\n", ptr->index, strbuf_get(&ptr->title),
           strbuf_get(&ptr->description), ptr->checked ? "✅" : "❌");
  }

  list_free(&list);

  return 0;
}
