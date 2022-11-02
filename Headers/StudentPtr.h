//
// Created by Afonso on 02/11/2022.
//

#ifndef AEDOUTRO_STUDENTPTR_H
#define AEDOUTRO_STUDENTPTR_H

#include "Student.h"

class StudentPtr {
private:
    Student* student;
public:
    StudentPtr(Student* student);
    Student* get_student();
    bool operator<(const StudentPtr& other);
};

#endif //AEDOUTRO_STUDENTPTR_H
