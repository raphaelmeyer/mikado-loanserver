namespace mikado
{
  class LoanApplication;
  struct Ticket;

  class LoanRepository {
    public:
      static Ticket store(LoanApplication const & application);
  };
}

