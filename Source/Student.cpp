//
// Created by Afonso on 21/10/2022.
//

#include <vector>
#include <algorithm>
#include "../Headers/Student.h"

Student::Student(string name, unsigned num): name(name), num(num) {}

Student::Student() {}

Student::Student(unsigned num): num(num) {}
/**
 * Adds UCTurma object to list of UCTurmas belonging to Student
 * @param uc_turma UCTurma to be added
 */
void Student::add_uc_turma(UCTurma &uc_turma) {
    uc_turmas.emplace_back(&uc_turma);
    uc_turma.add_student();
}

bool Student::operator<(Student other) const {
    return this->num > other.num;
}

list<UCTurma*> Student::get_timetable() const {
    return uc_turmas;
}

bool Student::timetable_has_conflict() const {
    vector<Slot> slots;
    bool has_tp = false;
    bool has_pl = false;
    for (UCTurma* uc_turma : uc_turmas) {
        for (const Slot& slot : uc_turma->get_slots()) {
            slots.push_back(slot);
        }
    }
    if (slots.size() == 0) return true;
    sort(slots.begin(), slots.end());
    float end = (slots[0].get_end());
    string day = slots[0].getDay();
    for (unsigned i = 1; i < slots.size(); i++) {
        if (day != slots[i].getDay()) {
            end = slots[i].get_end();
            day = slots[i].getDay();
            has_tp = slots[i].getType() == "TP";
            has_pl = slots[i].getType() == "PL";
        }
        else {
            if (end > slots[i].getStart()) {
                end = slots[i].get_end();
                has_tp = slots[i].getType() == "TP" || has_tp;
                has_pl = slots[i].getType() == "PL" || has_pl;
                if (has_tp && has_pl) {
                    return true;
                }

            }
            else {
                end = slots[i].get_end();
                has_tp = slots[i].getType() == "TP";
                has_pl = slots[i].getType() == "PL";
            }
        }
    }
    return false;
}

