#include "msgqueue.h"
#include "error.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int create_queue(const char* filename, int proj_id) {
  key_t key = 0;
  int msgid = 0;
  
  if ((key = ftok(filename, proj_id)) < 0) { // create an IPC token
    throw_error("IPC token creation failed.", -1);
  }

  if ((msgid = msgget(key, 0666 | IPC_CREAT)) < 0) { // create a new message queue
    throw_error("IPC message queue creation faild", -1);
  }

  return msgid;
}

int connect_queue(const char* filename, int proj_id) {
  key_t key = 0;
  int msgid = 0;

  if ((key = ftok(filename, proj_id)) < 0) { // create an IPC token
    throw_error("IPC token creation failed.", -1);
  }

  if ((msgid = msgget(key, 0)) < 0) { // connect to an existed message queue
    throw_error("IPC message queue connection failed", -1);
  }

  return msgid;
}

int send_to_queue(int id, const void* buffer, size_t size) {
  int status = 0;

  if ((status = msgsnd(id, buffer, size, 0)) != 0) {
    throw_warning("Send failed.");
  }

  return status;
}

int receive_from_queue(int id, void* buffer, size_t size) {
  int status = 0;

  if ((status = msgrcv(id, buffer, size, 0, 0)) < 0) {
    throw_warning("Receive failed.");
  }

  return status;
}

void destroy_queue(int id) {
  if (msgctl(id, IPC_RMID, 0) < 0) { // destroy an existed message queue
    throw_warning("IPC message queue distruction failed");
  } 
}
