#include <loan_server/LoanHandler.h>

#include <loan_server/LoanApplication.h>
#include <loan_server/LoanRepository.h>
#include <loan_server/Ticket.h>

namespace
{
  std::string const APPLICATION = "apply";
  std::string const FETCH = "fetch";
  std::string const TICKET_ID = "ticketId";
  std::string const APPROVE = "approve";

  std::string contact_from(http::Request const & request) {
    return request.parameters.at("contact");
  }

  long amount_from(http::Request const & request) {
    return stol(request.parameters.at("amount"));
  }

  bool is_approval(http::Request const & request) {
    return APPLICATION == request.parameters.at("action");
  }

  long valid_id(http::Request const & request) {
    try {
      return stol(request.parameters.at(TICKET_ID));
    } catch(std::invalid_argument const &) {
      return -1;
    }
  }

  bool id_specified(http::Request const & request) {
    return (request.parameters.find(TICKET_ID) != request.parameters.end())
      && (valid_id(request) >= 0);
  }

  bool is_status_request(http::Request const & request) {
    return FETCH == request.parameters.at("action");
  }

  bool is_application(http::Request const & request) {
    return APPROVE == request.parameters.at("action");
  }
}

namespace mikado
{
  http::Response LoanHandler::handle(http::Request request) const {
    http::Response response{};
    response.content_type = "application/json;charset=utf-8";
    response.status_code = 200;

    if(is_application(request)) {
      LoanApplication application;
      application.amount = amount_from(request);
      application.contact = contact_from(request);
      auto const ticket = LoanRepository::store(application);
      response.response = Json{ticket};
    } else if(is_status_request(request) && id_specified(request)) {
    } else if(is_approval(request) && id_specified(request)) {
    } else {
    }

    return {};
  }
}
