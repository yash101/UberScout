#include "../include/file.hxx"
#include <fstream>
#include <string>
#include <thread>
#include <sstream>
#include <iostream>

bool dev::fs::write_file(std::string file_location, std::string data)
{
    std::ofstream fout(file_location.c_str());
    if(fout.is_open())
    {
        fout << data;
        fout.close();
        return true;
    }
    else
    {
        return false;
    }
}

void dev::fs::write_file_async(std::string file_location, std::string data)
{
    std::thread([](std::string file_location, std::string data)
    {
        dev::fs::write_file(file_location, data);
    }, file_location, data).detach();
}

std::string dev::fs::read_file(std::string file_location)
{
    std::ifstream fin(file_location.c_str());
    if(fin.is_open())
    {
        std::stringstream str;
        str << fin.rdbuf();
        fin.close();
        return str.str();
    }
    else
    {
        return "File could not be opened!";
    }
}
