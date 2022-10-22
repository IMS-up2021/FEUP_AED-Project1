//
// Created by not_real_fu on 22-10-2022.


#include "../Headers/ProcessingTool.h"
#include <iostream>
#include <set>

bool ProcessingTool::is_in(std::string process, vector<std::string> v) const{
    for (string p:v){
        if(process==p){
            return true;
        }
    }
    return false;
}

/** Executes a process introduced by user input
 *
 * @param string process
 * @return 0 if no quit, 1 if quit mid process
 */
int ProcessingTool::executeProcess( string process) {

    if(!is_in(process,commands)){
        cout<<"Syntaxe errada"<<endl;
    }
    if(process=="listagem"){
        string subprocess, critério,modo,ano,escolha;


        vector<string>availableSubprocess={"1","2","3","0"};
        cout<<"Introduza o numero do modo de listagem:\n  1-listagem das turmas\n  2-listagem das unidades curriculares\n  3-listagem dos alunos"<<endl;
        cin>>subprocess;
        if(subprocess=="0") return 1;
        while(!is_in(subprocess,availableSubprocess)){
            cout<<"syntaxe Errada"<<endl;
            cin>>subprocess;
        }
        if(subprocess=="1"){
            cout<<"Introduza modo de listagem:\n  1-parcial\n  2-total:"<<endl;
            cin>>modo;
            while(!(modo=="1" || modo =="2")){
                cout<<"Sintaxe Errada"<<endl;
                cin>>modo;
            }
            if(modo=="1"){
                cout<<"Do ano:"<<endl;

                cin>>ano;
                while(stoi(ano)>5 || stoi(ano)<1){
                    cout<<"sintase errada"<<endl;
                    cin>>ano;
                    }
                }
                if(stoi(ano)==1){
                    for(UCTurma turma:database.getUcTurmas()){
                        cout<<turma.get_uc_turma().second<<endl;
                    }
                }
            }
        }





}
int ProcessingTool::initiate() {
    if(!database.populate()){
        return 0;
    }
    this->database.populate();
    return 1;
}
