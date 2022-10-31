//
// Created by Afonso on 30/10/2022.
//

#include "../Headers/Request.h"

Request::Request(std::string type, unsigned int target_student, std::string uc, std::string turma): type(type), target_student(target_student) {
    uc_turma = {uc, turma};
}

string Request::get_type() const {
    return type;
}

unsigned Request::get_target_student() const {
    return target_student;
}

pair<string, string> Request::get_uc_turma() const {
    return uc_turma;
}
