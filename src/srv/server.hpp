#pragma once

#include "pch.hpp"

namespace mr {
    class Application;
    class Prim;

    class Server {
    private:
        httplib::Server _srv;
        std::string _ip = "";
        std::vector<std::string> _clients;
        Application &_parent;

    public:
        Server(Application &parent, std::string val) : _parent(parent), _ip(val) {
          _srv.set_error_handler([](const auto& req, auto& res) {
              auto fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
              char buf[BUFSIZ];
              snprintf(buf, sizeof(buf), fmt, res.status);
              res.set_content(buf, "text/html");
              });
        };
        void connect_to_canvas(std::string);
        void server_func();

        ~Server() {
            _srv.stop();
        }

        void stop() noexcept {
            _srv.stop();
        }
        void sync_object(std::string);
        void append_ip(std::string);
        void add_new_user();
    };

    std::string get_self_ip();
}

