#include <stdio.h>

#include "object/todo.h"

int main() {
  todoList list = list_new();

  list_append(&list, strbuf_from("Something"), strbuf_from("Hello fellas"));
  list_append(&list, strbuf_from("Something"), strbuf_from("Hello fellas"));
  list_append(&list, strbuf_from("Something"), strbuf_from("Hello fellas"));
  list_append(&list, strbuf_from("Something"), strbuf_from("Hello fellas"));

  printf("%ld | %s | %s\n", list.head->index, list.head->title.data,
         list.head->description.data);

  list_remove(&list, 1);

  list_free(&list);

  return 0;
}
