#include <cstdint>

namespace http
{
  class IHandler;

  class Server {
    public:
      Server(IHandler & handler, std::uint16_t port);
      void start();

    private:
      IHandler & _handler;
      std::uint16_t _port;
  };
}
