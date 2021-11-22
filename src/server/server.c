#include "server.h"
#include "serverhandler.h"

#include <sign.h>
#include <error.h>
#include <cmdopt.h>
#include <package.h>
#include <msgqueue.h>

int terminate_status = 0; // the flag indicates the process termination

void terminate_server(int sig) {
  terminate_status = 1; // set terminate_status on terminate
}

void setup_server(int argc, char* argv[]) {
  int signals[] = { SIGINT, SIGTERM }; // signals for redefine
  options_t* options = create_options(); // the structure keeps all options of the process
  
  add_option(options, 'D', handler_daemon); // the option to set the program into deamon mode
  add_option(options, 'i', handler_int); // the option to set filename for integer values
  add_option(options, 'a', handler_array); // the option to set filename for arrays of characters
  add_option(options, 's', handler_struct); // the option to set filename for structure

  handle_options(options, argc, argv, "Di:a:s:"); // parse and handle command line arguments
  set_signal(signals, 2, terminate_server); // redefine signals of the process
  
  free_options(options);
}

void start_server() {
  char result[256];
  
  struct _package package;
  
  int id = create_queue("/tmp", 'A');
  while(!terminate_status) {
    if (receive_from_queue(id, &package, sizeof(struct _package)) > 0) {
      if (package_to_string(&package, result) == 0) { // translate received package to a string in a specific format (<date>:<data>)
	print_message(package.id, result);
      }
    }
  }
  destroy_queue(id);
}
