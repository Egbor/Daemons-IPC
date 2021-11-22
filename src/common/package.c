#include "package.h"
#include "parser.h"
#include "error.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

int string_to_package(struct _package* package, const char* str) {
  int i;
  int status;
  
  char type[256];
  char data[256];

  sscanf(str, "%[^[^:]*]", type); // get type from string
  sscanf(str, "%*[^:]:%[^\n]", data); // get data from string

  // enumerate each parser and parse a data of a specific type
  
  for (i = 0; i < parser_amount; i++) {
    if (strcmp(type, parsers[i].type) == 0) {
      if ((status = parsers[i].parse(package, data))) {
	throw_warning("Incorrect data");
	return status;
      }
      break;
    }
  }

  // throw warning if parser not found
  
  if (i == parser_amount) {
    throw_warning("Incorrect type");
    return -1;
  }

  return 0;
}

int package_to_string(struct _package* package, char* str) {
  int i;
  int status;
  
  time_t current_time = time(NULL);
  struct tm tm = *localtime(&current_time);

  char parsed_struct[256];

  // enumerate each parser and parse a package of a specific type
  
  for (i = 0; i < parser_amount; i++) {
    if (parsers[i].id == package->id) {
      if ((status = parsers[i].parse_package(package, parsed_struct))) {
	throw_warning("Incorrect data");
	return status;
      }
      break;
    }
  }

  // throw warning if parser not found
  
  if (i == parser_amount) {
    throw_warning("Incorrect type");
    return -1;
  }

  // create a string of a specific type (<date>:<data>)
  
  sprintf(str, "%02d/%02d/%04d %02d:%02d:%02d:%s",
	  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
	  tm.tm_hour, tm.tm_min, tm.tm_sec, parsed_struct);

  return 0;
}
