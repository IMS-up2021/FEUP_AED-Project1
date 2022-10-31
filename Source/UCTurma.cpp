//
// Created by Afonso on 20/10/2022.
//
#include "../Headers/UCTurma.h"

UCTurma::UCTurma(string uc, string turma) {
    uc_turma = {uc,turma};
    student_num = 0;
}

bool UCTurma::operator<(UCTurma other) const {
    return uc_turma < other.uc_turma;
}

pair<string, string> UCTurma::get_uc_turma() const {return uc_turma;}

/**
 * Adds Slot object to slots belonging to UCTurma
 * @param slot Slot to be added
 */
void UCTurma::add_slot(Slot slot) {
    slots.emplace_back(slot);
}

list<Slot> UCTurma::get_slots() const {
    return slots;
}

int UCTurma::add_remove_student(bool b) {
    if (b) {student_num++; return 0;}
    else if (student_num == 0) return 1;
    else {
        student_num--;
        return 0;
    }
}

int UCTurma::get_student_num() const {
    return student_num;
}

UCTurma::UCTurma(pair<string, string> uc_turma): uc_turma(uc_turma) {
    student_num = 0;
}
