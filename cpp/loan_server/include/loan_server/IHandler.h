#include <string>

namespace mikado {

  struct Request {
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
