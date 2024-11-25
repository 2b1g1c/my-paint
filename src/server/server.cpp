#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib") // link a library for Winsock
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <ifaddrs.h>
    #include <unistd.h>
#endif

#include "server/server.hpp"


void Server::append_ip(std::string vec_vals) {
    // parse json of vec_vals
}


void Server::connect_to_canvas(std::string val) {
  // get/post reqs
  httplib::Client cli(val, 4747);
  cli.Post("/cgsg/my_ip", _ip, "text/plain"); // send itself ip
  
  auto res = cli.Get("/cgsg/cli"); // refresh vector of _clients with this user
  append_ip(res->body);
  add_new_user();
}


void Server::add_new_user() {
  for (int i = 0; i < _clients.size(); i++) {
      httplib::Client cli(_clients[i], 4747);
      // json data instead of second param
      auto res = cli.Post("/cgsg/new_user", _clients[i], "text/plain");
  }
}


void Server::server_func() {
  // HTTP

  /*_srv.Get("/cgsg", [](const httplib::Request &, httplib::Response &res) {
    // send data to draw
    res.set_content("Hello World!", "text/plain");
  });*/

  _srv.Get("/cgsg/cli", [this](const httplib::Request &, httplib::Response &res) {
    // _clients -> json
    nlohmann::json j;
    // Create an array for saving ip adresses
    j["ip"] = nlohmann::json::array();
    for (int i = 0; i < _clients.size(); i++) {
      j["ip"].push_back(_clients[i]);
    }
    std::string json_str = j.dump();
    res.set_content("", "application/json");
  });

  /*
  _srv.Get("/cgsg/in", [](const httplib::Request &, httplib::Response &res) {
    // _clients -> json
    res.set_content("", "application/json");
  });
  */
  
  _srv.Post("/cgsg/draw", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content("POST", "text/plain");
    // req->body - there is json of new object for drawing
    //draw func
  });

  _srv.Post("/cgsg/draw", [this](const httplib::Request &req, httplib::Response &res) {
    res.set_content("POST", "text/plain");
    // req->body - the  re is json with ip of new system
    _clients.push_back(res.body);
  });

  _srv.Post("/cgsg/new_user", [this](const httplib::Request &req, httplib::Response &res) {
    res.set_content("POST", "text/plain");
    // req->body - the  re is json with ip of new system
    _clients.push_back(res.body);
  });

  _srv.Post("/cgsg/my_ip", [this](const httplib::Request &req, httplib::Response &res) {
    res.set_content("POST", "text/plain");
    // req->body - the  re is json with ip of new system
    _clients.push_back(res.body);
  });
  

  _srv.listen(_ip, 4747);
}

void Server::draw_object() {
    for (int i = 0; i < _clients.size(); i++) {
        httplib::Client cli(_clients[i], 4747);
        // json data instead of second param
        auto res = cli.Post("/cgsg/draw", "", "application/json");
    }
}


std::string get_self_ip() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return "WSAStartup failed";
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        WSACleanup();
        return "gethostname failed";
    }

    struct hostent* host = gethostbyname(hostname);
    if (host == nullptr) {
        WSACleanup();
        return "gethostbyname failed";
    }

    // convert addr to a string
    struct in_addr addr;
    addr.s_addr = *(u_long*)host->h_addr_list[0];
    WSACleanup();
    return inet_ntoa(addr);

#else
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;
    
    if (getifaddrs(&ifap) == -1) {
        return "getifaddrs failed";
    }

    for (ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family == AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            // choose a first interface with ip
            if (strcmp(ifa->ifa_name, "lo") != 0) { // ignore loopback interface
                freeifaddrs(ifap);
                return std::string(addr);
            }
        }
    }
    freeifaddrs(ifap);
    return "IP not found";
#endif
}
