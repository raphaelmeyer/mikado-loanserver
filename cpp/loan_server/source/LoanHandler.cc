#include <loan_server/LoanHandler.h>

#include <loan_server/LoanApplication.h>
#include <loan_server/LoanRepository.h>
#include <loan_server/Ticket.h>

namespace
{
  std::string const APPLICATION = "apply";

  std::string contact_from(mikado::Request const & request) {
    return request.parameters.at("contact");
  }

  long amount_from(mikado::Request const & request) {
    return stol(request.parameters.at("amount"));
  }

  bool is_application(mikado::Request const & request) {
    return APPLICATION == request.parameters.at("action");
  }
}

namespace mikado
{
    Response LoanHandler::handle(Request request) const {
      Response response{};
      response.content_type = "";
      response.status_code = 200;

      if (is_application(request)) {
        LoanApplication application;
        application.amount = amount_from(request);
        application.contact = contact_from(request);
        auto const ticket = LoanRepository::store(application);
        response.response = Json{ticket}; // .dump() ?
      } else {
      }

      return {};
    }
}
