//
// Created by Afonso on 20/10/2022.
//

#ifndef UNTITLED1_UCTURMA_H
#define UNTITLED1_UCTURMA_H
#include <string>
#include <list>
#include "Slot.h"

using namespace std;

class UCTurma {
private:
    pair<string, string> uc_turma;
    list<Slot> slots;
    int student_num;
public:
    UCTurma(string uc, string turma);
    bool operator<(UCTurma other) const;
    pair<string,string> get_uc_turma() const;
    void add_slot(Slot slot);
    list<Slot> get_slots() const;
    void add_student();
    void remove_student();
    int get_student_num() const;
};

#endif //UNTITLED1_UCTURMA_H
