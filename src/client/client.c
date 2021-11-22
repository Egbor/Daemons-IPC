#include "client.h"
#include "clienthandler.h"

#include <stdio.h>
#include <string.h>

#include <sign.h>
#include <cmdopt.h>
#include <package.h>
#include <msgqueue.h>

int terminate_status = 0; // the flag indicates the process termination

void terminate_client(int sig) {
  terminate_status = 1; // set terminate_status on terminate
}

void setup_client(int argc, char* argv[]) {
  int signals[] = { SIGINT, SIGTERM }; // signals for redefine
  options_t* options = create_options(); // the structure keeps all options of the process
  
  add_option(options, 'f', handler_file); // the option to set the program into file input mode

  handle_options(options, argc, argv, "f:"); // parse and handle command line arguments
  set_signal(signals, 2, terminate_client); // redefine signals of the process
  
  free_options(options);
}

void start_client() {
  char message[256];
  
  struct _package package;
  
  int id = connect_queue("/tmp", 'A');
  while(!terminate_status) {
    if (scan_message(message, 256) == 0) {
      if (string_to_package(&package, message) == 0) { // translate an input message in a specific format (<type>:<data>)
	send_to_queue(id, &package, sizeof(struct _package));
      }
    }
  }
}
