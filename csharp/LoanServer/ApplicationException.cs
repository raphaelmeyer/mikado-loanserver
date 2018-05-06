using System;

namespace MikadoMethod.LoanServer {
  public class ApplicationException : Exception {
    public ApplicationException(string message) : base(message) {}
    public ApplicationException(string message, Exception e) : base(message, e) {}
  }
}

