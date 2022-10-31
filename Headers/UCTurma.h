//
// Created by Afonso on 20/10/2022.
//

#ifndef UNTITLED1_UCTURMA_H
#define UNTITLED1_UCTURMA_H
#include <string>
#include <list>
#include "Slot.h"

#define TURMA_CAP 30

using namespace std;

class UCTurma {
private:
    pair<string, string> uc_turma;
    list<Slot> slots;
    int student_num;
    int temp_num;
public:
    UCTurma(string uc, string turma);
    UCTurma(pair<string, string> uc_turma);
    bool operator<(UCTurma other) const;
    pair<string,string> get_uc_turma() const;
    void add_slot(Slot slot);
    list<Slot> get_slots() const;
    int add_remove_student(bool b);
    int get_student_num() const;
    void create_temp_num();
    void load_temp_num();
    void reset_temp_num();
};

#endif //UNTITLED1_UCTURMA_H
