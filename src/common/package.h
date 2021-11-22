#ifndef _PACKAGE_H_
#define _PACKAGE_H_

enum message_id { INT, ARRAY, STRUCT };

struct _package {
  enum message_id id;
  union _data {
    int val;
    char arr[5];
    struct _struct {
      int a;
      int b;
      int c;
    } str;
  } data;
};

extern int string_to_package(struct _package* package, const char* str);
extern int package_to_string(struct _package* package, char* str);

#endif
