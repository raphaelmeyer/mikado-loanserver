using System;
using System.Net;

namespace MikadoMethod.LoanServer {

  public class LoanServer {

    private static LoanHandler handler = new LoanHandler();

    public static void Main() {
      var listener = new HttpListener();
      listener.Prefixes.Add("http://localhost:8080/");
      listener.Start();
      while(listener.IsListening) {
        var result = listener.BeginGetContext(ListenerCallback, listener);
        result.AsyncWaitHandle.WaitOne();
      }
      listener.Close();
    }

    private static void ListenerCallback(IAsyncResult result) {
      var listener = (HttpListener) result.AsyncState;
      var context = listener.EndGetContext(result);
      handler.HandleRequest(context);
    }
  }

}

