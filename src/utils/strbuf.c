#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strbuf.h"

void strbuf_panic(char *message) {
  printf("RUNTIME PANIC FROM `strbuf`\n");
  printf("%s\n", message);
  exit(1);
}

// initialization
strBuffer strbuf_new() {
  char *ptr = malloc(sizeof(char));

  return (strBuffer){.data = ptr, .len = 0, .capacity = 1};
}

strBuffer strbuf_from(char *input) {
  size_t len = strlen(input);
  size_t capacity = sizeof(char) * len;
  char *ptr = malloc(capacity);

  strcpy(ptr, input);

  return (strBuffer){.data = ptr, .len = len, .capacity = capacity};
}

// modifying and clearing
void strbuf_free(strBuffer *buffer) {
  if ((buffer) && (buffer->data) && (buffer->capacity > 0)) {
    free(buffer->data);
    buffer->capacity = 0;
    buffer->len = 0;
  } else {
    strbuf_panic("Attempted to free deallocated string buffer");
  }
}
void strbuf_push(strBuffer *buffer, char chr) {
  if (buffer->capacity < 1) {
    strbuf_panic("Attempted to push to deallocated string buffer");
  }

  buffer->len += 1;

  if (buffer->len > buffer->capacity) {
    buffer->capacity = buffer->len;

    char *ptr = realloc(buffer->data, sizeof(char) * buffer->capacity);

    if (!ptr) {
      strbuf_panic("Unable to reallocate string buffer (out of memory)");

      free(buffer->data);
      buffer->capacity = 0;
      buffer->len = 0;
    }

    buffer->data = ptr;
  }

  buffer->data[buffer->len - 1] = chr;
}
void strbuf_set(strBuffer *buffer, char *input) {
  if (buffer->capacity < 1) {
    strbuf_panic("Attempted to set deallocated string buffer");
  }

  buffer->len = strlen(input);

  if (buffer->len > buffer->capacity) {
    buffer->capacity = buffer->len;

    char *ptr = realloc(buffer->data, sizeof(char) * buffer->capacity);

    if (!ptr) {
      strbuf_panic("Unable to reallocate string buffer (out of memory)");

      free(buffer->data);
      buffer->capacity = 0;
      buffer->len = 0;
    }

    buffer->data = ptr;
  }

  strcpy(buffer->data, input);
}

char strbuf_getc(strBuffer *buffer, size_t position) {
  if (position >= buffer->len) {
    printf("RUNTIME PANIC FROM `strbuf`\n");
    printf("Attempted to get character %ld, but buffer len is %ld\n", position,
           buffer->len);
    exit(1);
  }

  return buffer->data[position];
}
char *strbuf_get(strBuffer *buffer) {
  if (buffer->capacity < 1) {
    strbuf_panic("Attempted to access deallocated buffer");
  }

  return buffer->data;
}
