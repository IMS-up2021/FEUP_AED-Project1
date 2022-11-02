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
 * Adds Slot object to slots belonging to UCTurma \n
 * Complexity: O(1)
 * @param slot Slot to be added
 */
void UCTurma::add_slot(Slot slot) {
    slots.emplace_back(slot);
}

list<Slot> UCTurma::get_slots() const {
    return slots;
}

/**
 * Increments or decrements the UCTurma's student number \n
 * Complexity: O(1)
 * @param b true if increment, false if decrement
 */
void UCTurma::add_remove_student(bool b) {
    /*if (student_num == 0 && !b) return 1;
    else if (student_num == TURMA_CAP && b) return 1;
    else if (b) {student_num++; return 0;}
    else {
        student_num--;
        return 0;
    }*/
    if (b) student_num++;
    else student_num--;
}

int UCTurma::get_student_num() const {
    return student_num;
}

UCTurma::UCTurma(pair<string, string> uc_turma): uc_turma(uc_turma) {
    student_num = 0;
    temp_num = -1;
}

/**
 * Saves current student_num for request processing \n
 * Complexity: O(1)
 */
void UCTurma::create_temp_num() {
    if (temp_num == -1) temp_num = student_num;
}

/**
 * Loads old student_num back in for when request block is invalid \n
 * Complexity: O(1)
 */
void UCTurma::load_temp_num() {
    if (temp_num != -1) student_num = temp_num;
    temp_num = -1;
}

/**
 * Resets temp_num for when request block is valid \n
 * Complexity: O(1)
 */
void UCTurma::reset_temp_num() {
    temp_num = -1;
}

bool UCTurma::student_num_good() const {
    return (student_num >= 0 && student_num <= TURMA_CAP);
}
