//
// Created by Afonso on 20/10/2022.
//
#include "../Headers/UCTurma.h"

/**
 * Construct UCTurma \n
 * Complexity: O(1)
 * @param uc desired UC
 * @param turma desired turma
 */
UCTurma::UCTurma(string uc, string turma) {
    uc_turma = {uc,turma};
    student_num = 0;
    temp_num = -1;
}

/**
 * Compare two UCTurmas by UC then by turma \n
 * Complexity: O(1)
 * @param other UCTurma to compare to
 * @return true if this<other, false otherwise
 */
bool UCTurma::operator<(UCTurma other) const {
    return uc_turma < other.uc_turma;
}

/**
 * Get string pair <uc,turma> corresponding to UCTurma \n
 * Complexity: O(1)
 * @return string pair <uc,turma>
 */
pair<string, string> UCTurma::get_uc_turma() const {return uc_turma;}

/**
 * Adds Slot object to slots belonging to UCTurma \n
 * Complexity: O(1)
 * @param slot Slot to be added
 */
void UCTurma::add_slot(Slot slot) {
    slots.emplace_back(slot);
}

/**
 * Get UCTurma's list of slots \n
 * Complexity: O(n) (n = number of slots)
 * @return list of slots
 */
list<Slot> UCTurma::get_slots() const {
    return slots;
}

/**
 * Increments or decrements UCTurma's student num
 * @param b true for increment, false for decrement
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

/**
 * Get number of students in UCTurma \n
 * Complexity: O(1)
 * @return number of students
 */
int UCTurma::get_student_num() const {
    return student_num;
}

/**
 * Construct UCTurma by string pair <uc,turma> \n
 * Complexity: O(1)
 * @param uc_turma string pair <uc,turma>
 */
UCTurma::UCTurma(const pair<string, string>& uc_turma): uc_turma(uc_turma) {
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

/**
 * Checks if number of students is within acceptable boundaries \n
 * Complexity: O(1)
 * @return true if good, false otherwise
 */
bool UCTurma::student_num_good() const {
    return (student_num >= 0 && student_num <= TURMA_CAP);
}
