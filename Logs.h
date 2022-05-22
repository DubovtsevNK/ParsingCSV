#pragma once
#include <iostream>
#include<sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>


namespace parsing
{
class Logs
{
private: // member

    class ErorReadFile : std::exception
    {
    private:
        std::string error_;
    public:
        ErorReadFile():error_("Eror"){};
        ErorReadFile(const std::string &error) : error_(error){}
        const char* what() const noexcept
        {
            return error_.c_str();
        }

    };

    std::ifstream file_;
    std::set<std::string> canselcymbol_;

    //std::unordered_map < std::string, std::vector<std::string>> logs_;

private: //func
    std::vector<std::string> Split(const std::string& s, char delim);
    std::string EraseSpace(std::string &str);
    std::string EraseSymbol(std::string str, const std::string& symbol);
    std::vector<std::string>& AddSection(const std::string& str);
public:

    std::unordered_map < std::string, std::vector<std::string>> logs_;

    Logs(const std::string &file) : file_(file) {};

    template<typename T>
    std::vector<T> Find(const std::string& str)const
    {
        const auto ptr = logs_.at(str);
        std::vector<T> result;
        std::stringstream ss;
        T s;
        for(auto & val : ptr)
        {
            ss<<val;
            ss >> s;
            result.push_back(s);
            ss.clear();
        }
        return result;
    }
    void Load();
    std::set<std::string>& AddCanselSymbol(std::string&& str);
    std::set<std::string>& AddCanselSymbol(std::initializer_list<std::string> list);
    std::set<std::string>& DeletCanselSymbol(std::string&& str);
    size_t CountValue(std::string& str);



    ~Logs();



};

}//namespace parsing

