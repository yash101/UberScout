#include "include/host.hxx"
#include "include/server.hxx"
#include "lib/dlib/dir_nav.h"
#include "include/database.hxx"
#include "include/file.hxx"
int main()
{
    h::boot();
    dev::fs::makedir("assets/database");
    d::registerTeam(300, "Another Team!");
    std::cout << "1165: " << d::getTeamName(1165) << std::endl;
    std::vector<d::ushort> hahas = d::getTeamNumbers();
    for(unsigned int i = 0; i < hahas.size(); i++)
    {
        std::cout << "Team: " << hahas[i] << " | " << d::getTeamName(hahas[i]) << std::endl;
    }
    s::web_server s;
    s.set_listening_port(8000);
    s.start();
    h::shutdown();
}
