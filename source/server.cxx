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

    if(incoming.path == "/team_list?type=numbers")
    {
        return team_list();
    }

    if(incoming.path == "/team_list?type=names")
    {
        return team_names();
    }

    if(incoming.path == "/team_list?type=add")
    {
        return add_team(incoming);
    }

    if(incoming.path == "/team_list?type=remove")
    {
        return remove_team(incoming);
    }

    if(incoming.path == "/getvalue")
    {
        h::log("Requested data for team " + incoming.queries["team"] + " for " + incoming.queries["path"] + "/" + incoming.queries["name"]);
        return d::getTeamValue(std::atoi(incoming.queries["team"].c_str()), incoming.queries["path"], incoming.queries["name"]);
    }

    if(incoming.path == "/setvalue")
    {
        d::modTeamValue(std::atoi(incoming.queries["team"].c_str()), incoming.queries["path"], incoming.queries["name"], incoming.queries["data"]);
        h::log("Requested set data for team " + incoming.queries["team"] + " for " + incoming.queries["path"] + "/" + incoming.queries["name"] + " with data: " + incoming.queries["data"]);
        return "Command Invoked!!!";
    }

    if(incoming.path.substr(0, 5) == "/file")
    {
        return process_f_req(incoming.path, outgoing);
    }
    return "Error! Unknown request!";
}
