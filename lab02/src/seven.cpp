#include "../include/seven.h"
#include <stdexcept>
#include <exception>
#include<iostream>


void check_digit(const unsigned char &c){
    if(c < '0' || c > '6')
        throw std::invalid_argument("Invalid seven digit");
    return;
};

void check_size(const size_t &size){
    if(size == 0) throw std::invalid_argument("Size cannot be a zero");
};

unsigned char* allocate_memory(size_t size) {
    unsigned char* ptr = nullptr;

    try {
        ptr = new unsigned char[size]{0}; 
    } catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        throw; 
    }

    return ptr;
}

void Seven::normal() {
size_t i = 0;
    while (i < _size && _digits[i] == '0') ++i;
    if (i == _size) {
        _size = 1;
        _digits[0] = '0';
    } else {
        _size -= i;
        unsigned char* new_digits = allocate_memory(_size);
        std::copy(_digits + i, _digits + i + _size, new_digits);
        delete[] _digits;
        _digits = new_digits;
    }
};

Seven::Seven(): _size(0), _digits{nullptr}{}

Seven::Seven(const size_t& n, unsigned char t){
    check_size(n);
    _digits = allocate_memory(n);
    check_digit(t);
    for (size_t i{0}; i < n; ++i)
        _digits[i] = t;
    _size = n;
    this->normal();
}

Seven::Seven(const std::initializer_list<unsigned char>& t){
    check_size(t.size());
    _digits = allocate_memory(t.size());
    size_t i{0};
    for (auto &c : t){
        check_digit(c);
        _digits[i++] = c;
    }
    _size = t.size();
    this->normal();
}

Seven::Seven(const std::string& t){
    check_size(t.size());
    _digits = allocate_memory(t.size());
    _size = t.size();
    for(size_t i{0}; i < _size; ++i){
        check_digit(t[i]);
        _digits[i] = t[i];
    }
    this->normal();
}

Seven::Seven(const Seven& other){
    _size = other.get_size();
    _digits = allocate_memory(_size);
    std::copy(other._digits, other._digits + _size, _digits);
}

Seven::Seven(Seven &&other) noexcept{
    _size = other.get_size();
    _digits = other.get_digits();
 
    other._size = 0;
    other._digits = nullptr;
}

Seven:: ~Seven()  noexcept {
    delete[] _digits;
}

size_t Seven::get_size() const{
    return _size;
}

unsigned char* Seven::get_digits() const{
    return _digits;
}


Seven Seven::operator+(const Seven &other) const{
    size_t max_size = std::max(get_size(), other.get_size()) + 1;
    Seven result;
    result._digits = allocate_memory(max_size);
    result._size = max_size;
    size_t pre_result{0};

    for(size_t i{0}; i < max_size || pre_result != 0; ++i){
        unsigned char digit_1 = (i < get_size()) ? get_digits()[get_size() - i - 1] - '0': 0;
        unsigned char digit_2 = (i < other.get_size()) ? other.get_digits()[other.get_size() - i - 1] - '0': 0;
        unsigned char sum = digit_1 + digit_2 + pre_result;
        result.get_digits()[max_size - 1 - i] = (sum % 7) + '0';
        pre_result = sum / 7;
    }

    result.normal();

    return result;
}

Seven Seven::operator-(const Seven &other) const{
    Seven result;
    result._digits = allocate_memory(get_size());
    result._size = get_size();
    size_t pre_result{0};

    for(size_t i{0}; i < _size; ++i){
        unsigned char digit_1 = get_digits()[get_size() - i - 1] - '0';
        unsigned char digit_2 = (i < other.get_size()) ? other.get_digits()[other.get_size() - i - 1] - '0': 0;
        int diff = digit_1 - digit_2 - pre_result;

        if(diff < 0){
            diff += 7;
            pre_result = 1;
        }
        else pre_result = 0;

        result.get_digits()[get_size() - i - 1]  = diff + '0';  
    }

    result.normal();

    return result;
}

bool Seven::operator<(const Seven &other) const{
    if (get_size() != other.get_size()){
        return get_size() < other.get_size();
    }
    for(size_t i{0}; i < get_size(); ++i){
        if (get_digits()[i] != other.get_digits()[i]){
            return get_digits()[i] < other.get_digits()[i];
        }
    }
    return false;
}

bool Seven::operator>(const Seven &other) const{
    return other < *this;
}

bool Seven::operator==(const Seven &other) const {
    if (get_size() != other.get_size()) return false;
    for (size_t i = 0; i < get_size(); ++i)
        if (get_digits()[i] != other.get_digits()[i]) 
            return false;
    return true;
}

Seven& Seven::operator=(const Seven& other){
    if (this == &other) return *this;
    delete[] _digits;

    _size = other.get_size();
    _digits = new unsigned char[_size];
    std::copy(other._digits, other._digits + _size, _digits);

    return *this;
}

std::ostream& operator<<(std::ostream &os, const Seven& s){
    for (size_t i{0}; i < s.get_size(); ++i)
        os << s.get_digits()[i];
    return os;
}
