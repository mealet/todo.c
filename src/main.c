#include <stdio.h>
#include <string.h>

#include "../lib/fort.h"
#include "object/todo.h"
#include "storage/storage.h"

#define STORAGE_PATH "todo.list"

int main(int argc, char *argv[]) {
  // loading todo list

  todoList list = list_new();
  if (storage_load(&list, STORAGE_PATH)) {
    printf("No TODO file found, creating new...\n");
    printf("Provide `help` CLI argument to see help\n");
    storage_save(&list, STORAGE_PATH);
  }

  // handling CLI arguments

  if (argc > 1) {
    if (!strcmp(argv[1], "add")) {
      if (argc < 4) {
        fprintf(stderr, "Not enough arguments for addition\n");
        exit(1);
      }

      strBuffer title = strbuf_from(argv[2]);
      strBuffer description = strbuf_from(argv[3]);

      list_append(&list, title, description);
    } else if (!strcmp(argv[1], "set")) {
      if (argc < 5) {
        fprintf(stderr, "Not enough arguments for editing\n");
        exit(1);
      }

      size_t index = strtol(argv[2], NULL, 10);
      if (index == 0) {
        fprintf(stderr, "Index 0 isn't avaible (use 1 instead)");
        exit(1);
      }

      index--;

      strBuffer title = strbuf_from(argv[3]);
      strBuffer description = strbuf_from(argv[4]);

      list_setTitle(&list, index, title);
      list_setDescription(&list, index, description);
    } else if (!strcmp(argv[1], "remove")) {
      if (argc < 3) {
        fprintf(stderr, "Not enough arguments for removal\n");
        exit(1);
      }

      size_t index = strtol(argv[2], NULL, 10);
      if (index == 0) {
        fprintf(stderr, "Index 0 isn't avaible (use 1 instead)");
        exit(1);
      }

      index--;
      list_remove(&list, index);
    } else if (!strcmp(argv[1], "check")) {
      if (argc < 3) {
        fprintf(stderr, "Not enough arguments for removal\n");
        exit(1);
      }

      size_t index = strtol(argv[2], NULL, 10);
      if (index == 0) {
        fprintf(stderr, "Index 0 isn't avaible (use 1 instead)");
        exit(1);
      }

      index--;
      list_check(&list, index);
    } else if (!strcmp(argv[1], "help")) {
      printf("CLI Arguments:\n");
      printf("- add [TITLE] [DESCRIPTION]\n");
      printf("- set [INDEX] [TITLE] [DESCRIPTION]\n");
      printf("- remove [INDEX]\n");
      printf("- check [INDEX]\n");
      printf("- help\n\n");
    }
  }

  // creating table

  ft_table_t *table = ft_create_table();
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_write_ln(table, " ", "Title", "Description", "Checked");

  bool empty = false;
  if (list.len == 0) {
    empty = true;
    list_append(&list, strbuf_from("Nothing"), strbuf_from("No items here"));
  }

  for (size_t i = 0; i < list.len; i++) {
    todoObject *ptr = list_get(&list, i);

    char index[3];
    size_t ptr_index = empty ? ptr->index : ptr->index + 1;
    sprintf(index, "%ld", ptr_index);

    ft_write_ln(table, index, strbuf_get(&ptr->title),
                strbuf_get(&ptr->description), ptr->checked ? "✅" : "❌");
  }

  if (empty) {
    list_pop(&list);
  }

  // displaying

  printf("%s\n", ft_to_string(table));

  // saving table

  storage_save(&list, STORAGE_PATH);

  // clearing up

  ft_destroy_table(table);
  list_free(&list);

  return 0;
}
