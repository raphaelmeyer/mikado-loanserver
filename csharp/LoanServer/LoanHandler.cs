using System;
using System.IO;
using System.Net;

namespace MikadoMethod.LoanServer {
  public class LoanHandler {

    public const string APPLICATION = "apply";
    public const string FETCH = "fetch";
    public const string TICKET_ID = "ticketId";
    public const string APPROVE = "approve";

    public void HandleRequest(HttpListenerContext context) {

      var request = context.Request;
      var response = context.Response;
      var writer = new StreamWriter(response.OutputStream);

      response.ContentType = "application/json;charset=utf-8";

      try {
        if(IsApplication(request)) {
          LoanApplication application = new LoanApplication();
          application.Amount = AmountFrom(request);
          application.Contact = ContactFrom(request);
          Ticket ticket = LoanRepository.Store(application);
          writer.WriteLine(Json.To<Ticket>(ticket));
        } else if(IsStatusRequest(request) && IdSpecified(request)) {
          writer.WriteLine(FetchLoanInfo(request.QueryString.Get(TICKET_ID)));
        } else if(IsApproval(request) && IdSpecified(request)) {
          writer.WriteLine(ApproveLoan(request.QueryString.Get(TICKET_ID)));
        } else {
          response.StatusCode = (int)HttpStatusCode.BadRequest;
          writer.WriteLine("Incorrect parameters provided");
        }
      } catch(Exception e) {
        response.StatusCode = (int)HttpStatusCode.BadRequest;
        writer.WriteLine("Uh oh! Problem occured: {0}", e.Message);
      }

      writer.Close();
    }

    private string ContactFrom(HttpListenerRequest request) {
      return request.QueryString.Get("contact");
    }

    private long AmountFrom(HttpListenerRequest request) {
      return long.Parse(request.QueryString.Get("amount"));
    }

    private string ApproveLoan(string parameter) {
      return Json.To<Ticket>(LoanRepository.Approve(parameter));
    }

    private bool IsApproval(HttpListenerRequest request) {
      return APPROVE.Equals(request.QueryString.Get("action"));
    }

    private bool IdSpecified(HttpListenerRequest request) {
      return request.QueryString.Get(TICKET_ID) != null && ValidId(request) >= 0;
    }

    private long ValidId(HttpListenerRequest request) {
      long ticketId;
      if (long.TryParse(request.QueryString.Get(TICKET_ID), out ticketId)) {
        return ticketId;
      }
      return -1;
    }

    private bool IsStatusRequest(HttpListenerRequest request) {
      return FETCH.Equals(request.QueryString.Get("action"));
    }

    private bool IsApplication(HttpListenerRequest request) {
      return APPLICATION.Equals(request.QueryString.Get("action"));
    }

    private string FetchLoanInfo(string ticketId) {
      return Json.To<LoanApplication>(LoanRepository.Fetch(ticketId));
    }

    public static long GetNextId() {
      try {
        var files = Directory.GetFiles(LoanRepository.REPOSITORY_ROOT, "*" + LoanRepository.FILE_EXTENSION);
        return files.Length;
      } catch(DirectoryNotFoundException) {
        return 0;
      }
    }

  }
}

