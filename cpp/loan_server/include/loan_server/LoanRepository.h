#include <string>

namespace mikado
{
  class LoanApplication;
  struct Ticket;

  class LoanRepository {
    public:
      static LoanApplication fetch(std::string ticket_id);
      static LoanApplication fetch(long ticket_id);
      static Ticket store(LoanApplication const & application);
      static Ticket approve(std::string ticket_id);

      static std::string const REPOSITORY_ROOT;
  };
}

