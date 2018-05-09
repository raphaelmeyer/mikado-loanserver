#include <loan_server/Server.h>
#include <loan_server/LoanHandler.h>

int main() {
  mikado::LoanHandler handler;
  http::Server server(handler, 8080);
  server.start();
}

