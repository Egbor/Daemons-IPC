#include "serverhandler.h"

#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

char int_filename[256] = "int.txt";
char array_filename[256] = "array.txt";
char struct_filename[256] = "struct.txt";

void handler_deamon(void* args) {
  pid_t pid = fork();

  if (pid == -1) {
    throw_error("The error was caused while creating a demon", -1);
  }

  if (pid == 0) {
    umask(0); // allow to set all the bits of the rights to craeted files 
    setsid(); // unbind the process from the current parent 

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
  } else {
    FILE* pid_file = fopen("/tmp/serverpid", "w");
    fprintf(pid_file, "%d\n", pid);
    fclose(pid_file);
    
    throw_warning("Demon was created");
    exit(0);
  }
}

void handler_int(void* args) {
  strcpy(int_filename, args);
}

void handler_array(void* args) {
  strcpy(array_filename, args);
}

void handler_struct(void* args) {
  strcpy(struct_filename, args);
}

int print_message(int type, char* message) {
  switch (type) {
  case 0: {
    FILE* int_file = fopen(int_filename, "a+");
    fprintf(int_file, "%s\n", message);
    fclose(int_file);
    break;
  }
  case 1: {
    FILE* array_file = fopen(array_filename, "a+");
    fprintf(array_file, "%s\n", message);
    fclose(array_file);
    break;
  }
  case 2: {
    FILE* struct_file = fopen(struct_filename, "a+");
    fprintf(struct_file, "%s\n", message);
    fclose(struct_file);
    break;
  }
  }
}
