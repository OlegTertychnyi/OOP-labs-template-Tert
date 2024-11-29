#pragma once

#include <string>
#include<stdbool.h>
#include <initializer_list>

class Seven{
    public:
        Seven();
        Seven(const size_t & n, unsigned char t = 0);
        Seven(const std::initializer_list<unsigned char> &t);
        Seven(const std::string &t);
        Seven(const Seven& other);
        Seven(Seven&& other) noexcept;


        Seven operator+(const Seven& other) const;
        Seven operator-(const Seven& other) const;
        
        bool operator==(const Seven& other) const;
        bool operator>(const Seven& other) const;
        bool operator<(const Seven& other) const;
        Seven& operator=(const Seven& other);

        size_t get_size() const;
        unsigned char* get_digits() const;
        void normal();


        virtual ~Seven() noexcept;
        
        

    private:
        size_t _size;
        unsigned char *_digits;
};

std::ostream& operator<<(std::ostream& os, const Seven& num);
