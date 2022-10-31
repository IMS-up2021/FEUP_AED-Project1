//
// Created by Afonso on 30/10/2022.
//

#include "../Headers/RequestProcesser.h"
#include <algorithm>

void RequestProcesser::add_request_list(list<Request> requests) {
    request_blocks.push(requests);
}

int RequestProcesser::process_next_request_block() {
    set<Student> new_students = database->getStudents();
    list<Request> block = request_blocks.front();
    request_blocks.pop();
    set<string> affected_uc;
    set<Student> affected_students;
    for (Request request : block) {
        string type = request.get_type();
        bool b;
        if (type == "add") b = true;
        else b = false;
        unsigned target_student = request.get_target_student();
        pair<string, string> uc_turma = request.get_uc_turma();
        auto it = new_students.find(Student(target_student));
        if (it == new_students.end()) return 1;
        affected_students.insert((*it));
        if (uc_turma.first == "") {
            list<UCTurma*> l = (*it).get_timetable();
            auto s_it = l.begin();
            while (s_it != l.end()) {
                if ((*s_it)->get_uc_turma().second == uc_turma.second) {
                    affected_uc.insert((*s_it)->get_uc_turma().first);
                    (*s_it)->add_remove_student(false);
                    s_it = l.erase(s_it);
                }
                else s_it++;
            }
            (*it).set_timetable(l);
        }
        else if (uc_turma.second == "") {
            list<UCTurma*> l = (*it).get_timetable();
            auto s_it = l.begin();
            while (s_it != l.end()) {
                if ((*s_it)->get_uc_turma().first == uc_turma.first) {
                    affected_uc.insert(uc_turma.first);
                    (*s_it)->add_remove_student(false);
                    l.erase(s_it);
                    (*it).set_timetable(l);
                    break;
                }
            }
        }
        else {
            if (b) {
                UCTurma* search = database->get_pointer_to_uc_turma(uc_turma);
                if (search == nullptr) return 1;
                affected_uc.insert(uc_turma.first);
                (*it).add_uc_turma_pointer(search);
            }
            else {
                list<UCTurma*> l = (*it).get_timetable();
                auto s_it = l.begin();
                while (s_it != l.end()) {
                    if ((*s_it)->get_uc_turma() == uc_turma) {
                        affected_uc.insert(uc_turma.first);
                        (*s_it)->add_remove_student(false);
                        l.erase(s_it);
                        (*it).set_timetable(l);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

RequestProcesser::RequestProcesser(CSVReader &reader): database(&reader) {}
