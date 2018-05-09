#include <string_view>
#include <json/json.hpp>

#include <string>

using Json = nlohmann::json;

namespace mikado
{
  struct LoanApplication {
    long application_no;
    long amount;
    std::string contact;
    bool approved;
  };

  void to_json(Json & json, LoanApplication const & application);
  void from_json(Json const & json, LoanApplication & application);
}

