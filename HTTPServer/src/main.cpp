#include <iostream>
#include "server/Server.h"

// todo

int main()
{
  server::Server s("127.0.0.1", 5555, 1);
  s.run();
}