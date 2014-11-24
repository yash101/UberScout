#ifndef HOST_HXX
#define HOST_HXX
#include <string>
#include <thread>
#include <sstream>
namespace h
{
    void boot();
    bool getCfg(std::string x);
    void putCfg(std::string callname);
    void log(std::string in);
    void setCfg(std::string x, bool val);
    void shutdown();
    template<typename T> std::string toString(T x)
    {
        std::stringstream str;
        str << x;
        return str.str();
    }
}
#endif // HOST_HXX
