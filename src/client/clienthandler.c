#include "clienthandler.h"

#include <signal.h>
#include <stdio.h>
#include <string.h>

FILE* in_stream = NULL;

void handler_file(void* args) {
  in_stream = fopen(args, "r");
}

int scan_message(char* message, size_t size) {
  if (in_stream) {
    fgets(message, size, in_stream);
    if (feof(in_stream)) {
      kill(0, SIGTERM);
      fclose(in_stream);
      return -1;
    }
  } else {
    char type[100];
    char data[100];

    printf("Type: ");
    scanf("%s", type);
    printf("Data: ");
    scanf("%c", data);
    scanf("%[^\n]", data);

    strcat(type, ":");
    strcat(type, data);

    strcpy(message, type);
  }

  return 0;
}


