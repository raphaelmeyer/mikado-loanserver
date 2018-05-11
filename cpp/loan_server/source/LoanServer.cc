#include <loan_server/Server.h>
#include <loan_server/LoanHandler.h>

#include <iostream>

int main() {
  mikado::LoanHandler handler;
  http::Server server(handler, 8080);
  server.start();

  std::cout << "Press ctrl+d to exit.\n";

  while(! std::cin.eof()) {
    char _;
    std::cin >> _;
  }

  server.stop();
}

