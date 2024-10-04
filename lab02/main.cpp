#include"include/seven.h"
#include<iostream>
#include <stdexcept>
#include <exception>


int main(){
    try{
        Seven s1;
        std::cout << "s1:" << s1 << std::endl;

        Seven s2(3, '1');
        std::cout << "s2:" << s2 << std::endl;

        Seven s3({'1', '2', '3', '4', '5', '5'});
        std::cout << "s3:" << s3 << std::endl;

        Seven s4("1345");
        std::cout << "s4:" << s4 << std::endl;

        Seven s5(s2);
        std::cout << "s5:" << s5 << std::endl;

        Seven s6(std::move(s4));
        std::cout << "s6:" << s6 << std::endl;

        std::cout << "s6 + s2:" << s6 + s2 << std::endl;
        std::cout << "s6 - s2:" << s6 - s2 << std::endl;

        std::cout << "s6 == s2:" << (s6 == s2) << std::endl;
        std::cout << "s6 > s2:" << (s6 > s2) << std::endl;
        std::cout << "s6 < s2:" << (s6 < s2) << std::endl;

        Seven s7;
        s7 = s3;
        std::cout << "s7:" << s7 << std::endl;


        try{
            Seven s8("");

            Seven s9(0, '1');

            Seven s9('9');

        } catch(const std::exception& e){
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        
    }catch(const std::exception& e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}