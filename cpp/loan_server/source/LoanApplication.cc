#include <loan_server/LoanApplication.h>

namespace mikado
{
  void to_json(Json & json, LoanApplication const & application) {
    json = Json{
      {"application_no", application.application_no},
      {"amount", application.amount},
      {"contact", application.contact},
      {"approved", application.approved}
    };
  }

  void from_json(Json const & json, LoanApplication & application) {
    application.application_no = json.at("application_no").get<long>();
    application.amount = json.at("amount").get<long>();
    application.contact = json.at("contact").get<std::string>();
    application.approved = json.at("approved").get<bool>();
  }
}

