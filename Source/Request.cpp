//
// Created by Afonso on 30/10/2022.
//

#include "../Headers/Request.h"

/**
 * Construct Request \n
 * Complexity: O(1)
 * @param type "add" or "remove" according to request
 * @param target_student number of target student
 * @param uc target UC
 * @param turma target turma
 */
Request::Request(std::string type, unsigned int target_student, std::string uc, std::string turma): type(type), target_student(target_student) {
    uc_turma = {uc, turma};
}

/**
 * Get request type \n
 * Complexity: O(1)
 * @return type of request
 */
string Request::get_type() const {
    return type;
}

/**
 * Get target student number \n
 * Complexity: O(1)
 * @return target student number
 */
unsigned Request::get_target_student() const {
    return target_student;
}

/**
 * Get string pair <uc,turma> of the request \n
 * Complexity: O(1)
 * @return string pair <uc,turma>
 */
pair<string, string> Request::get_uc_turma() const {
    return uc_turma;
}
