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
    int read_classes_per_uc();
    int read_classes();
    int read_students_classes();
    bool populate();
    list<UCTurma*> get_student_timetable(unsigned num) const;
    vector<pair<string,Slot>> get_uc_timetable(string uc) const;
    vector<pair<string,Slot>> get_turma_timetable(string turma) const;
    int get_studentnum_per_uc(string uc) const;
    const vector<UCTurma> &getUcTurmas() const;
    UCTurma* get_pointer_to_uc_turma(pair<string, string> uc_turma);
    const set<Student> &getStudents() const;
    void save_uc_changes(string uc);
    void discard_uc_changes(string uc);
    bool is_balanced(string uc) const;
    unsigned find_student_num_by_name(string name) const;
    Student get_student_by_num(unsigned num) const;
    void set_students(set<Student> s);

private:
    vector<UCTurma> uc_turmas;
    set<Student> students;
};

#endif //UNTITLED1_CSVREADER_H

