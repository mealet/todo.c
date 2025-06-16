#ifndef TODO_UTILS_STRBUF_H_
#define TODO_UTILS_STRBUF_H_

#include <stddef.h>

typedef struct {
  char *data;

  size_t len;
  size_t capacity;
} strBuffer;

strBuffer strbuf_new();
strBuffer strbuf_from(char *input);

void strbuf_free(strBuffer *buffer);
void strbuf_push(strBuffer *buffer, char chr);
void strbuf_set(strBuffer *buffer, char *input);

char strbuf_getc(strBuffer *buffer, size_t position);
char *strbuf_get(strBuffer *buffer);

#endif
