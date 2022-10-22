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
public:
    UCTurma(string uc, string turma);
    bool operator<(UCTurma other) const;
    pair<string,string> get_uc_turma() const;
    void add_slot(Slot slot);
};

#endif //UNTITLED1_UCTURMA_H
