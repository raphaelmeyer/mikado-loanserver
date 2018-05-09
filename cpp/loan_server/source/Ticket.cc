#include <loan_server/Ticket.h>

namespace mikado
{
  void to_json(Json & json, Ticket const & ticket) {
    json = Json{{"id", ticket.id}};
  }

  void from_json(Json const & json, Ticket & ticket) {
    ticket.id = json.at("id").get<long>();
  }
}

