#include "../include/database.hxx"
#include "../include/file.hxx"
#include "../include/host.hxx"

#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>

#define DB_PREFIX std::string("assets/database/")

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
    if(std::find(teams.begin(), teams.end(), team_number) != teams.end())
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

void d::registerTeam(d::ushort team_number, std::string team_name)
{
    h::log("Registering new team: " + toString(team_number) + " >> " + team_name);
    //Update the team DB!
    h::log("Adding team " + team_name + " to the team list!");
    std::vector<d::ushort> teams = d::getTeamNumbers();
    //Check to make sure team does not exist yet!
    if(std::find(teams.begin(), teams.end(), team_number) == teams.end())
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
