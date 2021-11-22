#ifndef _SERVER_HANDLER_H_
#define _SERVER_HANDLER_H

#include <stddef.h>

extern void handler_deamon(void* args);
extern void handler_int(void* args);
extern void handler_array(void* args);
extern void handler_struct(void* args);

extern void open_files();
extern void close_files();

extern int print_message(int type, char* message);

#endif
