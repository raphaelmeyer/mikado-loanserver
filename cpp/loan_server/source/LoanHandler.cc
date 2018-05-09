#include <loan_server/LoanHandler.h>

namespace
{
  bool is_application(mikado::Request const & request) {
    return false;
  }
}

namespace mikado
{
    Response LoanHandler::handle(Request request) const {
      Response response{};
      response.content_type = "";
      response.status_code = 200;

      if (is_application(request)) {
      } else {
      }

      return {};
    }
}
