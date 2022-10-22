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
};

#endif //UNTITLED1_SLOT_H
