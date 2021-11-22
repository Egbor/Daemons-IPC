#ifndef _CLIENT_HANDLER_H_
#define _CLIENT_HANDLER_H_

#include <stddef.h>

extern void handler_file(void* args);
extern int scan_message(char* message, size_t size);

#endif
