#ifndef _MSG_QUEUE_H_
#define _MSG_QUEUE_H_

#include <stddef.h>

extern int create_queue(const char* filename, int proj_id);
extern int connect_queue(const char* filename, int proj_id);

extern int send_to_queue(int id, const void* buffer, size_t size);
extern int receive_from_queue(int id, void* buffer, size_t size);

extern void destroy_queue(int id);

#endif
