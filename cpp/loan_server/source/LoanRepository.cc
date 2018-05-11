#include <loan_server/LoanRepository.h>

#include <loan_server/LoanApplication.h>
#include <loan_server/Ticket.h>

#include <fstream>

namespace mikado
{
  namespace
  {
    static std::string const FILE_EXTENSION = ".loan";

    std::string file_from_application(long application_no) {
      return LoanRepository::REPOSITORY_ROOT + "/"
          + std::to_string(application_no)
          + FILE_EXTENSION;
    }
  }

  std::string const LoanRepository::REPOSITORY_ROOT = ".";

  LoanApplication LoanRepository::fetch(std::string ticket_id) {
    return fetch(stol(ticket_id));
  }

  LoanApplication LoanRepository::fetch(long ticket_id) {
    std::ifstream file{file_from_application(ticket_id)};
    Json json;
    file >> json;
    LoanApplication application = json;
    return application;
  }

  Ticket LoanRepository::store(LoanApplication const & application) {
    std::ofstream file{file_from_application(application.application_no)};
    file << Json(application);
    return Ticket{application.application_no};
  }

  Ticket LoanRepository::approve(std::string ticket_id) {
    auto application = fetch(ticket_id);
    application.approved = true;
    store(application);
    return Ticket{application.application_no};
  }
}

