using System.IO;
using System.Runtime.Serialization.Json;
using System.Text;

namespace MikadoMethod.LoanServer {
  public class Json {
    public static string To<T>(T data) {
      var serializer = new DataContractJsonSerializer(typeof(T));
      var ms = new MemoryStream();
      serializer.WriteObject(ms, data);
      var json = ms.ToArray();
      ms.Close();
      return Encoding.UTF8.GetString(json, 0, json.Length);
    }

    public static T From<T>(string json) where T : class, new() {
      var data = new T();
      var ms = new MemoryStream(Encoding.UTF8.GetBytes(json));
      var serializer = new DataContractJsonSerializer(typeof(T));
      data = serializer.ReadObject(ms) as T;
      ms.Close();
      return data;
    }
  }
}

