#include "../include/database.hxx"
#include "../include/file.hxx"
#include "../include/host.hxx"

#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

#define DB_PREFIX std::string("assets/database/")

template<typename z> int locate(std::vector<z> x, z find)
{
    for(unsigned int i = 0; i < x.size(); i++)
    {
        if(x[i] == find)
        {
            return i;
        }
    }
    return -1;
}

template<typename z> std::string toString(z x)
{
    std::stringstream str;
    str << x;
    return str.str();
}

std::vector<d::ushort> d::getTeamNumbers()
{
    std::vector<d::ushort> teams;
    std::ifstream fin(toString(DB_PREFIX + "team_list.dat").c_str());
    d::ushort x;
    while(fin >> x)
    {
        teams.push_back(x);
    }
    return teams;
}

std::string d::getTeamName(d::ushort team_number)
{
    std::vector<d::ushort> teams = d::getTeamNumbers();
    if(locate(teams, team_number) != -1)
    {
        return dev::fs::read_file(DB_PREFIX + toString(team_number) + "/name.dat");
    }
    else
    {
        return "The team specified could not be found!";
    }
}

void d::writeTeamNumbers(std::vector<d::ushort> nums)
{
    std::stringstream str;
    for(unsigned int i = 0; i < nums.size(); i++)
    {
        str << nums[i] << std::endl;
    }
    dev::fs::write_file_async(DB_PREFIX + "team_list.dat", str.str());
    return;
}

void d::rmTeam(d::ushort teamNumber)
{
    std::vector<d::ushort> teams = d::getTeamNumbers();
    std::vector<d::ushort> x;
    for(unsigned int i = 0; i < teams.size(); i++)
    {
        if(teams[i] != teamNumber)
        {
            x.push_back(teams[i]);
        }
    }
    if(x.size() != teams.size())
    {
        d::writeTeamNumbers(x);
    }
}

void d::registerTeam(d::ushort team_number, std::string team_name)
{
    h::log("Registering new team: " + toString(team_number) + " >> " + team_name);
    //Update the team DB!
    h::log("Adding team " + team_name + " to the team list!");
    std::vector<d::ushort> teams = d::getTeamNumbers();
    if(locate(teams, team_number) == -1)
    {
        std::ofstream fout(DB_PREFIX + "team_list.dat", std::ios::app);
        if(fout.is_open())
        {
            fout << team_number << std::endl;
        }
    }
    else
    {
        h::log("Not adding team " + toString(team_number) + " because it already exists!");
    }
    //Create the filesystem layout!
    dev::fs::makedir(DB_PREFIX + toString(team_number));
    dev::fs::write_file_async(DB_PREFIX + toString(team_number) + "/name.dat", team_name);
}

void d::setTeamDescription(d::ushort team_number, std::string description)
{
    dev::fs::write_file_async(DB_PREFIX + toString(team_number) + "/description.dat", description);
    return;
}

void d::modTeamValue(d::ushort team_number, std::string name, std::string data)
{

}
