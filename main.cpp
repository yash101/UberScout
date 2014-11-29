#include "include/host.hxx"
#include "include/server.hxx"
#include "lib/dlib/dir_nav.h"
#include "include/database.hxx"
#include "include/file.hxx"
#include "include/boot.hxx"
#include "lib/dlib/iosockstream.h"
#include "lib/dlib/http_client/http_client.h"
int main(int argc, char** argv)
{
    if(argc > 1)
    {
        if(!strcmp(argv[1], "--help"))
        {
            std::cout << "Just run this program to start the server, or --configure to configure it!" << std::endl;
        }
        else
        {
            boot::configure();
        }
    }

    h::boot();
    h::log("Checking installation...");
    boot::checkInstallation();
    h::log("Performing postboot...");
    boot::boot();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    h::log("Creating the server");
    s::web_server s;
    h::log("Setting the server listening port to: " + dev::fs::read_file("installation/portno.cfg"));
    s.set_listening_port(std::atoi(dev::fs::read_file("installation/portno.cfg").c_str()));
    h::log("Starting the server...");
    s.start();
    h::shutdown();
}
