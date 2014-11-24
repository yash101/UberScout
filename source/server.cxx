#include "../lib/dlib/server.h"
#include "../include/server.hxx"
#include "../include/host.hxx"
#include "../include/file.hxx"
#include "server/server_func.hxx"
#include <string>
#include <cstring>

const std::string s::web_server::on_request(const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing)
{
    //Perform the logging of our request
    h::log("Recieved Request: " + incoming.path + " from " + incoming.foreign_ip + ":" + h::toString(incoming.foreign_port));
    if(incoming.path == "/")
    {
        outgoing.headers["Content-type"] = "text/html";
        return dev::fs::read_file("assets/web/html/index.zhtml");
    }
    if(incoming.path.substr(0, 5) == "/file")
    {
        return process_f_req(incoming.path, outgoing);
    }
    return "Error! Unknown request!";
}
