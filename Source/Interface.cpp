//
// Created by not_real_fu on 22-10-2022.


#include "../Headers/Interface.h"
#include <iostream>
#include <set>
#include <algorithm>

/** Function that makes sure the input is within range
 *
 * @param choice user's input
 * @param lim_start where the range of possible values starts(inclusive)
 * @param lim_end where the range of possible values ends(inclusive)
 * @return boolean value true/false
 */
bool Interface::is_in(string choice, int lim_start, int lim_end) const{
    set<string> availableChoices={"0","1","2","3","4","5","6","7","8","9"};
    if(availableChoices.find(choice)!= availableChoices.end()&&stoi(choice)>=lim_start && stoi(choice) <=lim_end ) return true;
    return false;
}

/** Function that compares 2 classes in a vector of pair<className,schedule>
 *
 * @param class1
 * @param class2
 * @return Boolean value t/f
 */
bool Interface::slotsLessthan(const pair<string , Slot> &aula1, const pair<string , Slot> &aula2) {
    if(aula1.second<aula2.second){
        return true;
    }
    return false;
}
/**Function that compares 2 classes by time(used for pair<pair<string,string>,class>
 *
 * @param aula1
 * @param aula2
 * @return t/f
 */
bool Interface::slotsLessthan1(const pair<pair<std::string, std::string>, Slot> &aula1,
                              const pair<pair<std::string, std::string>, Slot> &aula2) {
    if(aula1.second<aula2.second ){

        return true;
    }
    return false;
}
/** Function that compares 2 classes by time and classCode
 *
 * @param aula1
 * @param aula2
 * @return t/f
 */
bool Interface::slotsLessthan2(const pair<string ,Slot> &aula1,const pair<string ,Slot> &aula2){
    if(aula1.second<aula2.second){
        return true;
    }
    return false;
}
/**Checks if a string is a number
 *
 * @param number
 * @return boolean t/f
 */
bool Interface::is_number(std::string n) const {
    bool nr= true;
    //verificar se o nnumero é so composto por nrs
    for(char c:n){
        if(!isdigit(c)){
            cout<<"Numero de estudante so pode ser composto por numeros,reintroduzir:"<<endl;
            nr=false;
            break;
        }
    }
    return nr;
}
/** Function that compares 2 classes by their code;
 *
 * @param class1
 * @param class2
 * @return Boolean value t/f
 */
bool Interface::turmasLessthan(const UCTurma ucturma1, const UCTurma ucturma2) {
    if(ucturma1.get_uc_turma().second.compare(ucturma2.get_uc_turma().second)<0){
        return true;
    }
    return false;
}
/**Compares 2 classes by their code
 *
 * @param ucturma1
 * @param ucturma2
 * @return t/f
 */
bool Interface::turmasGreaterthan(const UCTurma ucturma1, const UCTurma ucturma2) {
    if(ucturma1.get_uc_turma().second.compare(ucturma2.get_uc_turma().second)>0){
        return true;
    }
    return false;
}
/**Compare 2 UC by their code
 *
 * @param ucturma1
 * @param ucturma2
 * @return t/f
 */
bool Interface::ucLessthan(const UCTurma ucturma1, const UCTurma ucturma2) {
    if(ucturma1.get_uc_turma().first.compare(ucturma2.get_uc_turma().first)<0){
        return true;
    }
    return false;
}
bool Interface::ucGreaterthan(const UCTurma ucturma1, const UCTurma ucturma2) {
    if(ucturma1.get_uc_turma().first.compare(ucturma2.get_uc_turma().first)>0){
        return true;
    }
    return false;
}
/** Lists according to input introduced by user
 *
 * @param
 * @return 0 if no quit, 1 if quit mid process
 */
int Interface::initiate() {
    MenuPrincipal:string userInput;
    cout<<"Introduza o numero do comando:\n\t1.Listagem\n\t2.Alteracoes\n\t0.Sair do programa"<<endl;
    cin>>userInput;
    //Limitar range de opcoes
    if (userInput == "0") return 1;
    while(!is_in(userInput, 1, 2)) {
        cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
        cin>>userInput;
    }


    //caso o utilizador escolha Listagem
    if (userInput == "1") {
        menuListagem:string criteria, mode, year, type, order;
        string uc,turma,student;
        cout<< "Introduza o numero do criterio de listagem:\n\t1.Listagem das turmas\n\t2.Listagem das unidades curriculares\n\t3.Listagem dos alunos\n\t4.Listagem do horario\n\t0.Voltar"<<endl;
        cin >> criteria;
        while (!is_in(criteria, 0, 4)) {
            cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
            cin >> criteria;
        }
        if (criteria == "0") goto MenuPrincipal;


        //caso o criterio de listagem for por turmas
        if (criteria == "1") {
            menuAnterior2:cout << "Introduza tipo de listagem:\n\t1.Parcial\n\t2.Total:\n\t0.Voltar" << endl;
            cin >> type;
            while (!(is_in(type, 0, 2))) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> type;
            }
            if (type == "0") goto menuListagem;


            //caso o tipo de listagem for parcial
            if (type == "1") {
                menuAnterior3:cout << "Introduza modo de listagem:\n\t1.Por ano\n\t2.Por UC\n\t0.Voltar" << endl;
                cin >> mode;
                while (!is_in(mode, 0, 2)) {
                    cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2;


                //caso o modo de listagem for por ano de turmas
                if (mode == "1") {
                    cout << "Do ano:\n0.Para voltar" << endl;
                    cin >> year;
                    if (year == "0") goto menuAnterior3;;
                    while (!is_in(year, 1, 3)) {
                        cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                        cin >> year;
                    }
                    //escolhe criterio de ordenacao
                    cout << "Criterio de ordenacao:\n\t1.crescente\n\t2.decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    if (year == "1") {
                        cout << "ainda a ser implementado" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                    if (year == "2") {
                        cout << "ainda a ser implementada" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                    if (year == "3") {
                        cout << "ainda a ser implementada" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                }


                //caso o modo de listagem for por unidade curricular de turmas
                if (mode == "2") {
                    cout << "Introduzir o numero da unidade curricular(ex:L.EIC001):\n\t0.Para voltar" << endl;
                    cin >> uc;
                    if (uc == "0") goto menuAnterior3;;
                    /*
                    while(se nao houver item correspondente/ null){
                        cout<<"Codigo da UC invalido, reintroduzir:"<<endl;
                        cin>>uc;
                    }
                    */
                    cout << "Criterio de ordenacoo:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    //ainda a ser implementada por falta de funcoes
                    if (order == "1") {
                        //ainda a ser implementada de acordo com ordenacao crescente
                    }
                    if (order == "2") {
                        //ainda a ser implementada de acordo com ordenacao decrescente
                    }
                }
            }


            //se o tipo de listagem das turmas for total
            if (type == "2") {
                cout << "Todas as turmas serao listadas:\n\t1.Para Continuar\n\t0.Para voltar" << endl;
                cin >> mode;
                int class_count=0;
                vector<UCTurma> turmas=database->getUcTurmas();
                while (!is_in(mode, 0, 1)) {
                    cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2;
                cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                cin >> order;
                while (!is_in(order, 1, 2)){
                    cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                    cin >> order;
                }
                if(order=="1"){
                    std::sort(turmas.begin(),turmas.end(), turmasLessthan);
                }
                if(order=="2"){
                    std::sort(turmas.begin(),turmas.end(), turmasGreaterthan);
                }
                for(UCTurma turma:turmas){
                    cout<<"Turma: "<<turma.get_uc_turma().second<<endl;
                    class_count++;
                }
                cout<<"\n";
                cout<<"No total existem "<<class_count<<" turmas"<<endl;
                return 0;
            }
        }


        //se o criterio de listagem for de unidades curriculares(listagem de nomes de unidades curriculares e o seu codigo)
        else if (criteria == "2") {
            menuAnterior2_UC:cout << "Introduza tipo de listagem:\n\t1.Parcial\n\t2.Total:\n\t0.Voltar" << endl;
            cin >> type;
            while (!(is_in(type, 0, 2))) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> type;
            }
            if(type == "0") goto menuListagem;


            //caso o tipo de listagem for parcial de unidades curriculares
            if (type == "1") {
                cout << "Introduza modo de listagem:\n\t1.Por ano\n\t2.Por aluno\n\t0.Voltar" << endl;
                cin >> mode;
                while (!is_in(mode, 0, 2)) {
                    cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2_UC;


                //caso o modo de listagem das UCs for por ano
                if(mode=="1"){
                    cout << "Do ano:\n0.Para voltar" << endl;
                    cin >> year;
                    while (!is_in(year, 0, 3)) {
                        cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                        cin >> year;
                    }
                    if (year == "0") goto menuAnterior2_UC;
                    //escolhe criterio de ordenacao
                    cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    if (year == "1") {
                        cout << "ainda a ser implementado" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                    if (year == "2") {
                        cout << "ainda a ser implementada" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                    if (year == "3") {
                        cout << "ainda a ser implementada" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                }


                //caso a listagem das unidades curriculares seja por aluno
                if(mode=="2"){
                    cout << "Introduzir numero do estudante(ex:202201001):\n\t0.Para voltar" << endl;
                    cin >> student;
                    if (uc == "0") goto menuAnterior2_UC;
                    /*
                    while(se nao houver item correspondente/ null){
                        cout<<"Numero de estudante invalido, reintroduzir:"<<endl;
                        cin>>student;
                    }
                    */
                    cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    //ainda a ser implementada por falta de funcoes
                    if (order == "1") {
                        //ainda a ser implementada de acordo com ordenacao crescente
                    }
                    if (order == "2") {
                        //ainda a ser implementada de acordo com ordenacao decrescente
                    }


                }
            }


            //caso listagem total das unidades curriculres
            if (type == "2") {
                cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente\n\t0.Para voltar" << endl;
                cin >> order;
                int uc_count=0;
                vector<UCTurma> UCs=database->getUcTurmas();
                while (!is_in(order, 0, 2)) {
                    cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                    cin >> order;
                }
                if(order=="0") goto menuAnterior2_UC;
                if (order == "1") {
                    std::sort(UCs.begin(),UCs.end(), ucLessthan);
                }
                if (order == "2") {
                    std::sort(UCs.begin(),UCs.end(), ucGreaterthan);
                }

                for(UCTurma uc:UCs){
                    cout<<"UC: "<<uc.get_uc_turma().first<<endl;
                    uc_count++;
                }
                cout<<"\n";
                cout<<"No total existem "<<uc_count<<" unidades curriculares."<<endl;
                return 0;
            }
        }


            //listagem dos alunos
        else if (criteria == "3") {
            menuAnterior2_Students:cout << "Introduza tipo de listagem:\n\t1.Parcial\n\t2.Total:\n\t0.Voltar" << endl;
            cin >> type;
            if (!is_in(type, 0, 2)) {
                cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                cin >> type;
            }
            if (type == "0") goto menuListagem;


            //listagem dos alunos parcial
            if (type == "1") {
                menuAnterior3_Students:cout << "Introduza modo de listagem:\n\t1.Por ano\n\t2.Por UC\n\t3.Por turma\n\t0.Voltar" << endl;
                cin >> mode;
                while (!is_in(mode, 0, 3)) {
                    cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2_Students;


                //caso o modo de listagem for por ano de alunos
                if (mode == "1") {
                    cout << "Do ano:\n0.Para sair" << endl;
                    cin >> year;
                    while (!is_in(year, 0, 3)) {
                        cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                        cin >> year;
                    }
                    if (year == "0") goto menuAnterior3_Students;
                    //escolhe criterio de ordenacao
                    cout << "Criterio de ordenacao:\n\t1.crescente\n\t2.decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    if (year == "1") {
                        cout << "ainda a ser implementado" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                    if (year == "2") {
                        cout << "ainda a ser implementada" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                    if (year == "3") {
                        cout << "ainda a ser implementada" << endl;
                        if (order == "1") {
                            //ainda a ser implementada de acordo com ordenacao crescente
                        }
                        if (order == "2") {
                            //ainda a ser implementada de acordo com ordenacao decrescente
                        }
                    }
                }


                //caso o modo de listagem for por unidade curricular de alunos
                if (mode == "2") {
                    CSVReader processingTool;
                    cout << "Introduzir o codigo da unidade curricular:\n\t0.Para voltar" << endl;
                    cin >> uc;
                    if (uc == "0") goto menuAnterior3_Students;
                    /*
                    while(se nao houver item correspondente/ null){
                        cout<<"Codigo de UC invalido, reintroduzir:"<<endl;
                        cin>>uc;
                    }
                    */

                    cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    cout<<"No total esta unidade curricular tem: "<<database->get_studentnum_per_uc(uc)<<" alunos"<<endl;
                    //ainda a ser implementada por falta de funcoes
                    if (order == "1") {
                        //ainda a ser implementada de acordo com ordenacao crescente
                    }
                    if (order == "2") {
                        //ainda a ser implementada de acordo com ordenacao decrescente
                    }

                    return 0;
                }


                //Caso a listagem parcial de alunos for por turma
                if (mode=="3"){
                    cout<<"Introduzir o codigo da turma(ex:1LEIC01):\n\t0.Para voltar"<<endl;
                    cin>>turma;
                    /*
                    while(se nao houver item correspondente/ null){
                        cout<<"Codigo de turma invalido, reintroduzir:"<<endl;
                        cin>>turma;
                    }
                    */
                    if(turma=="0") goto menuAnterior3_Students;
                    cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    //ainda a ser implementada por falta de funcoes
                    if (order == "1") {
                        //ainda a ser implementada de acordo com ordenacao crescente
                        return 0;
                    }
                    if (order == "2") {
                        //ainda a ser implementada de acordo com ordenacao decrescente
                        return 0;
                    }
                }
            }


            //listagem de alunos total
            if(type=="2"){
                cout << "Todas os alunos sao listados\n\t1.Para Continuar\n\t0.Para voltar" << endl;
                cin >> mode;
                while (!is_in(mode,0,1)) {
                    cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2_Students;
                cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                cin >> order;
                while (!is_in(order, 1, 2)){
                    cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                    cin >> order;
                }
                if (order == "1") {
                    //ainda a ser implementada de acordo com ordenacao crescente
                    return 0;
                }
                if (order == "2") {
                    //ainda a ser implementada de acordo com ordenacao decrescente
                    return 0;
                }
            }
        }


        //listagem do horario
        else if (criteria == "4") {
            menuAnterior1_horario:cout<< "Introduza o numero modo de listagem:\n\t1.Por aluno\n\t2.Por turma\n\t3.Por unidade curricular\n\t0.Voltar"<<endl;
            cin >> mode;
            while (!is_in(mode, 0, 3)) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> mode;
            }
            if (mode == "0") goto menuListagem;


            //caso modo de listagem por aluno
            if(mode=="1") {
                cout << "Introduza o numero do estudante(ex:202201001):\n\t0.Para voltar" << endl;
                cin >> student;
                while(!is_number(student)) cin>>student;
                //verificar se existe o aluno na base de dados;
                Student target = Student(stoi(student));
                auto it = database->getStudents().find(target);
                while(it==database->getStudents().end()){
                    cout<<"Codigo de estudante invalido, reintroduzir:"<<endl;
                    cin>>student;
                    target=Student(stoi(student));
                    it=database->getStudents().find(target);
                }
                if (student == "0") goto menuAnterior1_horario;

                vector< pair<pair<string, string>, Slot>> timetable;
                list<UCTurma*> ucturmas=database->get_student_timetable(stoi(student));
                for(UCTurma* ucturma:ucturmas){
                    for(Slot aula:ucturma->get_slots()){
                        timetable.push_back({ucturma->get_uc_turma(),aula});
                    }
                }
               std::sort(timetable.begin(),timetable.end(), slotsLessthan1);
                //aula é um par de <UCturma<uc,turma>,Slot>
                for(pair<pair<string,string>,Slot> aula:timetable){
                    cout<<aula.second.getDay()<<"\n"<<"Aula: "<<aula.first.first<<"\t"<<"Comeco: "<<aula.second.getStart()<<"h\t"<<"Duracao: "<<aula.second.getDuration()<<"h\t"<<"Tipo: "<<aula.second.getType()<<" \t"<<"Turma: "<<aula.first.second<<endl;
                    cout<<"\n";
                }
                return 0;
            }


            //caso modo de listagem por turma
            if(mode=="2"){
                cout << "Introduza o numero da turma(ex:1LEIC01):\n\t0.Para voltar" << endl;
                cin>>turma;
                bool not_found=true;
                vector<UCTurma>target_list=database->getUcTurmas();
                //finds if turma is in database
                for(UCTurma target:target_list){
                    if(target.get_uc_turma().second==turma) not_found=false;
                }
                while(not_found){
                    cout<<"numero de turma nao existente,reintroduzir:"<<endl;
                    cin>>turma;
                    for(UCTurma target:target_list){
                        if(target.get_uc_turma().second==turma) not_found=false;
                    }
                }
               if(turma=="0") goto menuAnterior1_horario;

                vector<pair<string,Slot>> timeTable=database->get_turma_timetable(turma);
                std::sort(timeTable.begin(), timeTable.end(), slotsLessthan);
                for(pair<string,Slot> aula: timeTable){
                    cout<<aula.second.getDay()<<"\n"<<"Aula: "<<aula.first<<"\t"<<"Comeco: "<<aula.second.getStart()<<"h\t"<<"Duracao: "<<aula.second.getDuration()<<"h\t"<<"Tipo: "<<aula.second.getType()<<endl;
                    cout<<"\n";
                }
                return 0;
            }

            //Listagem do horario por UC
            if(mode=="3"){
                menuAnterior2_horario:cout << "Introduza o codigo da UC:\n\t0.Para voltar" << endl;
                cin >> uc;
                UCTurma target= UCTurma(uc,"");
                vector<UCTurma> target_list= database->getUcTurmas();
                auto it = lower_bound(target_list.begin(),target_list.end(),target);
                while(it==target_list.end()){
                    cout<<"Codigo da UC invalido, reintroduzir:"<<endl;
                    cin>>uc;
                    target= UCTurma(uc,"");
                    it = lower_bound(target_list.begin(),target_list.end(),target);
                }
                if(uc=="0") goto menuAnterior1_horario;

                cout << "Introduza tipo de listagem:\n\t0.Para voltar" << endl;
                vector<pair<string,Slot>> timetable=database->get_uc_timetable(uc);
                std::sort(timetable.begin(),timetable.end(), slotsLessthan2);
                for(pair<string,Slot> aula:timetable){
                    cout<<aula.second.getDay()<<"\n"<<"Turma: "<<aula.first<<"\t"<<"Comeco: "<<aula.second.getStart()<<"h\t"<<"Duracao: "<<aula.second.getDuration()<<"h\t"<<"Tipo: "<<aula.second.getType()<<endl;
                    cout<<"\n";
                }
                return 0;

            }
        }
    }

    //ainda por implementar!!!!
    else if(userInput=="2"){
        //alteracoes do horario

    }

}



Interface::Interface(CSVReader &reader): database(&reader) {}
