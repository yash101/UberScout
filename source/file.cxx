#include "../include/file.hxx"
#include <fstream>
#include <string>
#include <thread>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif

bool dev::fs::write_file(std::string file_location, std::string data)
{
    std::ofstream fout(file_location.c_str());
    if(fout.is_open())
    {
        if(data.size() == 0)
        {
            fout.close();
            std::ofstream x(file_location.c_str(), std::ios::trunc);
            if(x.is_open())
            {
                x.close();
            }
        }
        else
        {
            fout << data;
            fout.close();
        }
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

void dev::fs::makedir(std::string name)
{
#ifdef _WIN32
    CreateDirectory(name.c_str(), NULL);
#else
    mkdir(name.c_str(), 0755);
#endif
}

void dev::fs::makedirpath(std::string name)
{
#ifdef _WIN32
#define PCONCAT '\\'
#else
#define PCONCAT '/'
#endif
    std::stringstream str;
    str << name;

    std::vector<std::string> names;
    std::string buf;
    while(std::getline(str, buf, PCONCAT))
    {
        names.push_back(buf);
    }
    for(unsigned int i = 0; i < names.size(); i++)
    {
        std::stringstream x;
        for(unsigned int j = 0; j < i; j++)
        {
            x << names[j] << PCONCAT;
        }
        dev::fs::makedir(x.str());
    }
}

void dev::fs::deleteFolder(std::string name)
{
#ifdef _WIN32
    RemoveDirectory(name.c_str());
#else
    rmdir(name.c_str());
#endif
}

void dev::fs::deleteFile(std::string name)
{
    remove(name.c_str());
}
