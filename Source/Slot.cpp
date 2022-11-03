//
// Created by Afonso on 20/10/2022.
//

#include "../Headers/Slot.h"

/**
 * Construct Slot \n
 * Complexity: O(1)
 * @param start start time
 * @param duration duration
 * @param day day of the week
 * @param type type of slot (T/TP/PL)
 */
Slot::Slot(float start, float duration, std::string day, std::string type): start(start), duration(duration), day(day), type(type) {}

/**
 * Get start of slot \n
 * Complexity: O(1)
 * @return start of slot
 */
float Slot::getStart() const {
    return start;
}

/**
 * Get duration of slot \n
 * Complexity: O(1)
 * @return
 */
float Slot::getDuration() const {
    return duration;
}

/**
 * Get day of week \n
 * Complexity: O(1)
 * @return day of week
 */
const string &Slot::getDay() const {
    return day;
}

/**
 * Get type of slot \n
 * Complexity: O(1)
 * @return type of slot
 */
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

/**
 * Compare two slots by start time and day of week \n
 * @param other Slot to compare to
 * @return true if this<other, false otherwise
 */
bool Slot::operator<(Slot other) const {
    if (day == other.day) {
        return start < other.start;
    }
    else {
        return get_day_num() < other.get_day_num();
    }
}

/**
 * Compare two slots by start time and day of week \n
 * @param other Slot to compare to
 * @return true if this>other, false otherwise
 */
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

/**
 * Get end of slot \n
 * Complexity: O(1)
 * @return end of slot
 */
float Slot::get_end() const {
    return start + duration;
}

