//
// Created by Afonso on 21/10/2022.
//

#include <vector>
#include <algorithm>
#include <set>
#include "../Headers/Student.h"

/**
 * Construct Student \n
 * Complexity: O(1)
 * @param name name of student
 * @param num number of student
 */
Student::Student(string name, unsigned num): name(name), num(num) {}

/**
 * Construct empty Student \n
 * Complexity: O(1)
 */
Student::Student() {}

/**
 * Construct Student only with number
 * @param num number of student
 */
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

/**
 * Compares two students by number \n
 * Complexity: O(1)
 * @param other Student to compare to
 * @return true if this<other, false otherwise
 */
bool Student::operator<(Student other) const {
    return this->num < other.num;
}

/**
 * Get list of student UCTurma pointers \n
 * Complexity: O(n) (n = size of list)
 * @return UCTurma pointer list
 */
list<UCTurma*> Student::get_timetable() const {
    return uc_turmas;
}

/**
 * Check if the Student has an invalid superposition (TP with PL, TP with TP, PL with PL) and if they have multiple turmas for one UC \n
 * Complexity: O(nlog(m) + nklog(nk)) (n = number of UCTurmas in student, k = number of slots per UCTurma, m = size of local uc set)
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

/**
 * Get name of student \n
 * Complexity: O(1)
 * @return name of student
 */
string Student::get_name() const {
    return name;
}

/**
 * Get number of student \n
 * Complexity: O(1)
 * @return number of student
 */
unsigned Student::get_num() const {
    return num;
}

/**
 * Sets student UCTurmas to l \n
 * Complexity: O(n) (n = size of l)
 * @param l new list of UCTurma*
 */
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

/**
 * Return const reference to student UCTurmas \n
 * Complexity: O(1)
 * @return
 */
const list<UCTurma *> &Student::getUcTurmas() const {
    return uc_turmas;
}

/**
 * Return student's number of UCs \n
 * Complexity: O(1)
 * @return
 */
unsigned Student::get_number_of_uc() const {
    return uc_turmas.size();
}

