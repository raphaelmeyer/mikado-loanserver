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

namespace mikado
{
  Server::Server(IHandler const & handler)
    : _handler(handler)
  {
  }

  void Server::start() {
    mg_mgr mgr;
    mg_connection *c;

    mg_mgr_init(&mgr, NULL);
    c = mg_bind(&mgr, "8080", ev_handler);
    mg_set_protocol_http_websocket(c);

    for (;;) {
      mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
  }

}

