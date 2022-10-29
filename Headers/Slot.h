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

};

#endif //UNTITLED1_SLOT_H
