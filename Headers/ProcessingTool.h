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
class ProcessingTool {
private:
    queue<string> processes;
    vector<string> commands={"listagem"};
    CSVReader database;
    bool is_in(string process,vector<string>v) const;
public:
    void addProcessToQueue(string process);//adds a process to the queue with the name p_name
    int executeProcess(string process);//executes processes in the queue
    int initiate();

};


#endif //UNTITLED1_PROCESSINGTOOL_H
