//
// Created by Afonso on 02/11/2022.
//

#include "../Headers/StudentPtr.h"

StudentPtr::StudentPtr(Student* student): student(student) {}

Student *StudentPtr::get_student() {
    return student;
}

bool StudentPtr::operator<(const StudentPtr &other) {
    return student->get_name() < other.student->get_name();
}