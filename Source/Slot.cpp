//
// Created by Afonso on 20/10/2022.
//

#include "../Headers/Slot.h"

Slot::Slot(float start, float duration, std::string day, std::string type): start(start), duration(duration), day(day), type(type) {}

float Slot::getStart() const {
    return start;
}

float Slot::getDuration() const {
    return duration;
}

const string &Slot::getDay() const {
    return day;
}

const string &Slot::getType() const {
    return type;
}

/*bool Slot::operator<(Slot outro) const {
    if(this->day<outro.getDay()) return true;
    if(this->day==outro.getDay()){
        if(this->start<outro.getStart()) return true;
    }
    return false;
}*/

bool Slot::operator<(Slot other) const {
    if (day == other.day) {
        return start < other.start;
    }
    else {
        return get_day_num() < other.get_day_num();
    }
}
bool Slot::operator>(Slot other ) const {
    if (day == other.day) {
        return start > other.start;
    }
    else {
        return get_day_num() > other.get_day_num();
    }
}

/**
 * Turns the slot's week day into a number (0 for Monday, 1 for Tuesday, etc) \n
 * Complexity: O(1)
 * @return day number
 */
int Slot::get_day_num() const {
    if (day == "Monday") return 0;
    else if (day == "Tuesday") return 1;
    else if (day == "Wednesday") return 2;
    else if (day == "Thursday") return 3;
    else if (day == "Friday") return 4;
    else if (day == "Saturday") return 5;
    else if (day == "Sunday") return 6;
    else return -1;
}

float Slot::get_end() const {
    return start + duration;
}

