//
// Created by not_real_fu on 22-10-2022.
//

#ifndef UNTITLED1_PROCESSINGTOOL_H
#define UNTITLED1_PROCESSINGTOOL_H
#include <queue>
#include <string>
using namespace std;
class ProcessingTool {
private:
    queue<string> processes;
public:
    void addProcess(string process);//adds a process to the queue with the name p_name
    void executeProcess(string process);//executes a process in the queue

};


#endif //UNTITLED1_PROCESSINGTOOL_H
