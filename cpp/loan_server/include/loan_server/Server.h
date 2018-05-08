namespace mikado
{
  class IHandler;

  class Server {
    public:
      Server(IHandler const & handler);
      void start();

    private:
      IHandler const & _handler;
  };
}
