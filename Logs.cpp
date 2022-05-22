#include "Logs.h"
#include <sstream>
#include <algorithm>
#include <numeric>

parsing::Logs::~Logs()
{
	file_.close();
}

std::vector<std::string> parsing::Logs::Split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        item = EraseSymbol(item," []");
        if (item.empty() or item == " " or canselcymbol_.count(item) == 1)
        {
            continue;
        }
        elems.push_back(item);
    }
 
    return elems;
}

std::string parsing::Logs::EraseSpace(std::string& str)
{
        auto endSecond = str.find_last_not_of(" ]");
    if (endSecond != std::string::npos)
        str.erase(endSecond + 1);
    if (str.find_first_not_of(" ") != std::string::npos)
    {
        str.erase(0, str.find_first_not_of(" ["));
    }
    return str;
}

std::string parsing::Logs::EraseSymbol(std::string str, const std::string& symbol)
{
    auto endSecond = str.find_last_not_of(symbol);
    if (endSecond != std::string::npos)
        str.erase(endSecond + 1);
    if (str.find_first_not_of(" ") != std::string::npos)
    {
        str.erase(0, str.find_first_not_of(symbol));
    }
    return str;
}



std::set<std::string>& parsing::Logs::AddCanselSymbol(std::string&& str)
{
    canselcymbol_.insert(str);
    return canselcymbol_;
}

std::set<std::string>& parsing::Logs::AddCanselSymbol(std::initializer_list<std::string> list)
{
    canselcymbol_.insert(list);
    return canselcymbol_;
}

std::set<std::string>& parsing::Logs::DeletCanselSymbol(std::string&& str)
{
    canselcymbol_.erase(str);
    return canselcymbol_;
}

void parsing::Logs::Load()
{
    if (file_.is_open())
    {
        std::vector<std::vector<std::string>*> tmp;
        std::string words;
        while (!file_.eof())
        {
            std::getline(file_, words);
            auto sp = Split(words, ';');
            if (sp.size() > 20 )
            {
                if(tmp.empty())
                {
                std::for_each(sp.begin(),sp.end(),[this,&tmp](std::string& str){
                tmp.push_back(&AddSection(EraseSymbol(str," ")));
                });
                }
                else
                {
                    size_t i = 0;
                    std::for_each(sp.begin(),sp.end(),[&tmp,&i](std::string& str){
                        tmp[i++]->push_back(str);
                    });

                }
                sp.clear();
            }
            if (!sp.empty() and (sp[0].find(":") != std::string::npos) )
            {
                std::transform(next(sp.begin()), sp.end(), std::back_inserter(AddSection(EraseSymbol(sp[0], ":"))),
                    [](std::string& str)
                    {
                        return str;
                    });
            }
        }
    }
    else
    {
        throw ErorReadFile("Not open's file");
    }
}

std::vector<std::string>& parsing::Logs::AddSection(const std::string& str)
{
    return logs_[str];
}
