#include <loan_server/Server.h>
#include <loan_server/LoanHandler.h>

int main() {
  mikado::LoanHandler handler;
  mikado::Server server(handler);
}

