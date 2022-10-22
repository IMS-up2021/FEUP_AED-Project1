//
// Created by Afonso on 20/10/2022.
//
#include "../Headers/UCTurma.h"

UCTurma::UCTurma(string uc, string turma) {
    uc_turma = {uc,turma};
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