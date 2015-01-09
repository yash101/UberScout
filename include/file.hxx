#ifndef FILE_HXX
#define FILE_HXX
#include <string>
namespace dev
{
    namespace fs
    {
        std::string read_file(std::string file_location);
        bool write_file(std::string file_location, std::string data);
        void write_file_async(std::string file_location, std::string data);
        void makedir(std::string name);
        void deleteFolder(std::string name);
        void deleteFile(std::string name);
        void makedirpath(std::string name);
        bool checkFile(std::string name);
        bool checkFolder(std::string name);
    }
}
#endif // FILE_HXX
