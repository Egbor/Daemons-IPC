#ifndef _PARSER_H_
#define _PARSER_H_

#include "package.h"

#include <stddef.h>

struct _parser {
  enum message_id id;
  char type[10];
  int(*parse)(struct _package* package, const char* data);
  int(*parse_package)(const struct _package* package, char* data);
};

extern const int parser_amount;
extern struct _parser parsers[];

#endif
