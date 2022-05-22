// Readxls.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Logs.h"



using namespace std;



int main()
{
    parsing::Logs log_("test.csv"s);
    log_.AddCanselSymbol({ "[","]","cm","kg"});
    log_.Load();
    auto valueVec = log_.Find<int>("X1");

    for(auto &val : valueVec)
    {
        std::cout<< val << std::endl;
    }

}



