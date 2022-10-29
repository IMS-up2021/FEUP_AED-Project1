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

bool Slot::operator<(Slot outro) const {
    if(this->day<outro.getDay()) return true;
    if(this->day==outro.getDay()){
        if(this->start<outro.getStart()) return true;
    }
    return false;
}

