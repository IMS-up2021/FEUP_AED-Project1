//
// Created by Afonso on 30/10/2022.
//

#include "../Headers/RequestProcesser.h"
#include <algorithm>

/**
 * Adds list of requests to queue \n
 * Complexity: O(1)
 * @param requests list of requests to add
 */
void RequestProcesser::add_request_list(list<Request> requests) {
    request_blocks.push(requests);
}

/**
 * Processes next list of requests in queue \n
 * Complexity: O(nlog(m)qlog(p)) (n = numner of requests, m = size of student BST, q = number of UCTurmas in student, p = size of affected_uc)
 * @return 0 if success, 1 otherwise
 */
int RequestProcesser::process_next_request_block() {
    new_students = database->getStudents();
    list<Request> block = request_blocks.front();
    request_blocks.pop();
    for (const Request& request : block) {
        string type = request.get_type();
        bool b;
        if (type == "add") b = true;
        else b = false;
        unsigned target_student = request.get_target_student();
        pair<string, string> uc_turma = request.get_uc_turma();
        auto it = new_students.find(Student(target_student));
        if (it == new_students.end()) return 1;
        affected_students.insert((*it).get_num());
        if (uc_turma.first.empty()) {
            list<UCTurma*> l = (*it).get_timetable();
            auto s_it = l.begin();
            while (s_it != l.end()) {
                if ((*s_it)->get_uc_turma().second == uc_turma.second) {
                    affected_uc.insert((*s_it)->get_uc_turma().first);
                    (*s_it)->create_temp_num();
                    (*s_it)->add_remove_student(false);
                    s_it = l.erase(s_it);
                }
                else s_it++;
            }
            (*it).set_timetable(l);
        }
        else if (uc_turma.second.empty()) {
            list<UCTurma*> l = (*it).get_timetable();
            auto s_it = l.begin();
            while (s_it != l.end()) {
                if ((*s_it)->get_uc_turma().first == uc_turma.first) {
                    affected_uc.insert(uc_turma.first);
                    (*s_it)->create_temp_num();
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
                (*search).create_temp_num();
                (*it).add_uc_turma_pointer(search);
            }
            else {
                list<UCTurma*> l = (*it).get_timetable();
                auto s_it = l.begin();
                while (s_it != l.end()) {
                    if ((*s_it)->get_uc_turma() == uc_turma) {
                        affected_uc.insert(uc_turma.first);
                        (*s_it)->create_temp_num();
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

/**
 * Checks for conflicts. To be called after processing a request block \n
 * Complexity: O(mnklog(nk)) (m = size of affected_students, n = number of UCTurmas in student, k = number of slots per UCTurma)
 * @return 0 if no conflicts, 1 if student timetable superposition, 2 if UC imbalance (1 has priority over 2)
 */
int RequestProcesser::check_for_problems() {
    for (unsigned num : affected_students) {
        auto it = new_students.find(Student(num));
        if ((*it).timetable_has_conflict()) return 1;
    }
    for (string uc : affected_uc) {
        if (!database->is_balanced(uc)) return 2;
    }
    return 0;
}

/**
 * Saves changes made in requests processed since last call to save_changes() or discard_changes() \n
 * Complexity: O(nk) (n = size of affected_uc, k = number of turmas per UC)
 */
void RequestProcesser::save_changes() {
    database->set_students(new_students);
    for (const string& uc : affected_uc) {
        database->save_uc_changes(uc);
    }
    new_students.clear();
    affected_uc.clear();
    affected_students.clear();
}

/**
 * Discards changes made in requests processed since last call to save_changes() or discard_changes() \n
 * Complexity: O(nk) (n = size of affected_uc, k = number of turmas per UC)
 */
void RequestProcesser::discard_changes() {
    for (const string& uc : affected_uc) {
        database->discard_uc_changes(uc);
    }
    new_students.clear();
    affected_uc.clear();
    affected_students.clear();
}