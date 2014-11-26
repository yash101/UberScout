#ifndef DATABASE_HXX
#define DATABASE_HXX
#include <vector>
#include <string>
namespace d
{
    typedef unsigned short ushort;
    std::vector<ushort> getTeamNumbers();
    std::string getTeamName(ushort team_number);
    void registerTeam(d::ushort team_number, std::string team_name);
    void writeTeamNumbers(std::vector<d::ushort> nums);
    void rmTeam(d::ushort team);
    void setTeamDescription(d::ushort team_number, std::string description);
    void modTeamValue(d::ushort team_number, std::string name, std::string data);
}
#endif // DATABASE_HXX
