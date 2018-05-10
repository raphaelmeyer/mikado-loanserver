#include <json/json.hpp>

#include <string>

using Json = nlohmann::json;

namespace mikado
{
  class LoanApplication {
    public:
      long application_no;
      long amount;
      std::string contact;
      bool approved;

      static LoanApplication new_application();
  };

  void to_json(Json & json, LoanApplication const & application);
  void from_json(Json const & json, LoanApplication & application);

}

