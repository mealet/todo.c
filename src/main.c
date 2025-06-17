#include <stdio.h>

#include "../lib/fort.h"
#include "object/todo.h"
#include "storage/storage.h"

#define STORAGE_PATH "todo"

int main(int argc, char *argv[]) {
  todoList list = list_new();
  if (storage_load(&list, STORAGE_PATH)) {
    fprintf(stderr, "No TODO file found, creating new...\n");
    storage_save(&list, STORAGE_PATH);
  }

  ft_table_t *table = ft_create_table();
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_write_ln(table, " ", "Title", "Description", "Checked");

  if (list.len == 0) {
    list_append(&list, strbuf_from("Nothing"), strbuf_from("No items here"));
  }

  for (size_t i = 0; i < list.len; i++) {
    todoObject *ptr = list_get(&list, i);

    char index[3];
    sprintf(index, "%ld", ptr->index);

    ft_write_ln(table, index, strbuf_get(&ptr->title),
                strbuf_get(&ptr->description), ptr->checked ? "✅" : "❌");
  }

  list_pop(&list);
  printf("%s\n", ft_to_string(table));

  ft_destroy_table(table);
  list_free(&list);

  return 0;
}
