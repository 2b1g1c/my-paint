#pragma once
#include "pch.hpp"

class Server {
private:
    httplib::Server _srv;
    std::string _ip = "";
    std::vector<std::string> _clients;
public:
    Server(std::string val) : _ip(val) {};
    void connect_to_canvas(std::string);
    void server_func();
    ~Server() {
        _srv.stop();
    }
    void stop() noexcept {
        _srv.stop();
    }
};


std::string get_self_ip();