#include "parser.h"

#include <errno.h>
#include <stdio.h>

int parse_int(struct _package* package, const char* data) {
  int value = 0;

  errno = 0;
  if (sscanf(data, "%d", &value) < 1) {
    return -1;
  }
  
  package->id = INT;
  package->data.val = value;

  return 0;
}

int parse_array(struct _package* package, const char* data) {
  char array[5] = { 0 };

  errno = 0;
  if (sscanf(data, "%c %c %c %c %c", &array[0], &array[1], &array[2], &array[3], &array[4]) < 5) {
    return -1;
  }
  
  package->id = ARRAY;
  package->data.arr[0] = array[0];
  package->data.arr[1] = array[1];
  package->data.arr[2] = array[2];
  package->data.arr[3] = array[3];
  package->data.arr[4] = array[4];

  return 0;
}

int parse_struct(struct _package* package, const char* data) {
  int a = 0, b = 0, c = 0;

  errno = 0;
  if (sscanf(data, "%d %d %d", &a, &b, &c) < 3) {
    return -1;
  }
  
  package->id = STRUCT;
  package->data.str.a = a;
  package->data.str.b = b;
  package->data.str.c = c;

  return 0;
}

int parse_package_int(const struct _package* package, char* data) {
  errno = 0;
  if (sprintf(data, "%d", package->data.val) == 0) {
    return -1;
  }

  return 0;
}

int parse_package_array(const struct _package* package, char* data) {
  if (sprintf(data, "%c %c %c %c %c", package->data.arr[0], package->data.arr[1],
	      package->data.arr[2], package->data.arr[3], package->data.arr[4]) == 0) {
    return -1;
  }

  return 0;
}

int parse_package_struct(const struct _package* package, char* data) {
  errno = 0;
  if (sprintf(data, "%d %d %d", package->data.str.a, package->data.str.b, package->data.str.c) == 0) {
    return -1;
  }

  return 0;
}

// array with all existed paresers
// the array can be extended

const int parser_amount = 3;
struct _parser parsers[] = { { INT, "int", parse_int, parse_package_int },
			     { ARRAY, "array", parse_array, parse_package_array },
			     { STRUCT, "struct", parse_struct, parse_package_struct }
};
