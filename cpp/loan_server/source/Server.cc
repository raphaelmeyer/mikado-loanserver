#include <loan_server/Server.h>
#include <loan_server/IHandler.h>

#include <mongoose/mongoose.h>

#include <sstream>
#include <stdexcept>

namespace http
{
  namespace
  {
    std::map<std::string, std::string> parse_query_string(std::string const & query_string) {

      auto url_decode = [](std::string const & url) {
        char buffer[1024];
        auto len = mg_url_decode(url.c_str(), url.size(), buffer, sizeof(buffer), 1);
        if(len < 0) {
          throw std::runtime_error{"url decode error"};
        }
        return std::string(buffer, len);
      };

      std::map<std::string, std::string> parameters;

      std::istringstream iss{query_string};
      std::string parameter;
      while(std::getline(iss, parameter, '&')) {
        auto const pos = parameter.find('=');
        auto const name = url_decode(parameter.substr(0, pos));
        auto const value = url_decode(parameter.substr(pos + 1));
        parameters[name] = value;
      }
      return parameters;
    }

    void ev_handler(mg_connection * connection, int event, void * event_data) {
      if (event == MG_EV_HTTP_REQUEST) {
        auto message = static_cast<http_message const *>(event_data);

        Request request{};

        request.uri = std::string(message->uri.p, message->uri.len);

        std::string query_string(message->query_string.p, message->query_string.len);
        request.parameters = parse_query_string(query_string);

        IHandler * handler = static_cast<IHandler *>(connection->user_data);
        auto const response = handler->handle(request);

        mg_send_head(connection, response.status_code, response.response.size(), response.content_type.c_str());
        mg_send(connection, response.response.c_str(), response.response.size());

        return;
      }
    }
  }

  Server::Server(IHandler & handler, std::uint16_t port)
    : _handler(handler)
    , _port(port)
    , _running(false)
    , _server_thread()
  {
  }

  void Server::start() {
    _running = true;
    _server_thread = std::thread{
      [this]{
        mg_mgr manager{};
        mg_mgr_init(&manager, nullptr);

        auto const port = std::to_string(_port);
        auto connection = mg_bind(&manager, port.c_str(), ev_handler);
        connection->user_data = static_cast<void *>(&_handler);

        mg_set_protocol_http_websocket(connection);

        while(_running) {
          mg_mgr_poll(&manager, 1000);
        }
        mg_mgr_free(&manager);
      }
    };
  }

  void Server::stop() {
    _running = false;
    _server_thread.join();
  }

}

