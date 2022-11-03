//
// Created by Afonso on 21/10/2022.
//

#ifndef UNTITLED1_STUDENT_H
#define UNTITLED1_STUDENT_H

#include "UCTurma.h"

class Student {
public:
    Student(string name, unsigned num);
    Student(unsigned num);
    Student();
    void add_uc_turma(UCTurma &uc_turma) const;
    void add_uc_turma_pointer(UCTurma* uc_turma) const;
    bool operator<(Student other) const;
    list<UCTurma*> get_timetable() const;
    void set_timetable(list<UCTurma*> l) const;
    bool timetable_has_conflict() const;
    string get_name() const;
    unsigned get_num() const;
    unsigned get_number_of_uc() const;

    const list<UCTurma *> &getUcTurmas() const;

private:
    mutable list<UCTurma*> uc_turmas;
    string name;
    unsigned num;
};

#endif //UNTITLED1_STUDENT_H
