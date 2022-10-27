//
// Created by not_real_fu on 22-10-2022.


#include "../Headers/ProcessingTool.h"
#include <iostream>
#include <set>
/** Função que verifica se as opções estão dentro dos possíveis
 *
 * @param choice user's input
 * @param lim_start where the range of possible values starts(inclusive)
 * @param lim_end where the range of possible values ends(inclusive)
 * @return boolean value true/false
 */
bool ProcessingTool::is_in(int choice, int lim_start, int lim_end) const{
    if(choice>=lim_start && choice <=lim_end) return true;
    return false;
}

/** Executes a process introduced by user input
 *
 * @param string process
 * @return 0 if no quit, 1 if quit mid process
 */
int ProcessingTool::listShow(int choice) {

    if(!is_in(choice,1,2)){
        cout<<"Sintaxe errada.\nPor favor, reintroduzir:"<<endl;
    }
    if(choice==1){
        int subprocess,critério,modo,ano,escolha;
        cout<<"Introduza o numero do modo de listagem:\n\t1.Listagem das turmas\n\t2.Listagem das unidades curriculares\n\t3.Listagem dos alunos"<<endl;
        cin>>subprocess;
        if(subprocess==0) return 1;
        while(!is_in(subprocess,1,3)){
            cout<<"Sintaxe errada.\nPor favor, reintroduzir:"<<endl;
            cin>>subprocess;
        }
        if(subprocess==1){
            cout<<"Introduza modo de listagem:\n  1-Parcial\n  2-Total:"<<endl;
            cin>>modo;
            if (modo==0) return 1;
            while(!(is_in(modo,1,2))){
                cout<<"Sintaxe errada.\nPor favor, reintroduzir:"<<endl;
                cin>>modo;
            }
            if(modo==1){
                cout<<"Do ano:"<<endl;
                cin>>ano;
                if (ano=0) return 1;
                while( !is_in(ano,1,3)){
                    cout<<"Sintase errada.\nPor favor, reintroduzir:"<<endl;
                    cin>>ano;
                    }
                }
                if(ano==1){
                    cout<<"ainda a ser implementado"<<endl;
                    }
                }
                if (ano==2) {
                    cout<<"ainda a ser implementada"<<endl;
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
