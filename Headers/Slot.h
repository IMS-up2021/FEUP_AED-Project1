//
// Created by Afonso on 20/10/2022.
//

#ifndef UNTITLED1_SLOT_H
#define UNTITLED1_SLOT_H
#include <string>

using namespace std;

class Slot {
private:
    float start;
    float duration;
    string day;
    string type;
public:
    Slot(float start, float duration, string day, string type);

    float getStart() const;

    float getDuration() const;

    const string &getDay() const;

    const string &getType() const;
    bool operator< (Slot aula) const;
    bool operator> (Slot aula) const;
    int get_day_num() const;
    float get_end() const;

};

#endif //UNTITLED1_SLOT_H
