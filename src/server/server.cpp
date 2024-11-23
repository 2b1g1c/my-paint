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


void Server::connect_to_canvas(std::string val) {
  // get/post reqs
  _srv.listen(_ip, 4747);
}


void Server::server_func() {
  // HTTP

  _srv.Get("/cgsg", [](const httplib::Request &, httplib::Response &res) {
    // send data to draw
    res.set_content("Hello World!", "text/plain");
  });
  _srv.listen(_ip, 4747);
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
