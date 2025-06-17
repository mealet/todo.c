#include <stdio.h>
#include <stdlib.h>

#include "todo.h"

void todo_panic(char *message) {
  printf("RUNTIME PANIC FROM `todo`\n");
  printf("%s\n", message);
  exit(1);
}

// Object

void object_cleanup(todoObject *object) {
  if (object) {
    strbuf_free(&object->title);
    strbuf_free(&object->description);
  }
}

// List

todoList list_new() {
  todoObject *ptr = malloc(sizeof(todoObject));

  return (todoList){.len = 0, .head = ptr, .latest = ptr};
}

void list_append(todoList *list, strBuffer title, strBuffer description) {
  list->latest->index = list->len;
  list->latest->title = title;
  list->latest->description = description;
  list->latest->checked = false;

  list->len += 1;

  todoObject *ptr = malloc(sizeof(todoObject));
  ptr->previous = list->latest;

  list->latest->next = ptr;
  list->latest = ptr;
}

void list_pop(todoList *list) {
  if (list->len == 0)
    return;

  if (list->len == 1) {
    object_cleanup(list->head);
  } else {
    todoObject *slot = list->latest;
    todoObject *clearable = slot->previous;
    todoObject *newLatest = clearable->previous;

    newLatest->next = slot;

    object_cleanup(clearable);
    free(clearable);
  }

  list->len -= 1;
}
void list_remove(todoList *list, size_t position) {
  if (list->len == 0) {
    todo_panic("Attempted to remove an item from empty list");
  }

  if ((position - 1 == list->len)) {
    return list_pop(list);
  }

  if (position >= list->len) {
    printf("RUNTIME PANIC FROM `todo`\n");
    printf("Attempted to remove position %ld, but list length is %ld\n",
           position, list->len);
    exit(1);
  }

  todoObject *pointer;
  if ((list->len - position) < position) {
    pointer = list->latest;

    while (pointer->index != position) {
      pointer = pointer->previous;
    }
  } else {
    pointer = list->head;

    while (pointer->index != position) {
      pointer = pointer->next;
    }
  }

  todoObject *lhs = pointer->previous;
  todoObject *rhs = pointer->next;
  size_t index = pointer->index;

  lhs->next = rhs;
  rhs->previous = lhs;

  object_cleanup(pointer);
  free(pointer);

  pointer = lhs;

  while (pointer) {
    pointer->index = index;
    index += 1;

    pointer = pointer->next;
  }

  list->len -= 1;
}

todoObject *list_get(todoList *list, size_t position) {
  if (position >= list->len) {
    printf("RUNTIME PANIC FROM `todo`\n");
    printf("Attempted to edit position %ld, but list length is %ld\n", position,
           list->len);
    exit(1);
  }

  todoObject *pointer;
  if ((list->len - position) < position) {
    pointer = list->latest;

    while (pointer->index != position) {
      pointer = pointer->previous;
    }
  } else {
    pointer = list->head;

    while (pointer->index != position) {
      pointer = pointer->next;
    }
  }

  return pointer;
}

void list_setTitle(todoList *list, size_t position, strBuffer value) {
  if (position >= list->len) {
    printf("RUNTIME PANIC FROM `todo`\n");
    printf("Attempted to edit position %ld, but list length is %ld\n", position,
           list->len);
    exit(1);
  }

  todoObject *pointer;
  if ((list->len - position) < position) {
    pointer = list->latest;

    while (pointer->index != position) {
      pointer = pointer->previous;
    }
  } else {
    pointer = list->head;

    while (pointer->index != position) {
      pointer = pointer->next;
    }
  }

  strbuf_free(&pointer->title);
  pointer->title = value;
}
void list_setDescription(todoList *list, size_t position, strBuffer value) {
  if (position >= list->len) {
    printf("RUNTIME PANIC FROM `todo`\n");
    printf("Attempted to edit position %ld, but list length is %ld\n", position,
           list->len);
    exit(1);
  }

  todoObject *pointer;
  if ((list->len - position) < position) {
    pointer = list->latest;

    while (pointer->index != position) {
      pointer = pointer->previous;
    }
  } else {
    pointer = list->head;

    while (pointer->index != position) {
      pointer = pointer->next;
    }
  }

  strbuf_free(&pointer->description);
  pointer->description = value;
}
void list_setChecked(todoList *list, size_t position, bool value) {
  if (position >= list->len) {
    printf("RUNTIME PANIC FROM `todo`\n");
    printf("Attempted to edit position %ld, but list length is %ld\n", position,
           list->len);
    exit(1);
  }

  todoObject *pointer;
  if ((list->len - position) < position) {
    pointer = list->latest;

    while (pointer->index != position) {
      pointer = pointer->previous;
    }
  } else {
    pointer = list->head;

    while (pointer->index != position) {
      pointer = pointer->next;
    }
  }

  pointer->checked = value;
}

void list_free(todoList *list) {
  if (list->len == 0) {
    free(list->head);
    return;
  }
  printf("%ld\n", list->len);

  list->len = 0;
  todoObject *ptr = list->head;

  while ((ptr) && (ptr->title.data)) {
    object_cleanup(ptr);
    todoObject *dealloc_ptr = ptr;

    ptr = ptr->next;
    free(dealloc_ptr);
  }
}
