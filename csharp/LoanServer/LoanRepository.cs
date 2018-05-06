using System;
using System.IO;
using System.Text;

namespace MikadoMethod.LoanServer {
  public class LoanRepository {

    public const string REPOSITORY_ROOT = "./loan";
    public const string FILE_EXTENSION = ".loan";

    public static LoanApplication Fetch(string ticketId) {
      long id;
      long.TryParse(ticketId, out id);
      return Fetch(id);
    }

    public static LoanApplication Fetch(long ticketId) {
      try {
        var json = File.ReadAllText(FileFromApplication(ticketId), Encoding.UTF8);
        return Json.From<LoanApplication>(json);
      } catch(FileNotFoundException e) {
        throw new ApplicationException("Ticket not found", e);
      } catch(Exception e) {
        throw new ApplicationException("Could not fetch application", e);
      }
    }

    public static Ticket Store(LoanApplication application) {
      try {
        Directory.CreateDirectory(REPOSITORY_ROOT);
        var json = Json.To<LoanApplication>(application);
        File.WriteAllText(FileFromApplication(application.ApplicationNo), json, Encoding.UTF8);
      } catch(Exception e) {
        throw new ApplicationException("Could not store application", e);
      }
      return new Ticket{ Id = application.ApplicationNo };
    }

    private static string FileFromApplication(long applicationNo) {
      return REPOSITORY_ROOT + "/" + applicationNo + FILE_EXTENSION;
    }

    public static Ticket Approve(string ticketId) {
      var application = Fetch(ticketId);
      application.Approved = true;
      Store(application);
      return new Ticket{ Id = application.ApplicationNo };
    }

  }
}

