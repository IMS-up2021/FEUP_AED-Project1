//
// Created by Afonso on 16/10/2022.
//

#ifndef UNTITLED1_CSVREADER_H
#define UNTITLED1_CSVREADER_H

#include "UCTurma.h"
#include "Student.h"
#include <vector>
#include <set>

class CSVReader {
public:
    void read_classes_per_uc();
    void read_classes();
    void read_students_classes();
    int populate();
    const vector<UCTurma> &getUcTurmas() const;

    const set<Student> &getStudents() const;

private:
    vector<UCTurma> uc_turmas;
    set<Student> students;
};

#endif //UNTITLED1_CSVREADER_H
