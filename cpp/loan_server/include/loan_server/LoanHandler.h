#include <loan_server/IHandler.h>

namespace mikado
{
  class LoanHandler : public http::IHandler {
    virtual http::Response handle(http::Request request) const;
  };
}
