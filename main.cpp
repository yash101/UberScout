#include "include/host.hxx"
#include "include/server.hxx"
#include "lib/dlib/dir_nav.h"
int main()
{
    h::boot();
    h::log("Hello World!");
    s::web_server s;
    s.set_listening_port(8000);
    s.start();
    h::shutdown();
}
