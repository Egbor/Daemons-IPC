#include <basename.h>

#include "server.h"

int main(int argc, char* argv[]) {  
  set_basename(argv[0]);
  setup_server(argc, argv);
  start_server();
  return 0;
}
