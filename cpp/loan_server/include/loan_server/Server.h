#include <cstdint>

namespace mikado
{
  class IHandler;

  class Server {
    public:
      Server(IHandler const & handler, std::uint16_t port);
      void start();

    private:
      IHandler const & _handler;
      std::uint16_t _port;
  };
}
