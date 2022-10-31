//
// Created by Afonso on 20/10/2022.
//
#include "../Headers/UCTurma.h"

UCTurma::UCTurma(string uc, string turma) {
    uc_turma = {uc,turma};
    student_num = 0;
    temp_num = -1;
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

/**
 * Increments or decrements the UCTurma's student number
 * @param b true if increment, false if decrement
 * @return 1 if failure (decrement when student_num is 0), 0 otherwise
 */
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
    temp_num = -1;
}

/**
 * Saves current student_num for request processing
 */
void UCTurma::create_temp_num() {
    if (temp_num == -1) temp_num = student_num;
}

/**
 * Loads old student_num back in for when request block is invalid
 */
void UCTurma::load_temp_num() {
    if (temp_num != -1) student_num = temp_num;
    temp_num = -1;
}

/**
 * Resets temo_num for when request block is valid
 */
void UCTurma::reset_temp_num() {
    temp_num = -1;
}
