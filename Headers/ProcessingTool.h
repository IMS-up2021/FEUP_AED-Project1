//
// Created by not_real_fu on 22-10-2022.
//

#ifndef UNTITLED1_PROCESSINGTOOL_H
#define UNTITLED1_PROCESSINGTOOL_H
#include <queue>
#include <string>
#include <set>
#include"CSVReader.h"

using namespace std;
class ProcessingTool {
private:
    queue<string> processes;
    set<string> commands={"listagem"};
    CSVReader database_;
public:
    void addProcess(string process);//adds a process to the queue with the name p_name
    int executeProcess();//executes processes in the queue
    int initiate();

};


#endif //UNTITLED1_PROCESSINGTOOL_H
