using System;
using System.Net;

namespace MikadoMethod.LoanServer {
  public class LoanApplication {
    public long ApplicationNo { get; set; }
    public long Amount { get; set; }
    public string Contact { get; set; }
    public bool Approved { get; set; }

    public LoanApplication() {
      ApplicationNo = LoanHandler.GetNextId();
    }
  }
}

