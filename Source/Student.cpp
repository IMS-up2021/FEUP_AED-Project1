//
// Created by Afonso on 21/10/2022.
//

#include <vector>
#include <algorithm>
#include <set>
#include "../Headers/Student.h"

Student::Student(string name, unsigned num): name(name), num(num) {}

Student::Student() {}

Student::Student(unsigned num): num(num) {}
/**
 * Adds UCTurma to Student via reference \n
 * Complexity: O(1)
 * @param uc_turma UCTurma to be added
 */
void Student::add_uc_turma(UCTurma &uc_turma) const{
    uc_turmas.emplace_back(&uc_turma);
    uc_turma.add_remove_student(true);
}

bool Student::operator<(Student other) const {
    return this->num < other.num;
}

list<UCTurma*> Student::get_timetable() const {
    return uc_turmas;
}

/**
 * Check if the Student has an invalid superposition (TP with PL, TP with TP, PL with PL) and if they have multiple turmas for one UC \n
 * Complexity: O(nklog(nk)) (n = number of UCTurmas in student, k = number of slots per UCTurma)
 * @return true if conflict, false otherwise
 */
bool Student::timetable_has_conflict() const {
    vector<Slot> slots;
    set<string> uc;
    bool has_tp = false;
    bool has_pl = false;
    for (UCTurma* uc_turma : uc_turmas) {
        auto it = uc.insert(uc_turma->get_uc_turma().first);
        if (!it.second) return true;
        for (const Slot& slot : uc_turma->get_slots()) {
            slots.push_back(slot);
        }
    }
    if (slots.size() == 0) return false;
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

string Student::get_name() const {
    return name;
}

unsigned Student::get_num() const {
    return num;
}

void Student::set_timetable(list<UCTurma *> l) const{
    uc_turmas = l;
}

/**
 * Adds UCTurma to Student via pointer, doesn't increment UCTurma's student_num \n
 * Complexity: O(1)
 * @param uc_turma pointer to add
 */
void Student::add_uc_turma_pointer(UCTurma *uc_turma) const {
    uc_turmas.push_back(uc_turma);
}

const list<UCTurma *> &Student::getUcTurmas() const {
    return uc_turmas;
}

