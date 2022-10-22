//
// Created by not_real_fu on 22-10-2022.


#include "../Headers/ProcessingTool.h"
#include <iostream>
#include <set>
/** Function used to add user requests to the queue of processes
 *
 * @param string process
 */
void ProcessingTool::addProcess(string process) {
    this->processes.push(process);
}
/** Executes a process introduced by user input
 *
 * @param string process
 * @return 1 if sucessful 0 if not
 */
int ProcessingTool::executeProcess() {
    string currentProcess = processes.front();
    if(commands.find(currentProcess)==commands.end()){
        cout<<"Syntaxe errada"<<endl;
        processes.pop();
    }
    if(currentProcess=="listagem"){
        string subprocess,critério,modo;
        int ano,escolhas;
        set<string>availableSubprocesses={"listagem_das_turmas","listagem_das_unidades","listagen_dos_alunos"};
        cout<<"Introduza o modo de listagem:\n  listagem_das_turmas\n  listagem_das_unidades_curriculares\n  listagem_dos_alunos"<<endl;
        cin>>subprocess;
        if(subprocess=="quit") return 1;
        while(availableSubprocesses.find(subprocess)==availableSubprocesses.end()){
            cout<<"syntaxe Errada"<<endl;
            cin>>subprocess;
        }
        if(subprocess=="listagem_das_turmas"){
            cout<<"Introduza modo de listagem:\n  parcial\n  total:"<<endl;
            cin>>modo;
            while(!(modo=="parcial" || modo =="total")){
                cout<<"Sintaxe Errada"<<endl;
                cin>>modo;
            }
            if(modo=="parcial"){
                cout<<"Do ano:"<<endl;
                cin>>ano;
                while(ano>5 || ano<1){
                    cout<<"sintase errada"<<endl;
                    cin>>ano;
                    }
                }
                if(ano==1){
                    for(UCTurma turma:database_.getUcTurmas()){
                        cout<<turma.get_uc_turma().second<<endl;
                    }
                }
            }
        }





}
int ProcessingTool::initiate() {
    if(!database_.populate()){
        return 0;
    }
    this->database_.populate();
    return 1;
}
