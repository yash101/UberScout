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

template<typename T> inline std::string toString(T x)
{
    std::stringstream str;
    str << x;
    return str.str();
}

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
//    std::stringstream str;
//    str << name;

//    std::vector<std::string> names;
//    std::string buf;
//    while(std::getline(str, buf, PCONCAT))
//    {
//        names.push_back(buf);
//    }
//    for(unsigned int i = 0; i < names.size(); i++)
//    {
//        std::stringstream x;
//        for(unsigned int j = 0; j < i; j++)
//        {
//            x << names[j] << PCONCAT;
//            std::cout << "Creating directory: " << names[i] << PCONCAT << std::endl;
//        }
//        dev::fs::makedir(x.str());
//    }
//    std::vector<std::string> names;
//    std::string buf;
//    std::stringstream str(name);
//    while(str.peek() != EOF)
//    {
//        if((char) str.peek() == '/' || (char) str.peek() == '\\')
//        {
//            std::cout << "Pushed back: " << buf << std::endl;
//            names.push_back(buf);
//            buf = "";
//        }
//        else
//        {
//            buf = buf + toString((char) str.peek());
//        }
//        str.get();
//    }
//    names.push_back(buf);

//    for(unsigned int i = 0; i < names.size(); i++)
//    {
//        std::cout << "Buffer: " << names[i] << std::endl;
//        std::stringstream x;
//        for(unsigned int j = 0; j < i; j++)
//        {
//            x << names[j] << PCONCAT;
//            std::cout << "Creating directory: " << names[i] << PCONCAT << std::endl;
//        }
//        dev::fs::makedir(x.str());
//    }
    std::stringstream fn(name);
    std::vector<std::string> fns;
    std::string buffer;

    while(fn.peek() != EOF)
    {
        char ch = (char) fn.get();
        buffer = buffer + ch;
        if(ch == '/' || ch == '\\')
        {
            fns.push_back(buffer);
            buffer.clear();
        }
    }
    if(buffer.size() != 0)
    {
        fns.push_back(buffer);
    }

    for(unsigned int i = 0; i < fns.size(); i++)
    {
        std::stringstream z;
        for(unsigned int j = 0; j <= i; j++)
        {
            z << fns[j];
        }
        dev::fs::makedir(z.str());
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

bool dev::fs::checkFile(std::string name)
{
    std::ifstream fin(name.c_str());
    bool x = !fin.fail();
    if(fin.is_open())
    {
        fin.close();
    }
    return x;
}

//bool dev::fs::checkFolder(std::string folder)
//{
//    dev::fs::write_file(folder + "/.testdir", "Random test directory file!");
//    if(dev::fs::checkFile(folder + "/.testdir"))
//    {
//        dev::fs::deleteFile(folder + "/.testdir");
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
