//
// Created by Afonso on 16/10/2022.
//

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../Headers/CSVReader.h"
#include "../Headers/UCTurma.h"

using namespace std;

/**
 * Checks if file exists
 * @param name Name of file to test
 * @return true if file exists, false otherwise
 */
bool exists_test0 (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

/**
 * Loads values from classes_per_uc.csv into a vector of UCTurma objects
 */
void CSVReader::read_classes_per_uc() {
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
    while (getline(in, line)) {
        istringstream iss(line);
        getline(iss, uc, ',');
        getline(iss, turma, ',');
        uc_turmas.emplace_back(uc, turma);
    }
    in.close();
}

/**
 * Searches a pair of strings <uc,turma> in a vector of UCTurma objects
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
 * Loads values from classes.csv into the UCTurma vector belonging to the CSVReader object
 */
void CSVReader::read_classes() {
    ifstream in("Input/classes.csv");
    string line, type, turma, uc, s_start, s_duration, day;
    float start, duration;
    pair<string, string> uc_turma;
    int search;
    getline(in, line);
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
}

/**
 * Creates the set of students with the info on students_classes.csv
 */
void CSVReader::read_students_classes() {
    ifstream in("Input/students_classes.csv");
    string s_num, name, uc, turma, line;
    pair<string,string> uc_turma;
    unsigned num;
    unsigned curr = 0;
    Student curr_student;
    getline(in, line);
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
}

/**
 * Populates the data structures with the info from classes.csv, classes_per_uc.csv and students_classes.csv
 * @return 1 if success, 0 otherwise
 */
int CSVReader::populate() {
    read_classes_per_uc();
    sort(uc_turmas.begin(), uc_turmas.end());
    read_classes();
    read_students_classes();
    int search = binarySearch(uc_turmas, {"L.EIC025","3LEIC12"});
    uc_turmas[search].add_slot(Slot(2.0, 1.0, "Tuesday", "T"));
    return 1;
}

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

vector<pair<string, Slot>> CSVReader::get_turma_timetable(string turma) const {
    vector<pair<string, Slot>> ret;
    for (const UCTurma& uc_turma : uc_turmas) {
        if (uc_turma.get_uc_turma().second == turma) {
            for (const Slot& slot : uc_turma.get_slots()) ret.emplace_back(uc_turma.get_uc_turma().first, slot);
        }
    }
    return ret;
}
