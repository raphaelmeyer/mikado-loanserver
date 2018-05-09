#include <json/json.hpp>

using Json = nlohmann::json;

namespace mikado
{
  struct Ticket {
    long id;
  };

  void to_json(Json & json, Ticket const & ticket);
  void from_json(Json const & json, Ticket & ticket);
}

