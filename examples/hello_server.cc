/*
   Mathieu Stefani, 13 février 2016

   Example of an hello world server
*/


#include "pistache/endpoint.h"

#include <iostream>

using namespace Pistache;

class HelloHandler : public Http::Handler {
public:

    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request&, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "Hello World");
    }
};

int main() {
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
    auto opts = Pistache::Http::Endpoint::options()
        .threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<HelloHandler>());
    server.serveThreaded();

    std::cout << "Press Enter to exit" << '\n';
    std::cin.get();

    server.shutdown();
}
