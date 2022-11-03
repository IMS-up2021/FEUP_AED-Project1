//
// Created by Afonso on 30/10/2022.
//

#include "../Headers/RequestProcesser.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <filesystem>

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
 * Complexity: O(n(log(p) + log(m)qlog(k))) (n = number of requests, p = size of new_students, m = size of students BST, q = number of UCTurmas in student, k = size of affected_uc_turma)
 * @return 0 if success, 1 otherwise
 */
int RequestProcesser::process_next_request_block() {
    list<Request> block = request_blocks.front();
    request_blocks.pop();
    for (const Request& request : block) {
        string type = request.get_type();
        bool b;
        if (type == "add") b = true;
        else b = false;
        unsigned target_student = request.get_target_student();
        pair<string, string> uc_turma = request.get_uc_turma();
        Student student_search = database->get_student_by_num(target_student);
        if (student_search.get_num() == 0) return 1;
        auto it = new_students.insert(student_search);
        if (uc_turma.first.empty()) {
            list<UCTurma*> l = (*it.first).get_timetable();
            auto s_it = l.begin();
            while (s_it != l.end()) {
                if ((*s_it)->get_uc_turma().second == uc_turma.second) {
                    affected_uc_turma.emplace((*s_it)->get_uc_turma().first, (*s_it)->get_uc_turma().second);
                    (*s_it)->create_temp_num();
                    (*s_it)->add_remove_student(false);
                    s_it = l.erase(s_it);
                }
                else s_it++;
            }
            (*it.first).set_timetable(l);
        }
        else if (uc_turma.second.empty()) {
            list<UCTurma*> l = (*it.first).get_timetable();
            auto s_it = l.begin();
            while (s_it != l.end()) {
                if ((*s_it)->get_uc_turma().first == uc_turma.first) {
                    affected_uc_turma.emplace((*s_it)->get_uc_turma().first, (*s_it)->get_uc_turma().second);
                    (*s_it)->create_temp_num();
                    (*s_it)->add_remove_student(false);
                    l.erase(s_it);
                    (*it.first).set_timetable(l);
                    break;
                }
                else s_it++;
            }
        }
        else {
            if (b) {
                UCTurma* search = database->get_pointer_to_uc_turma(uc_turma);
                if (search == nullptr) return 1;
                affected_uc_turma.insert(uc_turma);
                (*search).create_temp_num();
                (*it.first).add_uc_turma_pointer(search);
                (*search).add_remove_student(true);
            }
            else {
                list<UCTurma*> l = (*it.first).get_timetable();
                auto s_it = l.begin();
                while (s_it != l.end()) {
                    if ((*s_it)->get_uc_turma() == uc_turma) {
                        affected_uc_turma.insert(uc_turma);
                        (*s_it)->create_temp_num();
                        (*s_it)->add_remove_student(false);
                        l.erase(s_it);
                        (*it.first).set_timetable(l);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

/**
 * Construct RequestProcesser \n
 * Complexity: O(1)
 * @param reader CSVReader to draw data from
 */
RequestProcesser::RequestProcesser(CSVReader &reader): database(&reader) {}

/**
 * Checks for conflicts. To be called after processing a request block \n
 * Complexity: O(nF1 + m(log(n) + k)) (n = size of new_students, m = size of affected_uc_turma, n = size of uc_turmas vector, k = number of turmas in UC) \n
 * F1 is complexity of student.timetable_has_conflict(): O(nlog(m) + nklog(nk)) (n = number of UCTurmas in student, k = number of slots per UCTurma, m = size of local uc set)
 * @return 0 if no conflicts, 1 if student timetable superposition or invalid UCTurma student_number, 2 if UC imbalance (1 has priority over 2)
 */
int RequestProcesser::check_for_problems() {
    for (const Student& student : new_students) {
        if (student.timetable_has_conflict()) return 1;
    }
    string curr_uc;
    int ret = 0;
    for (const pair<string,string>& uc_turma : affected_uc_turma) {
        if (curr_uc.empty() || curr_uc != uc_turma.first) {
            if (!database->is_balanced(uc_turma.first)) ret = 2;
            curr_uc = uc_turma.first;
        }
        if (!database->is_uc_turma_student_num_good(uc_turma)) return 1;
    }
    return ret;
}

/**
 * Saves changes made in requests processed since last call to save_changes() or discard_changes() \n
 * Complexity: O(qlog(p) n(log(m) + k) + log(q)) (n = size of affected_uc_turma, m = size of uc_turmas vector, k = number of turmas in UC, q = size of new_students, p = size of students BST)
 */
void RequestProcesser::save_changes() {
    for (const Student& student : new_students) {
        database->insert_student(student);
    }
    string curr_uc;
    for (const pair<string,string>& uc_turma : affected_uc_turma) {
        if (curr_uc.empty() || curr_uc != uc_turma.first) {
            database->save_uc_changes(uc_turma.first);
            curr_uc = uc_turma.first;
        }
    }
    new_students.clear();
    affected_uc_turma.clear();
}

/**
 * Discards changes made in requests processed since last call to save_changes() or discard_changes() \n
 * Complexity: O(n(log(m) + k) + log(q)) (n = size of affected_uc_turma, m = size of uc_turmas vector, k = number of turmas in UC, q = size of new_students)
 */
void RequestProcesser::discard_changes() {
    string curr_uc;
    for (const pair<string,string>& uc_turma : affected_uc_turma) {
        if (curr_uc.empty() || curr_uc != uc_turma.first) {
            database->discard_uc_changes(uc_turma.first);
            curr_uc = uc_turma.first;
        }
    }
    new_students.clear();
    affected_uc_turma.clear();
}

/**
 * Saves unprocessed requests to unprocessed_requests.csv
 * Complexity: O(nk) (n = size of queue, k = number of requests per block)
 */
void RequestProcesser::write_requests_to_file() {
    ofstream ofs;
    list<Request> curr;
    pair<string, string> curr_uc_turma;
    ofs.open("Input/unprocessed_requests.csv");
    ofs << "RequestType,TargetStudent,UC,Turma\n";
    while (!request_blocks.empty()) {
        curr = request_blocks.front();
        request_blocks.pop();
        ofs << "Block\n";
        for (const Request& request : curr) {
            curr_uc_turma = request.get_uc_turma();
            ofs << request.get_type() << ',' << request.get_target_student() << ',' << ((curr_uc_turma.first == "")? "null" : curr_uc_turma.first) << ',' << ((curr_uc_turma.second == "")? "null" : curr_uc_turma.second) << '\n';
        }
    }
}

/**
 * Read unprocessed requests from unprocessed_requests.csv
 * Complexity: O(nk) (n = number of blocks, k = number of requests per block)
 * @return
 */
int RequestProcesser::read_requests_from_file() {
    ifstream ifs;
    ifs.open("Input/unprocessed_requests.csv");
    if (!ifs.is_open()) return 1;
    string line;
    string type, uc, turma, target_s;
    unsigned target_student;
    getline(ifs, line);
    list<Request> curr;
    if (line != "RequestType,TargetStudent,UC,Turma") return 1;
    while (getline(ifs, line)) {
        if (line == "Block") {
            if (!curr.empty()) {
                request_blocks.push(curr);
                curr.clear();
            }
            continue;
        }
        else {
            istringstream iss(line);
            getline(iss, type, ',');
            getline(iss, target_s, ',');
            getline(iss, uc, ',');
            getline(iss, turma, ',');
            if (uc == "null") uc = "";
            if (turma == "null") turma = "";
            curr.emplace_back(type, stoi(target_s), uc, turma);
        }
    }
    if (!curr.empty()) {
        request_blocks.push(curr);
        curr.clear();
    }
    ifs.close();
    filesystem::remove("Input/unprocessed_requests.csv");
    return 0;
}

/**
 * Checks if request queue is empty \n
 * Complexity: O(1)
 * @return true if empty, false otherwise
 */
bool RequestProcesser::queue_empty() const {
    return request_blocks.empty();
}
