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
    //Processing command line arguments
    for(int i = 0; i < argc; i++)
    {
        if(!strcmp(argv[i], "--download"))
        {
            boot::downloadAssets();
        }

        if(!strcmp(argv[i], "--help"))
        {
            std::cout << "Just run this program to start the server, or --configure to configure it!" << std::endl;
        }

        if(!strcmp(argv[i], "--configure"))
        {
            boot::configure();
        }
    }

    //Booting and ensuring everything is golden!
    h::boot();
    h::log("Checking installation...");
    boot::checkInstallation();
    h::log("Performing postboot...");
    boot::boot();

    //Just a grace sleep period. 100% unnecessary ;)
    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    if(!dev::fs::checkFolder("assets"))
    {
        h::log("Assets folder does not exist! Please run this executable with the --download flag!");
        h::shutdown();
    }

    //Booting and running the server
    h::log("Creating the server");
    s::web_server s;
    h::log("Setting the server listening port to: " + dev::fs::read_file("installation/portno.cfg"));
    s.set_listening_port(std::atoi(dev::fs::read_file("installation/portno.cfg").c_str()));
    h::log("Starting the server...");
    s.start();

    h::shutdown();
}
