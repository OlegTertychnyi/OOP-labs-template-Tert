#include "../include/execute.h"
#include "../include/stdc++.h"

bool isAfraid(const std::string& day, int number) {
    if (day == "Понедельник" && number == 12) {
        return true;
    } else if (day == "Вторник" && number > 95) {
        return true;
    } else if (day == "Среда" && number == 34) {
        return true;
    } else if (day == "Четверг" && number == 0) {
        return true;
    } else if (day == "Пятница" && number % 2 == 0) {
        return true;
    } else if (day == "Суббота" && number == 56) {
        return true;
    } else if (day == "Воскресенье" && (number == 666 || number == -666)) {
        return true;
    }
    return false;
}
