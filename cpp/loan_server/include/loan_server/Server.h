#include <thread>
#include <cstdint>

namespace http
{
  class IHandler;

  class Server {
    public:
      Server(IHandler & handler, std::uint16_t port);
      void start();
      void stop();

    private:
      IHandler & _handler;
      std::uint16_t _port;
      bool _running;
      std::thread _server_thread;
  };
}
