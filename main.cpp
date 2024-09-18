#include "include/stdc++.h"
#include "include/execute.h"

int main()
{
    std::string day;
    int number;
    std::cout << "enter left value:";
    std::cin  >> day;
    std::cout << "enter right value:";
    std::cin  >> number;


    std::cout << "result: " << isAfraid(day,number) << std::endl;

    return 0;
}
