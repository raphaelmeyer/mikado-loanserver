#include <loan_server/Server.h>
#include <loan_server/IHandler.h>

#include <mongoose/mongoose.h>

namespace
{
  static void ev_handler(struct mg_connection *c, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
      struct http_message *hm = (struct http_message *) p;

      // get handler from user_data
      // auto const response = handler->handle({x, y, z});

      mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
      mg_printf(c, "%.*s", (int)hm->message.len, hm->message.p);
    }
  }

}

namespace http
{
  Server::Server(IHandler const & handler, std::uint16_t port)
    : _handler(handler)
    , _port(port)
  {
  }

  void Server::start() {
    mg_mgr manager;
    mg_mgr_init(&manager, NULL);

    auto const port = std::to_string(_port);
    auto connection = mg_bind(&manager, port.c_str(), ev_handler);

    mg_set_protocol_http_websocket(connection);

    for (;;) {
      mg_mgr_poll(&manager, 1000);
    }
    mg_mgr_free(&manager);
  }

}

