#include <loan_server/IHandler.h>

namespace mikado
{
  class LoanHandler : public http::IHandler {
    public:
      virtual http::Response handle(http::Request request) const;

      static long get_next_id();
  };
}
