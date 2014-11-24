#ifndef SERVER_HXX
#define SERVER_HXX
#include "../lib/dlib/server.h"
#include <string>
namespace s
{
    class web_server : public dlib::server_http
    {
    private:
        const std::string on_request(const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing);
    };
}
#endif // SERVER_HXX
