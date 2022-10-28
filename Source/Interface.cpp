//
// Created by not_real_fu on 22-10-2022.


#include "../Headers/Interface.h"
#include <iostream>
#include <set>
/** Função que verifica se as opções estão dentro dos possíveis
 *
 * @param choice user's input
 * @param lim_start where the range of possible values starts(inclusive)
 * @param lim_end where the range of possible values ends(inclusive)
 * @return boolean value true/false
 */
bool Interface::is_in(string choice, int lim_start, int lim_end) const{
    set<string> availableChoices={"1","2","3","4","5","6","7","8","9","10"};
    if(availableChoices.find(choice)!= availableChoices.end()&&stoi(choice)>=lim_start && stoi(choice) <=lim_end ) return true;
    return false;
}

/** Lists according to input introduced by user
 *
 * @param choice users input/choice
 * @return 0 if no quit, 1 if quit mid process
 */
int Interface::listShow(string choice) {
    //Limitar range de opcoes
    if(!is_in(choice,1,2)){
        cout<<"Sintaxe errada.\nPor favor, reintroduzir:"<<endl;
    }
    //caso o utilizador escolha Listagem
    if(choice=="1"){
        string criteria,mode,year,type,order;
        string uc;
        cout<<"Introduza o numero do criterio de listagem:\n\t1.Listagem das turmas\n\t2.Listagem das unidades curriculares\n\t3.Listagem dos alunos\n\t4.Listagem do horario\n\t0.Sair"<<endl;
        cin>>criteria;
        if(criteria=="0") return 1;
        while(!is_in(criteria,1,4)){
            cout<<"Sintaxe errada.\nPor favor, reintroduzir:"<<endl;
            cin>>criteria;
        }
        //caso o criterio de listagem for por turmas
        if(criteria=="1") {
            cout << "Introduza tipo de listagem:\n\t1.Parcial\n\t2.Total:\n\t0.Sair" << endl;
            cin >> type;
            if (type == "0") return 1;
            while (!(is_in(type, 1, 2))) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> type;
            }
            //caso o tipo de listagem for parcial
            if (type == "1") {
                cout << "Introduza modo de listagem:\n\t1.Por ano\n\t2.Por UC\n\t0.Sair" << endl;
                cin >> mode;
                if (mode == "0") return 1;
                while(!is_in(mode,1,2)){
                    cout<<"Sintase errada.\nPor favor, reintroduzir:"<<endl;
                    cin>>mode;
                }
                //caso o modo de listagem for por ano
                if (mode == "1") {
                    cout << "Do ano:\n0.Para sair" << endl;
                    cin >> year;
                    if (year == "0") return 1;
                    while (!is_in(year, 1, 3)) {
                        cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                        cin >> year;
                    }
                    //escolhe criterio de ordenacao
                    cout<<"Criterio de ordenacao:\n\t1.crescente\n\t2.decrescente"<<endl;
                    cin>>order;
                    while(!is_in(order,1,2)){
                        cout<<"Sintase errada.\nPor favor reintroduzir:"<<endl;
                        cin>>order;
                    }

                    if (year == "1") {
                        cout << "ainda a ser implementado" << endl;
                        if(order=="1"){
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if(order=="2"){
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                    if (year == "2") {
                        cout << "ainda a ser implementada" << endl;
                        if(order=="1"){
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if(order=="2"){
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                    if (year== "3") {
                        cout << "ainda a ser implementada" << endl;
                        if(order=="1"){
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if(order=="2"){
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                }
                //caso o modo de listagem for por unidade curricular
                if(mode=="2"){
                    cout<<"Introduzir o numero da unidade curricular:\n\t0.Para Sair"<<endl;
                    cin>>uc;
                    if(uc=="0") return 1;
                    /*
                    while(se nao houver item correspondente/ null){
                        cout<<"Nome de UC invalido, reintroduzir:"<<endl;
                        cin>>uc;
                    }
                    */
                    cout<<"Criterio de ordenacoo:\n\t1.Crescente\n\t2.Decrescente"<<endl;
                    cin>>order;
                    while(!is_in(order,1,2)){
                        cout<<"Sintase errada.\nPor favor reintroduzir:"<<endl;
                        cin>>order;
                    }
                    //ainda a ser implementada por falta de funcoes
                    if(order=="1"){
                        //ainda a ser implementada de acordo com ordenacao crescente
                    }
                    if(order=="2"){
                        //ainda a ser implementada de acordo com ordenacao decrescente
                    }
                }
            }
            //se o tipo de listagem das turmas for total
            if(type=="2"){
                cout << "Todas as turmas sao listadas\n\t1.Para Continuar\n\t0.Para Sair" << endl;
                cin >> mode;
                if (mode == "0") return 1;
                while(!is_in(mode,0,1)){
                    cout<<"Sintase errada.\nPor favor reintroduzir:"<<endl;
                    cin>>mode;
                }
                cout<<"Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente"<<endl;
                cin>>order;
                while(!is_in(order,1,2)){
                    cout<<"Sintase errada.\nPor favor reintroduzir:"<<endl;
                    cin>>order;
                }
                // Mostrar todas as turmas de acordo com a ordenacao

            }
        }
        //se o criterio de listagem for de unidades curriculares(listagem de nomes de unidades curriculares e o seu codigo)
        if(criteria=="2"){
            cout << "Introduza tipo de listagem:\n\t1.Parcial\n\t2.Total:\n\t0.Sair" << endl;
            cin >> type;
            if (type == "0") return 1;
            while (!(is_in(type, 1, 2))) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> type;
            }
            //caso o tipo de listagem for parcial
            if (type == "1") {
                cout << "Do ano:\n0.Para sair" << endl;
                cin >> year;
                if (year == "0") return 1;
                while (!is_in(year, 1, 3)) {
                    cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                    cin >> year;
                }
                //escolhe criterio de ordenacao
                cout<<"Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente"<<endl;
                cin>>order;
                while(!is_in(order,1,2)){
                    cout<<"Sintase errada.\nPor favor reintroduzir:"<<endl;
                    cin>>order;
                }
                if (year == "1") {
                    cout << "ainda a ser implementado" << endl;
                    if(order=="1"){
                        //ainda a ser implementada de acordo com ordenacao crescente
                    }
                    if(order=="2"){
                        //ainda a ser implementada de acordo com ordenacao decrescente
                    }
                }
                if (year == "2") {
                    cout << "ainda a ser implementada" << endl;
                    if(order=="1"){
                        //ainda a ser implementada de acordo com ordenacao crescente
                    }
                    if(order=="2"){
                        //ainda a ser implementada de acordo com ordenacao decrescente
                    }
                }
                if (year== "3") {
                    cout << "ainda a ser implementada" << endl;
                    if(order=="1"){
                        //ainda a ser implementada de acordo com ordenacao crescente
                    }
                    if(order=="2"){
                        //ainda a ser implementada de acordo com ordenacao decrescente
                    }
                }
            }
            //caso listagem total das unidades curriculres
            if(type=="2") {
                cout<<"Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente"<<endl;
                cin>>order;
                while(!is_in(order,1,2)){
                    cout<<"Sintase errada.\nPor favor reintroduzir:"<<endl;
                    cin>>order;
                }
                if(order=="1"){
                    //ainda a ser implementada de acordo com ordenacao crescente
                }
                if(order=="2"){
                    //ainda a ser implementada de acordo com ordenacao decrescente
                }
            }


        }
    }
}







int Interface::initiate() {
    if(!database.populate()){
        return 0;
    }
    this->database.populate();
    return 1;
}
