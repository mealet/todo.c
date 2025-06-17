#include <stdio.h>
#include <stdlib.h>

#include "storage.h"

int storage_save(todoList *list, char *path) {
  // clearing file
  {
    FILE *stream = fopen(path, "w");
    fclose(stream);
  }

  FILE *stream = fopen(path, "a");
  if (!stream) {
    return 1;
  }

  for (size_t i = 0; i < list->len; i++) {
    todoObject *obj = list_get(list, i);

    fprintf(stream, "%s..%s..%d\n", strbuf_get(&obj->title),
            strbuf_get(&obj->description), obj->checked);
  }

  fclose(stream);
  return 0;
}

int storage_load(todoList *ptr, char *path) {
  FILE *stream = fopen(path, "r");

  if (!stream) {
    return 1;
  }

  while (!feof(stream)) {
    strBuffer title = strbuf_new();
    strBuffer description = strbuf_new();
    bool checked = false;

    int current = fgetc(stream);

    if (current == -1) {
      break;
    }

    while (!feof(stream)) {
      if (current == '.' && fgetc(stream) == '.') {
        current = fgetc(stream);
        break;
      }

      strbuf_push(&title, current);
      current = fgetc(stream);
    }

    while (!feof(stream)) {
      if (current == '.' && fgetc(stream) == '.') {
        current = fgetc(stream);
        break;
      }

      strbuf_push(&description, current);
      current = fgetc(stream);
    }

    if (current == '1')
      checked = true;

    current = fgetc(stream);

    list_append(ptr, title, description);
    list_setChecked(ptr, ptr->len - 1, checked);
  }

  fclose(stream);
  return 0;
}
