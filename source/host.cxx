#include "../include/host.hxx"
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <csignal>
#include <thread>

#include "../lib/dlib/config_reader.h"

#ifndef CFGB_LOCATION
#define CFGB_LOCATION   "appb.cfg"
#endif

#ifndef LOG_LOCATION
#define LOG_LOCATION    "log.out"
#endif

namespace misc
{
    std::string getTime()
    {
        std::stringstream str;
        std::time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        str << asctime(timeinfo);

        if(str.str().size() != 0)
        {
            return str.str().substr(0, str.str().size() - 1);
        }
        else
        {
            return str.str();
        }
    }
}

namespace vars
{
    static std::ifstream cfgin(CFGB_LOCATION);
    static std::map<std::string, bool> cflags;
    static std::ofstream logout(LOG_LOCATION, std::ios::app);
}

void sig(int action)
{
    h::log("Quitting due to signal [" + dlib::cast_to_string(action) + "] being raised!");
    vars::logout.close();
    vars::cfgin.close();
    exit(EXIT_SUCCESS);
}

void setSigHandlers()
{
    if(h::getCfg("handle_signals"))
    {
        h::log("Setting signals for SIGINT, SIGABRT, SIGFPE, SIGSEGV and SIGTERM.");
        signal(SIGINT, sig);
        signal(SIGABRT, sig);
        signal(SIGFPE, sig);
        signal(SIGSEGV, sig);
        signal(SIGTERM, sig);
    }
    else
    {
        h::log("Signal handling disabled! Add handle_signals to the config_b <" + dlib::cast_to_string(CFGB_LOCATION) + "> file.");
    }
}

namespace parser
{
    inline bool operator==(std::string x, std::string y)
    {
        return !strcmp(x.c_str(), y.c_str());
    }

    inline bool yesno(std::string chk)
    {
        return chk == "yes" || chk == "true" || chk == "1" || chk == "y" || chk == "t" || chk == "enable";
    }

    void parseCfg()
    {
        std::string buf;
        if(vars::cfgin.is_open())
        while(std::getline(vars::cfgin, buf))
        {
            vars::cflags[buf] = true;
            h::log("Enabled: " + buf);
        }
    }
}

void checkcfg()
{
    if(!vars::cfgin.is_open())
    {
        h::log("Configuration is not open or does not exist!!!");
        std::ofstream fout(CFGB_LOCATION);
        if(fout.is_open())
        {
            fout << "debug" << std::endl;
            fout << "ramfs" << std::endl;
            fout.close();
            h::log("Successfully wrote configuration file to: " + dlib::cast_to_string(CFGB_LOCATION));
            vars::cfgin.open(CFGB_LOCATION, std::ifstream::in);
            if(!vars::cfgin.is_open())
            {
                h::log("Unable to open configuration file! Something's wrong!");
            }
        }
        else
        {
            h::log("Unable to write configuration file to: " + dlib::cast_to_string(CFGB_LOCATION) +
                   "! Perhaps, do you have the permissions to write there?");
        }
    }
}

bool h::getCfg(std::string x)
{
    if(vars::cflags.find(x) == vars::cflags.end())
    {
        return false;
    }
    else
    {
        return vars::cflags[x];
    }
}

void h::setCfg(std::string x, bool val)
{
    if(!val)
    {
        vars::cflags.erase(x);
    }
    else
    {
        vars::cflags[x] = true;
    }
    std::ofstream fout(CFGB_LOCATION);
    if(fout.is_open())
    {
        for(std::map<std::string, bool>::const_iterator it = vars::cflags.begin(); it != vars::cflags.end(); it++)
        {
            fout << it->first << std::endl;
        }
        fout.close();
    }
    else
    {
        h::log("Unable to sync config file changes!");
    }
}

void h::log(std::string in)
{
    if(h::getCfg("debug"))
    {
        std::cout << misc::getTime() << ": " << in << std::endl;
    }
    if(vars::logout.is_open())
    {
        vars::logout << misc::getTime() << ": " << in << std::endl;
    }
}

void h::putCfg(std::string callname)
{
    h::setCfg(callname, true);
}

void h::boot()
{
    checkcfg();
    parser::parseCfg();
    setSigHandlers();
}

void h::shutdown()
{
    h::log("h::shutdown() called!");
    sig(-1);
    exit(EXIT_SUCCESS);
}
