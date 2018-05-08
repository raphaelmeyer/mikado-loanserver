#include <loan_server/IHandler.h>

namespace mikado
{
  class LoanHandler : public IHandler {
    virtual Response handle(Request request) const;
  };
}
