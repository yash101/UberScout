#include "../include/boot.hxx"
#include "../include/database.hxx"
#include "../include/file.hxx"
#include "../include/host.hxx"
#ifndef __WIN32
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <map>

#include "../lib/dlib/iosockstream.h"
#include "../lib/dlib/dir_nav.h"

#define DEFAULT_INSTALLATION_PORT   "3000"
#define DEVYASH_CDN                 "/x/uberscout/respack.zip"
#ifdef __WIN32
std::string unziputility = "";
#else
std::string unziputility = "unzip ";
#endif

template<typename T> inline std::string toString(T b)
{
    std::stringstream str;
    str << b;
    return str.str();
}

void boot::downloadAssets()
{
    try
    {
        dlib::iosockstream sock("devyashis.me:80");
        sock << "GET " << DEVYASH_CDN << " HTTP/1.0\r\n\r\n";
        std::string x;
        while(sock.peek() != EOF)
        {
            x = x + (char) sock.get();
        }
        unsigned int start = x.find("\r\n\r\n");
        if(start + 4 > x.size())
        {
            h::log("Server transaction failed!");
        }
        else
        {
            dev::fs::write_file("download.zip", x.substr(start + 4, x.size()));
            dlib::file downloadfile("download.zip");
            std::string cmd = unziputility;
            system(toString(unziputility + " download.zip").c_str());
        }
    }
    catch(std::exception& e)
    {
        h::log(e.what());
    }
}

void boot::checkInstallation()
{
    dev::fs::write_file("installation/.testinst", "This file is to test that this directory exists.");
    if(!dev::fs::checkFile("installation/.testinst"))
    {
        h::log("The installation directory does not exist! Installing!");
        install();
    }

    h::log("Server starting on port: " + dev::fs::read_file("installation/portno.cfg"));
}

void boot::install()
{
    h::log("Installation has begun!");
    h::log("Creating installation directory!");
    dev::fs::makedirpath("installation");
    h::log("Creating server port file!");
    dev::fs::write_file("installation/portno.cfg", DEFAULT_INSTALLATION_PORT);
    h::log("Installation complete!");
}

void boot::configure()
{
    std::string buffer;

    checkInstallation();
    std::cout << "This utility will guide you through the configuration of this server!" << std::endl;
    std::cout << "Port number...This is the port that the server will listen on!" << std::endl << "# ";

    unsigned short int portno;
    std::getline(std::cin, buffer);
    portno = std::atoi(buffer.c_str());
    dev::fs::write_file_async("installation/portno.cfg", toString(portno));

    h::boot();

    std::cout << "Enable debug output? This will cause extremely verbose output on your terminal screen! Y/N? ";
    char c;
    std::cin >> c;
    if (toupper(c) == 'Y')
    {
        h::setCfg("debug", true);
    }

    exit(EXIT_SUCCESS);
}

void __fork()
{
#ifndef __WIN32
    if(h::getCfg("fork"))
    {
        h::log("Forking has been enabled!");
    }
    if(h::getCfg("fork_listener"))
    {
        h::setCfg("fork", true);
    }

    if(h::getCfg("fork"))
    {
        h::log("About to fork!");
        pid_t pid = fork();
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        if(pid < 0)
        {
            h::log("Failed to fork! This server will run without forking!");
        }
        else
        {
            if(pid == 0)
            {
                h::log("Child PID acquired!");
                h::log("Child PID written to installation/pid.dat");
                dev::fs::write_file_async("installation/pid.dat", toString(getpid()));
            }
            else
            {
                if(h::getCfg("fork_listener"))
                {
                    h::log("The listener will listen for 10 seconds, for any messages generated by the child before exit!");
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                }
                h::log("Parent is exiting!");
                h::shutdown();
            }
        }
    }
#endif
}

void boot::boot()
{
    __fork();
}
