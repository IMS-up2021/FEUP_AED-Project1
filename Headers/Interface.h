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
    static bool slotsGreaterthan(const pair<string ,Slot> &aula1,const pair<string ,Slot> &aula2);
    static bool slotsLessthan1(const pair<pair<string,string>,Slot> &aula1, const pair<pair<string,string>,Slot> &aula2);
    static bool slotsGreaterthan1(const pair<pair<string,string>,Slot> &aula1,const pair<pair<string,string>,Slot> &aula2);
    static bool slotsLessthan2(const pair<string ,Slot> &aula1,const pair<string ,Slot> &aula2);
    bool is_number(string n) const;


public:
    void addProcessToQueue(string process);//adds a process to the queue with the name p_name
    int listShow();//executes the listing
    int initiate();
    Interface(CSVReader& reader);

};


#endif //UNTITLED1_PROCESSINGTOOL_H
