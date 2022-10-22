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

bool exists_test0 (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

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

void CSVReader::delete_data() {
    string turmas = "turmas.csv";
    ifstream in(turmas);
    string line;
    while (getline(in,line)) {
        line += ".csv";
        remove(line.c_str());
    }
}

void CSVReader::delete_classes() {
    const char* name = "turmas.csv";
    remove(name);
}

int CSVReader::populate() {
    read_classes_per_uc();
    sort(uc_turmas.begin(), uc_turmas.end());
    read_classes();
    read_students_classes();
    int search = binarySearch(uc_turmas, {"L.EIC025","3LEIC12"});
    uc_turmas[search].add_slot(Slot(2.0, 1.0, "Tuesday", "T"));
    return 1;
}