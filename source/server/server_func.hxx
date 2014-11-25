#ifndef SERVER_FUNC_HXX
#define SERVER_FUNC_HXX
#include "../../include/server.hxx"
#include "../../include/host.hxx"
#include "../../include/file.hxx"
#include "../../include/database.hxx"
#include "../../lib/dlib/server.h"
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

inline bool operator==(std::string a, std::string b)
{
    return !strcmp(a.c_str(), b.c_str());
}

std::string team_list()
{
    std::vector<d::ushort> teams = d::getTeamNumbers();
    std::stringstream str;
    for(unsigned int i = 0; i < teams.size(); i++)
    {
        str << teams[i] << std::endl;
    }

    return str.str();
}

std::string team_names()
{
    std::vector<d::ushort> teams = d::getTeamNumbers();
    std::stringstream s;
    for(unsigned int i = 0; i < teams.size(); i++)
    {
        s << d::getTeamName(teams[i]) << std::endl;
    }
    return s.str();
}

std::string process_f_req(std::string location, dlib::outgoing_things& outgoing)
{
    if(location.substr(0, 14) == "/file/css?loc=")
    {
        outgoing.headers["Content-type"] = "text/css";
        return dev::fs::read_file(location.substr(14, location.size()));
    }

    if(location.substr(0, 15) == "/file/html?loc=")
    {
        outgoing.headers["Content-type"] = "text/html";
        return dev::fs::read_file(location.substr(15, location.size()));
    }

    if(location.substr(0, 13) == "/file/js?loc=")
    {
        outgoing.headers["Content-type"] = "text/javascript";
        return dev::fs::read_file(location.substr(13, location.size()));
    }

    if(location.substr(0, 14) == "/file/png?loc=")
    {
        outgoing.headers["Content-type"] = "image/png";
        return dev::fs::read_file(location.substr(14, location.size()));
    }

    if(location.substr(0, 15) == "/file/wave?loc=")
    {
        outgoing.headers["Content-type"] = "audio/wave";
        return dev::fs::read_file(location.substr(15, location.size()));
    }

    if(location.substr(0, 15) == "/file/mpeg?loc=")
    {
        outgoing.headers["Content-type"] = "audio/mpeg";
        return dev::fs::read_file(location.substr(15, location.size()));
    }

    return "";
}

#endif // SERVER_FUNC_HXX
