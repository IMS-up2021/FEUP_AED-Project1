//
// Created by Afonso on 16/10/2022.
//

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../Headers/CSVReader.h"

using namespace std;

/**
 * Loads values from classes_per_uc.csv into a vector of UCTurma objects \n
 * Complexity: O(n) (n = number of lines)
 */
int CSVReader::read_classes_per_uc() {
/*    ifstream in("Input/classes_per_uc.csv");
    ofstream out;
    out.open("turmas.csv", ios_base::app);
    ofstream curr;
    string line, uc, group;
    getline(in, line);
    while (getline(in, line)){
        istringstream iss(line);
        getline(iss, uc, ',');
        getline(iss, group, ',');
        if (!exists_test0( group + ".csv")) {
            out << group << '\n';
        }
        curr.open(group + ".csv", ios_base::app);
        bool bool1 = curr.is_open();
        curr << uc << '\n';
        curr.close();
    }*/
    ifstream in("Input/classes_per_uc.csv");
    string line, uc, turma;
    getline(in, line);
    if (line != "UcCode,ClassCode") return 1;
    while (getline(in, line)) {
        istringstream iss(line);
        getline(iss, uc, ',');
        getline(iss, turma, ',');
        uc_turmas.emplace_back(uc, turma);
    }
    in.close();
    return 0;
}

/**
 * Searches a pair of strings <uc,turma> in a vector of UCTurma objects \n
 * Complexity: O(log(n)) (n = size of vector)
 * @param uc_turmas Vector of UCTurma objects to look in
 * @param uc_turma Pair of strings to find
 * @return Index of element with desired pair, -1 otherwise
 */
int binarySearch(const vector<UCTurma>& uc_turmas, pair<string, string> uc_turma) {
    int low = 0;
    int high = uc_turmas.size();
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (uc_turmas[mid].get_uc_turma() == uc_turma)
            return mid;
        if (uc_turmas[mid].get_uc_turma() < uc_turma)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

/**
 * Loads values from classes.csv into the UCTurma vector belonging to the CSVReader object \n
 * Complexity: O(nlog(m)) (n = number of lines, m = size of uc_turmas vector)
 */
int CSVReader::read_classes() {
    ifstream in("Input/classes.csv");
    string line, type, turma, uc, s_start, s_duration, day;
    float start, duration;
    pair<string, string> uc_turma;
    int search;
    getline(in, line);
    if (line != "ClassCode,UcCode,Weekday,StartHour,Duration,Type") return 1;
    while (getline(in,line)) {
        istringstream iss(line);
        getline(iss, turma, ',');
        getline(iss, uc, ',');
        getline(iss, day, ',');
        getline(iss, s_start, ',');
        getline(iss, s_duration, ',');
        getline(iss, type, ',');
        start = stof(s_start);
        duration = stof(s_duration);
        uc_turma = {uc, turma};
        search = binarySearch(uc_turmas, uc_turma);
        uc_turmas[search].add_slot(Slot(start,duration,day,type));
    }
    in.close();
    return 0;
}

/**
 * Creates the set of students with the info on students_classes.csv \n
 * Complexity: O(nlog(m)log(k)) (n = number of lines, m = size of uc_turmas vector, k = size of student BST)
 */
int CSVReader::read_students_classes() {
    ifstream in("Input/students_classes.csv");
    string s_num, name, uc, turma, line;
    pair<string,string> uc_turma;
    unsigned num;
    unsigned curr = 0;
    Student curr_student;
    getline(in, line);
    if (line != "StudentCode,StudentName,UcCode,ClassCode" && line != "﻿StudentCode,StudentName,UcCode,ClassCode") return 1;
    while (getline(in, line)) {
        istringstream iss(line);
        getline(iss, s_num, ',');
        getline(iss, name, ',');
        getline(iss, uc, ',');
        getline(iss, turma, ',');
        num = stoi(s_num);
        if (curr == 0) {
            curr_student = Student(name, num);
            int search = binarySearch(uc_turmas, {uc, turma});
            curr_student.add_uc_turma(uc_turmas[search]);
            curr = num;
        }
        else if (curr != num) {
            students.insert(curr_student);
            curr_student = Student(name, num);
            int search = binarySearch(uc_turmas, {uc, turma});
            curr_student.add_uc_turma(uc_turmas[search]);
            curr = num;
        }
        else {
            int search = binarySearch(uc_turmas, {uc, turma});
            curr_student.add_uc_turma(uc_turmas[search]);
        }
    }
    return 0;
}

/**
 * Populates the data structures with the info from classes.csv, classes_per_uc.csv and students_classes.csv \n
 * Complexity: O(nlog(n)) (n = size of uc_turmas vector) plus one call to read_classes_per_uc(), read_classes() and read_students_classes() each
 * @return 0 if success, 1 otherwise
 */
bool CSVReader::populate() {
    int read1 = read_classes_per_uc();
    sort(uc_turmas.begin(), uc_turmas.end());
    int read2 = read_classes();
    int read3 = read_students_classes();
    return (read1 == 0 && read2 == 0 && read3 == 0);
}

/**
 * Get student's timetable \n
 * Complexity: O(log(n)) (n = size of students BST)
 * @param num number of student
 * @return UCTurmas student is in
 */
list<UCTurma*> CSVReader::get_student_timetable(unsigned num) const {
    Student target = Student(num);
    auto it = students.find(target);
    list<UCTurma*> timetable = (*it).get_timetable();
    return timetable;
}

const vector<UCTurma> &CSVReader::getUcTurmas() const {
    return uc_turmas;
}

const set<Student> &CSVReader::getStudents() const {
    return students;
}

/**
 * Obtain timetable for a given UC \n
 * Complexity: O(log(n) + km) (n = size of uc_turmas vector, k = number of turmas in UC, m = number of slots in UCTurma)
 * @param uc UC to check
 * @return vector of pairs containing the slot's turma and the slot itself
 */
vector<pair<string, Slot>> CSVReader::get_uc_timetable(string uc) const {
    UCTurma target = UCTurma(uc, "");
    auto it = lower_bound(uc_turmas.begin(), uc_turmas.end(), target);
    vector<pair<string, Slot>> ret;
    while ((*it).get_uc_turma().first == uc) {
        for (const Slot& slot : (*it).get_slots()) ret.emplace_back((*it).get_uc_turma().second,slot);
        it++;
    }
    return ret;
}

/**
 * Obtain number of students enrolled in a given UC \n
 * Complexity: O(log(n) + k) (n = size of uc_turmas vector, k = number of turmas in UC)
 * @param uc UC to check
 * @return number of students in UC
 */
int CSVReader::get_studentnum_per_uc(string uc) const {
    UCTurma target = UCTurma(uc, "");
    int ret = 0;
    auto it = lower_bound(uc_turmas.begin(), uc_turmas.end(), target);
    while ((*it).get_uc_turma().first == uc) {
        ret += (*it).get_student_num();
        it++;
    }
    return ret;
}

/**
 * Obtain timetable for a given turma \n
 * Complexity: O(nk) (n = size of uc_turmas vector, k = number of slots in UCTurma)
 * @param turma turma whose timetable to get
 * @return vector of pairs containing the slot's UC and the slot itself
 */
vector<pair<string, Slot>> CSVReader::get_turma_timetable(string turma) const {
    vector<pair<string, Slot>> ret;
    for (const UCTurma& uc_turma : uc_turmas) {
        if (uc_turma.get_uc_turma().second == turma) {
            for (const Slot& slot : uc_turma.get_slots()) ret.emplace_back(uc_turma.get_uc_turma().first, slot);
        }
    }
    return ret;
}

/**
 * Checks if a given UC is balanced \n
 * Complexity: O(log(n) + k) (n = size of uc_turmas vector, k = number of turmas in UC)
 * @param uc UC to check
 * @return true if balanced, false otherwise
 */
bool CSVReader::is_balanced(string uc) const {
    UCTurma target = UCTurma(uc, "");
    int min = INT32_MAX;
    int max = INT32_MIN;
    int curr;
    auto it = lower_bound(uc_turmas.begin(), uc_turmas.end(), target);
    while ((*it).get_uc_turma().first == uc) {
        curr = (*it).get_student_num();
        if (curr > max) max = curr;
        if (curr < min) min = curr;
        it++;
    }
    return (max-min) < 4;
}

/**
 * Finds number of student by their name \n
 * Complexity: O(n) (n = size of students BST)
 * @param name name of student to find
 * @return number of student
 */
unsigned CSVReader::find_student_num_by_name(string name) const {
    for (const Student& student : students) {
        if (student.get_name() == name) return student.get_num();
    }
    return 1;
}

/**
 * Obtain pointer to desired UCTurma \n
 * Complexity: O(log(n)) (n = size of uc_turmas vector)
 * @param uc_turma name of UCTurma to look for
 * @return pointer to uc_turma
 */
UCTurma *CSVReader::get_pointer_to_uc_turma(const pair<string, string>& uc_turma) {
    int search = binarySearch(uc_turmas, uc_turma);
    if (search == -1) return nullptr;
    else return &uc_turmas[search];
}


void CSVReader::set_students(set<Student> s) {
    students = s;
}

/**
 * Save changes made to uc in processed requests \n
 * Complexity: O(log(n) + k) (n = size of uc_turmas vector, k = number of turmas in UC)
 * @param uc uc to alter
 */
void CSVReader::save_uc_changes(string uc) {
    auto it = lower_bound(uc_turmas.begin(), uc_turmas.end(), UCTurma(uc,""));
    while ((*it).get_uc_turma().first == uc) {
        (*it).reset_temp_num();
        it++;
    }
}

/**
 * Discard changes made to uc in processed requests \n
 * Complexity: O(log(n) + k) (n = size of uc_turmas vector, k = number of turmas in UC)
 * @param uc uc to restore
 */
void CSVReader::discard_uc_changes(string uc) {
    auto it = lower_bound(uc_turmas.begin(), uc_turmas.end(), UCTurma(uc,""));
    while ((*it).get_uc_turma().first == uc) {
        (*it).load_temp_num();
        it++;
    }
}

/**
 * Get Student by their number
 * Complexity: O(log(n)) (n = size of students BST)
 * @param num number to find
 * @return empty student if not found, desired Student otherwise
 */
Student CSVReader::get_student_by_num(unsigned int num) const {
    auto it = students.find(Student(num));
    if (it == students.end()) return Student(0);
    else return (*it);
}

/**
 * Saves current student database to students_classes.csv
 * Complexity: O(nk) (n = number of students, k = number of UCTurma per student)
 */
void CSVReader::write_students_to_file() const {
    ofstream ofs;
    ofs.open("Input/students_classes.csv");
    ofs << "StudentCode,StudentName,UcCode,ClassCode" << '\n';
    unsigned num;
    string name;
    pair<string,string> code_uc_turma;
    for (const Student& student : students) {
        num = student.get_num();
        name = student.get_name();
        for (UCTurma* uc_turma : student.getUcTurmas()) {
            code_uc_turma = uc_turma->get_uc_turma();
            ofs << num << ',' << name << ',' << code_uc_turma.first << ',' << code_uc_turma.second << '\n';
        }
    }
}

bool CSVReader::is_uc_turma_student_num_good(const pair<string, string> &uc_turma) {
    int search = binarySearch(uc_turmas, uc_turma);
    if (search == -1) return true;
    return uc_turmas[search].student_num_good();
}

void CSVReader::insert_student(Student student) {
    auto it = students.find(student);
    students.erase(it);
    students.insert(student);
}
