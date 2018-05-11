#include <loan_server/LoanHandler.h>

#include <loan_server/LoanApplication.h>
#include <loan_server/LoanRepository.h>
#include <loan_server/Ticket.h>

#include <fstream>

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

  std::string approve_loan(std::string parameter) {
    auto const json =Json{mikado::LoanRepository::approve(parameter)};
    return json.dump();
  }

  bool is_approval(http::Request const & request) {
    try {
      return APPROVE == request.parameters.at("action");
    } catch(std::out_of_range const &) {
      return false;
    }
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
    try {
      return FETCH == request.parameters.at("action");
    } catch(std::out_of_range const &) {
      return false;
    }
  }

  bool is_application(http::Request const & request) {
    try {
      return APPLICATION == request.parameters.at("action");
    } catch(std::out_of_range const &) {
      return false;
    }
  }

  std::string fetch_loan_info(std::string ticket_id) {
    auto const json = Json{mikado::LoanRepository::fetch(ticket_id)};
    return json.dump();
  }
}

namespace mikado
{
  http::Response LoanHandler::handle(http::Request request) const {
    http::Response response{};
    response.content_type = "Content-Type: application/json;charset=utf-8";
    response.status_code = 200;

    try {
      if(is_application(request)) {
        LoanApplication application{LoanApplication::new_application()};
        application.amount = amount_from(request);
        application.contact = contact_from(request);
        auto const ticket = LoanRepository::store(application);
        response.response = Json{ticket}.dump();
      } else if(is_status_request(request) && id_specified(request)) {
        response.response = fetch_loan_info(request.parameters.at(TICKET_ID));
      } else if(is_approval(request) && id_specified(request)) {
        response.response = approve_loan(request.parameters.at(TICKET_ID));
      } else {
        Json error = {{"error", "Incorrect parameters provided"}};
        response.response = error.dump();
        response.status_code = 400;
      }
    } catch(std::exception const & e) {
      Json error = {{ "error", "Uh oh! Problem occured: " + std::string{e.what()} }};
      response.response = error.dump();
      response.status_code = 500;
    }

    return response;
  }

  long LoanHandler::get_next_id() {
    std::ifstream read_id(LoanRepository::REPOSITORY_ROOT + "/last.id", std::ios::binary);
    long last_id = 0;
    read_id >> last_id;
    read_id.close();

    long next_id = ++last_id;

    std::ofstream write_id(LoanRepository::REPOSITORY_ROOT + "/last.id", std::ios::binary);
    write_id << next_id;
    write_id.close();

    return next_id;
  }
}
