//
// Created by not_real_fu on 22-10-2022.
//

#ifndef UNTITLED1_PROCESSINGTOOL_H
#define UNTITLED1_PROCESSINGTOOL_H
#include <queue>
#include <string>
#include <list>
#include"CSVReader.h"

using namespace std;
class Interface {
private:
    queue<string> processes;
    CSVReader* database;
    bool is_in(string choice,int lim_start,int lim_end) const;
    static bool slotsLessthan(const pair<string,Slot> &aula1,const pair<string ,Slot> &aula2);
    static bool pair_stringLessthan(const pair<string,Slot> &aula1,const pair<string ,Slot> &aula2);
    static bool pair_stringGreaterthan(const pair<string,Slot> &aula1,const pair<string ,Slot> &aula2);
    static bool slotsGreaterthan(const pair<string,Slot> &aula1,const pair<string ,Slot> &aula2);
    static bool turmasLessthan(const UCTurma &ucturma1, const UCTurma &ucturma2);
    static bool turmasGreaterthan(const UCTurma &ucturma1, const UCTurma &ucturma2);
    static bool slotsLessthan1(const pair<pair<string,string>,Slot> &aula1, const pair<pair<string,string>,Slot> &aula2);
    static bool ucLessthan(const UCTurma &ucturma1, const UCTurma &ucturma2);
    static bool ucGreaterthan(const UCTurma &ucturma1, const UCTurma &ucturma2);
    static bool ucLessthan1(const UCTurma* ucturma1, const UCTurma* ucturma2);
    static bool ucGreaterthan1(const UCTurma* ucturma1, const UCTurma* ucturma2);
    static bool stringGreaterthan(const string s1,const string s2);
    static bool set_compareLessthan_student(const Student &s1,const Student &s2);




    bool is_number(string n) const;


public:
    void addProcessToQueue(string process);//adds a process to the queue with the name p_name
    int initiate();//executes the listing
    Interface(CSVReader& reader);

};


#endif //UNTITLED1_PROCESSINGTOOL_H
