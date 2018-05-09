#include <map>
#include <string>

namespace http {

  struct Request {
    std::map<std::string, std::string> parameters;
  };

  struct Response {
    int status_code;
    std::string content_type;
    std::string response;
  };

  class IHandler {
    virtual Response handle(Request request) const = 0;
  };
}
