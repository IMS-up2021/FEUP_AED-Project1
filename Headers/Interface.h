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
    CSVReader database;
    bool is_in(string choice,int lim_start,int lim_end) const;
public:
    void addProcessToQueue(string process);//adds a process to the queue with the name p_name
    int listShow(string choice);//executes the listing
    int initiate();

};


#endif //UNTITLED1_PROCESSINGTOOL_H
