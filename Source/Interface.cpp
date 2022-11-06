//
// Created by not_real_fu on 22-10-2022.


#include "../Headers/Interface.h"
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
/**Constructor for Interface \n
 * Complexity: O(1)
 * @param CSVReader reader
 * @param Request request
 */
Interface::Interface(CSVReader &reader, RequestProcesser* request): database(&reader), requestProcesser(request) {}
/** Function that makes sure the input is within range \n
 * Complexity: O(1)
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




/** Function that compares 2 classes in a vector of pair<className,schedule> \n
 * Complexity: O(1)
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

/**Function that compares 2 classes by time(used for pair<pair<string,string>,class> \n
 * Complexity: O(1)
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

/**Compare function for set of student pointers \n
 * Complexity: O(1)
 * @param Student* s1
 * @param Student* s2
 * @return t/f
 */
bool Interface::set_compareLessthan_student(const Student* s1,const Student* s2){
    return (s1->get_name()<s2->get_name());
}


/**Checks if a string is a number \n
 * Complexity: O(n) (n = size of string)
 * @param number
 * @return boolean t/f
 */
bool Interface::is_number(std::string n) const {
    bool nr= true;
    //verificar se o nnumero é so composto por nrs
    for(char c:n){
        if(!isdigit(c)){
            nr=false;
            break;
        }
    }
    return nr;
}


/**Compare 2 UC by their code \n
 * Complexity: O(n) (n = size of string) (the complexity for string.compare() isn't listed on cppreference, I am assuming it is O(n) based on other string methods and a stackoverflow page)
 * @param ucturma1
 * @param ucturma2
 * @return t/f
 */
bool Interface::ucGreaterthan1(const UCTurma* ucturma1, const UCTurma* ucturma2) {
    if((*ucturma1).get_uc_turma().first.compare((*ucturma2).get_uc_turma().first)>0){
        return true;
    }
    return false;
}

/**Compare 2 UC by their code \n
 * Complexity: O(n) (n = size of string) (the complexity for string.compare() isn't listed on cppreference, I am assuming it is O(n) based on other string methods and a stackoverflow page)
 * @param ucturma1
 * @param ucturma2
 * @return t/f
 */
bool Interface::ucLessthan1(const UCTurma* ucturma1, const UCTurma* ucturma2) {
    if((*ucturma1).get_uc_turma().first.compare((*ucturma2).get_uc_turma().first)<0){
        return true;
    }
    return false;
}




/** Operations according to input introduced by user
 *
 * @param
 * @return 0 if no quit, 1 if quit mid process
 */
int Interface::initiate() {
    MenuPrincipal:string userInput;
    cout<<"Introduza o numero do comando:\n\t1.Listagem\n\t2.Alteracoes\n\t3.Carregar estado da ultima ultilizacao do programa\n\t4.Guardar estado do programa\n\t0.Sair do programa"<<endl;
    cin>>userInput;
    //Limitar range de opcoes
    if (userInput == "0") return 1;
    while(!is_in(userInput, 1, 4)) {
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
            menuAnterior2:cout << "Introduza tipo de listagem:\n\t1.Parcial\n\t2.Total\n\t0.Voltar" << endl;
            cin >> type;
            while (!(is_in(type, 0, 2))) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> type;
            }
            if (type == "0") goto menuListagem;


            //caso o tipo de listagem for parcial
            if (type == "1") {
                menuAnterior3:cout << "Introduza modo de listagem:\n\t1.Por ano\n\t2.Por UC\n\t3.Por aluno\n\t0.Voltar" << endl;
                cin >> mode;
                while (!is_in(mode, 0, 3)) {
                    cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2;


                //caso o modo de listagem for por ano de turmas
                //Complexity: O(n + mlog(m)) (n = times user tries an invalid input, m = number of UCTurmas)
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
                    int turma_count=0;
                    if (year == "1") {
                        set<string> partialTurmas;
                        for(const UCTurma& turma:database->getUcTurmas()) {
                            if(turma.get_uc_turma().second.substr(0,1)=="1") partialTurmas.insert(turma.get_uc_turma().second);
                        }
                        if (order == "1") {
                            for(const string& turma:partialTurmas){
                                cout<<"Turma: "<<turma<<endl;
                                turma_count++;
                            }
                        }
                        if (order == "2") {
                            auto it=partialTurmas.end();
                            for(it--;it!=partialTurmas.begin();it--){
                                cout<<"Turma: "<<*it<<endl;
                                turma_count++;
                            }
                            cout<<"Turma: "<<*it<<endl;
                            turma_count++;
                        }
                        cout<<"\n";
                        cout<<"O numero de turmas no 1 ano: "<<turma_count<<"\n"<<endl;
                        return 0;
                    }
                    if (year == "2") {
                        set<string> partialTurmas;
                        for(UCTurma turma:database->getUcTurmas()) {
                            if(turma.get_uc_turma().second.substr(0,1)=="2") partialTurmas.insert(turma.get_uc_turma().second);
                        }
                        if (order == "1") {
                            for(string turma:partialTurmas){
                                cout<<"Turma: "<<turma<<endl;
                                turma_count++;
                            }
                        }
                        if (order == "2") {
                            auto it=partialTurmas.end();
                            for(it--;it!=partialTurmas.begin();it--){
                                cout<<"Turma: "<<*it<<endl;
                                turma_count++;
                            }
                            turma_count++;
                            cout<<"Turma: "<<*it<<endl;
                        }
                        cout<<"\n";
                        cout<<"O numero de turmas no 2 ano: "<<turma_count<<"\n"<<endl;
                    }
                    if (year == "3") {
                        set<string> partialTurmas;
                        for(UCTurma turma:database->getUcTurmas()) {
                            if(turma.get_uc_turma().second.substr(0,1)=="3") partialTurmas.insert(turma.get_uc_turma().second);
                        }
                        if (order == "1") {
                            for(string turma:partialTurmas){
                                cout<<"Turma: "<<turma<<endl;
                                turma_count++;
                            }
                        }
                        if (order == "2") {
                            auto it=partialTurmas.end();
                            for(it--;it!=partialTurmas.begin();it--){
                                cout<<"Turma: "<<*it<<endl;
                                turma_count++;
                            }
                            turma_count++;
                            cout<<"Turma: "<<*it<<endl;
                        }
                        cout<<"\n";
                        cout<<"O numero de turmas no 1 ano: "<<turma_count<<"\n"<<endl;
                    }
                    return 0;
                }


                //caso o modo de listagem for por unidade curricular de turmas
                //Complexity: O(mlog(n) + n) (m = number of inputs until valid input, n = size of uc_turmas vector)
                if (mode == "2") {
                    int turma_count=0;
                    cout << "Introduzir o numero da unidade curricular(ex:L.EIC001):\n\t0.Para voltar" << endl;
                    cin >> uc;
                    if(uc=="0") goto menuAnterior3;
                    UCTurma target= UCTurma(uc,"");
                    auto it = lower_bound( database->getUcTurmas().begin(), database->getUcTurmas().end(),target);
                    while(it== database->getUcTurmas().end()){
                        cout<<"Codigo da UC invalido, reintroduzir:"<<endl;
                        cin>>uc;
                        if(uc=="0") goto menuAnterior3;
                        target= UCTurma(uc,"");
                        it = lower_bound( database->getUcTurmas().begin(), database->getUcTurmas().end(),target);

                    }
                    vector<string> turmas;
                    while ((*it).get_uc_turma().first == uc) {
                        turmas.push_back((*it).get_uc_turma().second);
                        it++;
                    }
                    cout << "Criterio de ordenacoo:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    if (order == "1") {
                        for(string turma:turmas){
                            cout<<"Turma: "<<turma<<endl;
                            turma_count++;
                        }
                    }
                    if (order == "2") {
                        auto it = turmas.end();
                        for (it--; it != turmas.begin(); it--) {
                            cout << "Turma: " << *it << endl;
                            turma_count++;
                        }
                        turma_count++;
                        cout << "Turma: " << *it << endl;
                    }
                    cout<<"\n";
                    cout<<"No total existem "<<turma_count<<" turmas em: " <<uc<<"\n"<<endl;
                    return 0;
                }


                //caso a listagem de turmas for por aluno
                if (mode=="3"){
                    string n_c;
                    int class_count;
                    cout << "\t1.Pelo nome\n\t2.Pelo codigo\n\t0.Voltar" << endl;
                    cin >> n_c;
                    while (!is_in(n_c, 0, 2)) {
                        cout << "Sintase errada, Por favor,reintroduzir" << endl;
                        cin >> n_c;
                    }
                    if (n_c == "0") goto menuAnterior3_uc;

                    if (n_c == "1") {
                        cout << "Introduza o nome do estudante:\n\t0.Voltar" << endl;
                        cin.ignore();
                        getline(cin, student);
                        int s = database->find_student_num_by_name(student);
                        if (student == "0") goto menuAnterior3;
                        while (s == 1) {
                            cout << "Nome nao encontrado,reintroduzir:" << endl;
                            cin >> student;
                            s = database->find_student_num_by_name(student);
                            if (student == "0") goto menuAnterior3;
                        }
                        cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                        cin >> order;
                        while (!is_in(order, 1, 2)) {
                            cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                            cin >> order;
                        }
                        list<UCTurma*> UCTurmas=database->get_student_timetable(s);
                        set<string> turmas;
                        for(UCTurma* turma:UCTurmas){
                            turmas.insert(turma->get_uc_turma().second);
                        }
                        if(order=="1"){
                            for(string turma:turmas){
                                cout<<"Turma: "<<turma<<endl;
                                class_count++;
                            }
                        }
                        if(order=="2"){
                            auto it = turmas.end();
                            for (it--; it != turmas.begin(); it--) {
                                cout << "Turma: " << *it << endl;
                                class_count++;
                            }
                            cout << "Turma: " << *it << endl;
                            class_count++;
                        }
                    }
                    if(n_c=="2"){
                        cout << "Introduza o numero do estudante(ex:202201001):\n\t0.Para voltar" << endl;
                        cin >> student;
                        //verificar se existe o aluno na base de dados;
                        while(!is_number(student)) {
                            cout<<"Codigo invalido,reintroduzir:"<<endl;
                            cin>>student;
                        }
                        //Student target = Student(stoi(student));
                        Student search = database->get_student_by_num(stoi(student));
                        //auto it = database->getStudents().find(target);
                        if (student == "0") goto menuAnterior3;
                        while(search.get_num() == 0){
                            cout<<"Codigo de estudante nao existente, reintroduzir:"<<endl;
                            cin>>student;
                            while(!is_number(student)) {
                                cout<<"Codigo invalido,reintroduzir:"<<endl;
                                cin>>student;
                            }
                            //target=Student(stoi(student));
                            //it=database->getStudents().find(target);
                            search = database->get_student_by_num(stoi(student));
                            if (student == "0") goto menuAnterior3;
                        }

                        cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                        cin >> order;
                        while (!is_in(order, 1, 2)) {
                            cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                            cin >> order;
                        }
                        list<UCTurma*> UCTurmas=database->get_student_timetable(stoi(student));
                        set<string> turmas;
                        for(UCTurma* turma:UCTurmas){
                            turmas.insert(turma->get_uc_turma().second);
                        }
                        if(order=="1"){
                            for(string turma:turmas){
                                cout<<"Turma: "<<turma<<endl;
                                class_count++;
                            }
                        }
                        if(order=="2"){
                            auto it = turmas.end();
                            for (it--; it != turmas.begin(); it--) {
                                cout << "Turma: " << *it << endl;
                                class_count++;
                            }
                            cout << "Turma: " << *it << endl;
                            class_count++;
                        }
                    }
                    return 0;
                }
            }


            //se o tipo de listagem das turmas for total
            //Complexity: O(nlog(n)) (n = number of turmas)
            if (type == "2") {
                cout << "Todas as turmas serao listadas:\n\t1.Para Continuar\n\t0.Para voltar" << endl;
                cin >> mode;
                int class_count=0;
                set<string> turmas;
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

                for(UCTurma t:database->getUcTurmas()){
                    turmas.insert(t.get_uc_turma().second);
                }
                if(order=="1"){
                    for(string turma:turmas){
                        cout<<"Turma: "<<turma<<endl;
                        class_count++;
                    }
                }
                if(order=="2"){
                    auto it = turmas.end();
                    for (it--; it != turmas.begin(); it--) {
                        cout << "Turma: " << *it << endl;
                        class_count++;
                    }
                    class_count++;
                    cout << "Turma: " << *it << endl;
                }
                cout<<"\n";
                cout<<"No total existem "<<class_count<<" turmas."<<"\n"<<endl;
                return 0;
            }
        }


        //se o criterio de listagem for de unidades curriculares(listagem de unidades curriculares e o seu codigo)
        else if (criteria == "2") {
            menuAnterior2_UC:
            cout << "Introduza tipo de listagem:\n\t1.Parcial\n\t2.Total\n\t0.Voltar" << endl;
            cin >> type;
            while (!(is_in(type, 0, 2))) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> type;
            }
            if (type == "0") goto menuListagem;


            //caso o tipo de listagem for parcial de unidades curriculares
            if (type == "1") {
                menuAnterior3_uc:
                int uc_count=0;
                cout << "Introduza modo de listagem:\n\t1.Por ano\n\t2.Por aluno\n\t0.Voltar" << endl;
                cin >> mode;
                while (!is_in(mode, 0, 2)) {
                    cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2_UC;

                //caso o modo de listagem das UCs for por ano
                if (mode == "1") {
                    cout << "Do ano:\n0.Para voltar" << endl;
                    cin >> year;
                    while (!is_in(year, 0, 3)) {
                        cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                        cin >> year;
                    }
                    if (year == "0") goto menuAnterior3_uc;
                    //escolhe criterio de ordenacao
                    cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    set<string> partialUCs;
                    if (year == "1") {
                        for (UCTurma ucturma: database->getUcTurmas()) {
                            if (ucturma.get_uc_turma().second.substr(0, 1) == "1") {
                                partialUCs.insert(ucturma.get_uc_turma().first);
                            }
                        }
                    }
                    if (year == "2") {
                        for (UCTurma ucturma: database->getUcTurmas()) {
                            if (ucturma.get_uc_turma().second.substr(0, 1) == "2") {
                                partialUCs.insert(ucturma.get_uc_turma().first);
                            }
                        }
                    }
                    if (year == "3") {
                        for (UCTurma ucturma:database->getUcTurmas()) {
                            if (ucturma.get_uc_turma().second.substr(0, 1) == "3") {
                                partialUCs.insert(ucturma.get_uc_turma().first);
                            }
                        }
                    }
                    if(order=="1"){
                        for(string uc :partialUCs){
                            cout<<"UC: "<< uc<<endl;
                            uc_count++;
                        }
                    }
                    if(order=="2"){
                        auto it = partialUCs.end();
                        for (it--; it != partialUCs.begin(); it--) {
                            cout << "UC: " << *it << endl;
                            uc_count++;
                        }
                        uc_count++;
                        cout << "UC: " << *it << endl;
                    }
                    cout<<"\n"<<endl;
                    cout<<"No total existem "<<uc_count<<" UCs"<<" no "<<"ano "<<year<<"\n"<<endl;
                    uc_count=0;
                    return 0;
                }

                //caso a listagem das unidades curriculares seja por aluno
                if (mode == "2") {
                    string n_c;
                    menuAnterior4_uc:
                    cout << "\t1.Pelo nome\n\t2.Pelo codigo\n\t0.Voltar" << endl;
                    cin >> n_c;
                    while (!is_in(n_c, 0, 2)) {
                        cout << "Sintase errada, Por favor,reintroduzir" << endl;
                        cin >> n_c;
                    }
                    if (n_c == "0") goto menuAnterior3_uc;

                    if (n_c == "1") {
                        cout << "Introduza o nome do estudante:\n\t0.Voltar" << endl;
                        cin.ignore();
                        getline(cin, student);
                        int s = database->find_student_num_by_name(student);
                        if (student == "0") goto menuAnterior4_uc;
                        while (s == 1) {
                            cout << "Nome nao encontrado,reintroduzir:" << endl;
                            cin >> student;
                            s = database->find_student_num_by_name(student);
                            if (student == "0") goto menuAnterior4_uc;
                        }
                        cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                        cin >> order;
                        while (!is_in(order, 1, 2)) {
                            cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                            cin >> order;
                        }
                        list<UCTurma*> ucs=database->get_student_timetable(s);
                        if (order == "1") {
                            ucs.sort(ucLessthan1);
                        }
                        if (order == "2") {
                            ucs.sort(ucGreaterthan1);
                        }
                        for(UCTurma* uc:ucs){
                            cout<<"UC: "<<uc->get_uc_turma().first<<endl;
                            uc_count++;
                        }
                        cout<<"\n"<<endl;
                        cout<<"O nr de UCs: "<<uc_count<<"\n"<<endl;
                        return 0;
                    }
                    if(n_c=="2"){
                        cout << "Introduza o numero do estudante(ex:202201001) ou nome:\n\t0.Para voltar" << endl;
                        cin >> student;
                        //verificar se existe o aluno na base de dados;
                        while(!is_number(student)) {
                            cout<<"Codigo invalido,reintroduzir:"<<endl;
                            cin>>student;
                        }
                        //Student target = Student(stoi(student));
                        Student search = database->get_student_by_num(stoi(student));
                        //auto it = database->getStudents().find(target);
                        if (student == "0") goto menuAnterior4_uc;
                        while(search.get_num() == 0){
                            cout<<"Codigo de estudante nao existente, reintroduzir:"<<endl;
                            cin>>student;
                            while(!is_number(student)) {
                                cout<<"Codigo invalido,reintroduzir:"<<endl;
                                cin>>student;
                            }
                            //target=Student(stoi(student));
                            search = database->get_student_by_num(stoi(student));
                            //it=database->getStudents().find(target);
                            if (student == "0") goto menuAnterior4_uc;
                        }

                        cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                        cin >> order;
                        while (!is_in(order, 1, 2)) {
                            cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                            cin >> order;
                        }
                        list<UCTurma*> ucs=database->get_student_timetable(stoi(student));
                        if (order == "1") {
                            ucs.sort(ucLessthan1);
                        }
                        if (order == "2") {
                            ucs.sort(ucGreaterthan1);
                        }
                        for(UCTurma* uc:ucs){
                            cout<<"UC: "<<uc->get_uc_turma().first<<endl;
                            uc_count++;
                        }
                        cout<<"\n"<<endl;
                        cout<<"O nr de UCs: "<<uc_count<<"\n"<<endl;
                        return 0;
                    }
                }
            }
            //caso listagem total das unidades curriculres
            if (type == "2") {
                cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente\n\t0.Para voltar" << endl;
                cin >> order;
                int uc_count=0;
                set<string> UCs;
                while (!is_in(order, 0, 2)) {
                    cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                    cin >> order;
                }
                if(order=="0") goto menuAnterior2_UC;

                for(UCTurma uc:database->getUcTurmas()){
                    UCs.insert(uc.get_uc_turma().first);
                }
                if (order == "1") {
                    for(string uc:UCs){
                        cout<<"UC: "<<uc<<endl;
                        uc_count++;
                    }
                }
                if (order == "2") {

                    auto it=UCs.end();
                    for(it--;it!=UCs.begin();it--){
                        cout<<"UC: "<<*it<<endl;
                        uc_count++;
                    }
                    cout<<"UC: "<<*it<<endl;
                    uc_count++;
                }
                cout<<"\n";
                cout<<"No total existem "<<uc_count<<" unidades curriculares."<<"\n"<<endl;
                return 0;

            }
        }

            //listagem dos alunos
        else if (criteria == "3") {
            menuAnterior2_Students:
            cout << "Introduza tipo de listagem:\n\t1.Parcial\n\t2.Total:\n\t0.Voltar" << endl;
            cin >> type;
            if (!is_in(type, 0, 2)) {
                cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                cin >> type;
            }
            if (type == "0") goto menuListagem;


            //listagem dos alunos parcial
            if (type == "1") {
                menuAnterior3_Students:
                cout
                        << "Introduza modo de listagem:\n\t1.Por ano\n\t2.Por UC\n\t3.Por turma\n\t4.Com mais de n UCs\n\t0.Voltar"
                        << endl;
                cin >> mode;
                while (!is_in(mode, 0, 4)) {
                    cout << "Sintase errada.\nPor favor, reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2_Students;


                //caso o modo de listagem for por ano de alunos
                if (mode == "1") {
                    int student_count = 0;
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
                    set<Student *, decltype(set_compareLessthan_student) *> res(set_compareLessthan_student);
                    if (year == "1") {
                        for (Student s: database->getStudents()) {
                            for (UCTurma *turma: s.getUcTurmas()) {
                                Student *s_p = new Student(s);
                                if (turma->get_uc_turma().second.substr(0, 1) == "1") {
                                    res.insert(s_p);
                                    break;
                                }
                            }
                        }
                        if (order == "1") {
                            for (Student *s: res) {
                                cout << "Aluno: " << s->get_name() << "   Codigo: " << s->get_num() << endl;
                                delete s;
                                student_count++;
                            }
                        }
                        if (order == "2") {
                            auto it = res.end();
                            for (it--; it != res.begin(); it--) {
                                cout << "Aluno: " << (*it)->get_name() << "   Codigo" << (*it)->get_num() << endl;
                                delete (*it);
                                student_count++;
                            }
                            cout << "Aluno: " << (*it)->get_name() << "   Codigo" << (*it)->get_num() << endl;
                            delete (*it);
                            student_count++;
                        }
                        cout << "\n";
                        cout << "Total de alunos que tem aulas em turmas do 1 ano: " << student_count << "\n" << endl;
                    }
                    if (year == "2") {
                        for (Student s: database->getStudents()) {
                            for (UCTurma *turma: s.getUcTurmas()) {
                                Student *s_p = new Student(s);
                                if (turma->get_uc_turma().second.substr(0, 1) == "2") {
                                    res.insert(s_p);
                                    break;
                                }
                            }
                        }
                        if (order == "1") {
                            for (Student *s: res) {
                                cout << "Aluno: " << s->get_name() << "   Codigo: " << s->get_num() << endl;
                                delete s;
                                student_count++;
                            }
                        }
                        if (order == "2") {
                            auto it = res.end();
                            for (it--; it != res.begin(); it--) {
                                cout << "Aluno: " << (*it)->get_name() << "   Codigo: " << (*it)->get_num() << endl;
                                delete (*it);
                                student_count++;
                            }
                            cout << "Aluno: " << (*it)->get_name() << "   Codigo" << (*it)->get_num() << endl;
                            delete (*it);
                            student_count++;
                        }
                        cout << "\n";
                        cout << "Total de alunos que tem aulas em turmas do 2 ano: " << student_count << "\n" << endl;
                    }

                    if (year == "3") {
                        for (Student s: database->getStudents()) {
                            for (UCTurma *turma: s.getUcTurmas()) {
                                Student *s_p = new Student(s);
                                if (turma->get_uc_turma().second.substr(0, 1) == "3") {
                                    res.insert(s_p);
                                    break;
                                }
                            }
                        }
                        if (order == "1") {
                            for (Student *s: res) {
                                cout << "Aluno: " << s->get_name() << "   Codigo: " << s->get_num() << endl;
                                delete s;
                                student_count++;
                            }
                        }
                        if (order == "2") {
                            auto it = res.end();
                            for (it--; it != res.begin(); it--) {
                                cout << "Aluno: " << (*it)->get_name() << "   Codigo: " << (*it)->get_num() << endl;
                                delete (*it);
                                student_count++;
                            }
                            cout << "Aluno: " << (*it)->get_name() << "   Codigo" << (*it)->get_num() << endl;
                            delete (*it);
                            student_count++;
                        }
                        cout << "\n";
                        cout << "Total de alunos no que tem aulas em turmas do 3 ano: " << student_count << "\n"
                             << endl;
                    }
                    return 0;
                }


                //caso o modo de listagem for de alunos por unidade curricular
                if (mode == "2") {
                    int student_count = 0;
                    cout << "Introduzir o codigo da unidade curricular:\n\t0.Para voltar" << endl;
                    cin >> uc;
                    //verificar se existe UC na base de dados
                    if (uc == "0") goto menuAnterior3_Students;
                    UCTurma target = UCTurma(uc, "");
                    auto it = lower_bound( database->getUcTurmas().begin(),  database->getUcTurmas().end(), target);
                    while (it ==  database->getUcTurmas().end()) {
                        cout << "Codigo da UC invalido, reintroduzir:" << endl;
                        cin >> uc;
                        target = UCTurma(uc, "");
                        it = lower_bound( database->getUcTurmas().begin(),  database->getUcTurmas().end(), target);
                        if (uc == "0") goto menuAnterior3_Students;
                    }

                    cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    set<Student *, decltype(set_compareLessthan_student) *> students(set_compareLessthan_student);
                    for (Student s: database->getStudents()) {
                        //verificar se o aluno tem a UC
                        for (UCTurma *ucturma: s.getUcTurmas()) {
                            if (ucturma->get_uc_turma().first == uc) {
                                Student *s_p = new Student(s);
                                students.insert(s_p);
                                break;
                            }
                        }
                    }
                    if (order == "1") {
                        for (Student *s: students) {
                            cout << "Aluno: " << s->get_name() << "   Codigo: " << s->get_num() << endl;
                            delete s;
                            student_count++;
                        }
                    }
                    if (order == "2") {
                        auto it = students.end();
                        for (it--; it != students.begin(); it--) {
                            cout << "Aluno: " << (*it)->get_name() << "   Codigo: " << (*it)->get_num() << endl;
                            delete (*it);
                            student_count++;
                        }
                        cout << "Aluno: " << (*it)->get_name() << "   Codigo: " << (*it)->get_num() << endl;
                        delete (*it);
                        student_count++;
                    }
                    cout << "\n";
                    cout << "No total esta unidade curricular tem: " << database->get_studentnum_per_uc(uc) << " alunos"
                         << "\n" << endl;
                    return 0;
                }


                //Caso a listagem parcial de alunos for por turma
                if (mode == "3") {
                    int aluno_count = 0;
                    cout << "Introduzir o codigo da turma(ex:1LEIC01):\n\t0.Para voltar" << endl;
                    cin >> turma;
                    bool not_found = true;
                    //finds if turma is in database
                    if (turma == "0") goto menuAnterior3_Students;
                    for (UCTurma target:  database->getUcTurmas()) {
                        if (target.get_uc_turma().second == turma) not_found = false;
                    }
                    while (not_found) {
                        cout << "numero de turma nao existente,reintroduzir:" << endl;
                        cin >> turma;
                        for (UCTurma target:  database->getUcTurmas()) {
                            if (target.get_uc_turma().second == turma) not_found = false;
                        }
                        if (turma == "0") goto menuAnterior3_Students;
                    }
                    cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                        cin >> order;
                    }
                    set<Student *, decltype(&set_compareLessthan_student)> students(&set_compareLessthan_student);
                    for (Student s: database->getStudents()) {
                        //verificar se o aluno tem a turma
                        for (UCTurma *ucturma: s.getUcTurmas()) {
                            if (ucturma->get_uc_turma().second == turma) {
                                Student *s_p = new Student(s);
                                students.insert(s_p);
                                break;
                            }
                        }
                    }
                    if (order == "1") {
                        for (Student *s: students) {
                            cout << "Aluno: " << s->get_name() << "   Codigo: " << s->get_num() << endl;
                            delete s;
                            aluno_count++;
                        }
                    }
                    if (order == "2") {
                        auto it = students.end();
                        for (it--; it != students.begin(); it--) {
                            cout << "Aluno: " << (*it)->get_name() << "   Codigo: " << (*it)->get_num() << endl;
                            delete (*it);
                            aluno_count++;
                        }
                        cout << "Aluno: " << (*it)->get_name() << "   Codigo: " << (*it)->get_num() << endl;
                        delete (*it);
                        aluno_count++;
                    }
                    cout << "\n";
                    cout << "No total esta turma tem: " << aluno_count << " alunos" << "\n"
                         << endl;
                    return 0;
                }

                //caso listagem de alunos seja por mais de n UCs
                if (mode == "4") {
                    cout << "Introduza o nr de ucs:\n\t0.Voltar" << endl;
                    cin >> uc;
                    if (uc == "0") goto menuAnterior3_Students;
                    while (!is_number(uc)) {
                        cout << "Sintase errada, reintroduzir" << endl;
                        cin >> uc;
                        if (uc == "0") goto menuAnterior3_Students;
                    }
                    cout << "Introduza criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente " << endl;
                    cin >> order;
                    while (!is_in(order, 1, 2)) {
                        cout << "Sintase errada, reintroduzir: " << endl;
                        cin >> order;
                    }

                    //Coloca estudantes com mais de n nr de ucs num set ordenado
                    set<pair<string, unsigned int>> ordered_students;
                    int student_count = 0;
                    for (Student student: database->getStudents()) {
                        if (student.get_number_of_uc() >= stoi(uc)) {
                            ordered_students.insert({student.get_name(), student.get_num()});
                        }
                    }
                    if (order == "1") {
                        for (pair<string, unsigned int> s: ordered_students) {
                            cout << "Aluno: " << s.first << "   Codigo: " << s.second << endl;
                            student_count++;
                        }
                    }
                    if (order == "2") {
                        auto it = ordered_students.end();
                        for (it--; it != ordered_students.begin(); it--) {
                            cout << "Aluno: " << it->first << "   Codigo: " << it->second << endl;

                            student_count++;
                        }
                        cout << "Aluno: " << it->first << "   Codigo: " << it->second << endl;
                        student_count++;
                    }
                    cout << "\n";
                    cout << "No total sao: " << student_count << " alunos" << "\n" << endl;
                    return 0;
                }
            }


            //listagem de alunos total
            if (type == "2") {
                int student_count = 0;
                cout << "Todas os alunos serao listados\n\t1.Para Continuar\n\t0.Para voltar" << endl;
                cin >> mode;
                while (!is_in(mode, 0, 1)) {
                    cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                    cin >> mode;
                }
                if (mode == "0") goto menuAnterior2_Students;
                cout << "Criterio de ordenacao:\n\t1.Crescente\n\t2.Decrescente" << endl;
                cin >> order;
                while (!is_in(order, 1, 2)) {
                    cout << "Sintase errada.\nPor favor reintroduzir:" << endl;
                    cin >> order;
                }
                set<Student *, decltype(&set_compareLessthan_student)> students(&set_compareLessthan_student);
                for (Student aluno: database->getStudents()) {
                    Student *s_p = new Student(aluno);
                    students.insert(s_p);
                }
                if (order == "1") {
                    for (Student *s: students) {
                        cout << "Aluno: " << s->get_name() << "   Codigo: " << s->get_num() << endl;
                        delete s;
                        student_count++;
                    }
                }
                if (order == "2") {
                    auto it = students.end();
                    for (it--; it != students.begin(); it--) {
                        cout << "Aluno: " << (*it)->get_name() << "   Codigo: " << (*it)->get_num() << endl;
                        delete (*it);
                        student_count++;
                    }
                    cout << "Aluno: " << (*it)->get_name() << "   Codigo: " << (*it)->get_num() << endl;
                    delete (*it);
                    student_count++;
                }
                cout << "\n";
                cout << "Existem " << student_count << " alunos no total." << "\n" << endl;
                return 0;
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
                string n_c;
                menuAnterior3_horario:
                cout << "\t1.Pelo nome\n\t2.Pelo codigo\n\t0.Voltar" << endl;
                cin >> n_c;
                while (!is_in(n_c, 0, 2)) {
                    cout << "Sintase errada, Por favor,reintroduzir" << endl;
                    cin >> n_c;
                    if (n_c == "0") goto menuAnterior1_horario;
                }
                if (n_c == "0") goto menuAnterior1_horario;

                //caso listagem de horario do estudante for por nome
                if (n_c == "1") {
                    cout << "Introduza o nome do estudante:\n\t0.Voltar" << endl;
                    cin.ignore();
                    getline(cin, student);
                    int s = database->find_student_num_by_name(student);
                    if (student == "0") goto menuAnterior3_horario;
                    while (s == 1) {
                        cout << "Nome nao encontrado,reintroduzir:" << endl;
                        cin >> student;
                        s = database->find_student_num_by_name(student);
                        if (student == "0") goto menuAnterior3_horario;
                    }

                    vector<pair<pair<string, string>, Slot>> timetable;
                    list<UCTurma *> ucturmas = database->get_student_timetable(s);
                    for (UCTurma *ucturma: ucturmas) {
                        for (Slot aula: ucturma->get_slots()) {
                            timetable.push_back({ucturma->get_uc_turma(), aula});
                        }
                    }
                    cout << "Horario do estuante: " << s << "\n\n";
                    std::sort(timetable.begin(), timetable.end(), slotsLessthan1);
                    //aula é um par de <UCturma<uc,turma>,Slot>
                    for (pair<pair<string, string>, Slot> aula: timetable) {
                        cout << aula.second.getDay() << "\n";
                        cout << "Aula: " << aula.first.first << endl;
                        cout << "Comeco: " << aula.second.getStart() << "h" << '\t' << "Fim:" << aula.second.get_end()
                             << "h" << "\t" << "Duracao: " << aula.second.getDuration() << "h" << "\t" << "Tipo: "
                             << aula.second.getType() << "\t" << "Turma: " << aula.first.second << endl;
                        cout << "\n";
                    }
                    return 0;
                }

                //caso listagem do horario do estudante for por codigo
                if(n_c=="2"){
                    cout << "Introduza o numero do estudante(ex:202201001) ou nome:\n\t0.Para voltar" << endl;
                    cin >> student;
                    //verificar se existe o aluno na base de dados;
                    while(!is_number(student)) {
                        cout<<"Codigo invalido,reintroduzir:"<<endl;
                        cin>>student;
                    }
                    Student search = database->get_student_by_num(stoi(student));
                    if (student == "0") goto menuAnterior3_horario;
                    while(search.get_num() == 0){
                        cout<<"Codigo de estudante nao existente, reintroduzir:"<<endl;
                        cin>>student;
                        while(!is_number(student)) {
                            cout<<"Codigo invalido,reintroduzir:"<<endl;
                            cin>>student;
                        }
                        search = database->get_student_by_num(stoi(student));
                        if (student == "0") goto menuAnterior3_horario;
                    }


                    vector< pair<pair<string, string>, Slot>> timetable;
                    list<UCTurma*> ucturmas=database->get_student_timetable(stoi(student));
                    for(UCTurma* ucturma:ucturmas){
                        for(Slot aula:ucturma->get_slots()){
                            timetable.push_back({ucturma->get_uc_turma(),aula});
                        }
                    }
                    std::sort(timetable.begin(),timetable.end(), slotsLessthan1);
                    //aula é um par de <UCturma<uc,turma>,Slot>
                    cout << "Horario do estudante: " << student << "\n\n";
                    for(pair<pair<string,string>,Slot> aula:timetable){
                        cout<<aula.second.getDay()<<endl;
                        cout<<"Aula: "<<aula.first.first<<endl;
                        cout<<"Comeco: "<<aula.second.getStart()<<"h\t"<<"Duracao: "<<aula.second.getDuration()<<"h\t"<<"Tipo: "<<aula.second.getType()<<" \t"<<"Turma: "<<aula.first.second<<endl;
                        cout<<"\n";
                    }
                    return 0;
                }

            }


            //caso modo de listagem por turma
            if(mode=="2"){
                cout << "Introduza o numero da turma(ex:1LEIC01):\n\t0.Para voltar" << endl;
                cin>>turma;
                //finds if turma is in database
                bool not_found=true;

                for(UCTurma target:database->getUcTurmas()){
                    if(target.get_uc_turma().second==turma) not_found=false;
                }
                while(not_found){
                    cout<<"numero de turma nao existente,reintroduzir:"<<endl;
                    cin>>turma;
                    for(UCTurma target:database->getUcTurmas()){
                        if(target.get_uc_turma().second==turma) not_found=false;
                    }
                    if(turma=="0") goto menuAnterior1_horario;
                }
               if(turma=="0") goto menuAnterior1_horario;

                vector<pair<string,Slot>> timeTable=database->get_turma_timetable(turma);
                std::sort(timeTable.begin(), timeTable.end(), slotsLessthan);
                for(pair<string,Slot> aula: timeTable){
                    cout<<aula.second.getDay()<<endl;
                    cout<<"Turma: "<<aula.first<<endl;
                    cout<<"\t"<<"Comeco: "<<aula.second.getStart()<<"h\t"<<"FIm: "<<aula.second.get_end()<<"h\t"<<"Duracao: "<<aula.second.getDuration()<<"h\t"<<"Tipo: "<<aula.second.getType()<<endl;
                    cout<<"\n";
                }
                return 0;
            }

            //Listagem do horario por UC
            if(mode=="3"){
                cout << "Introduza o codigo da UC:\n\t0.Para voltar" << endl;
                cin >> uc;
                UCTurma target= UCTurma(uc,"");
                auto it = lower_bound(database->getUcTurmas().begin(),database->getUcTurmas().end(),target);
                while(it==database->getUcTurmas().end()){
                    cout<<"Codigo da UC invalido, reintroduzir:"<<endl;
                    cin>>uc;
                    target= UCTurma(uc,"");
                    it = lower_bound(database->getUcTurmas().begin(),database->getUcTurmas().end(),target);
                }
                if(uc=="0") goto menuAnterior1_horario;

                cout << "Introduza tipo de listagem:\n\t0.Para voltar" << endl;
                vector<pair<string,Slot>> timetable=database->get_uc_timetable(uc);
                std::sort(timetable.begin(),timetable.end(),slotsLessthan);
                for(pair<string,Slot> aula:timetable){
                    cout<<aula.second.getDay()<<endl;
                    cout<<"Turma: "<<aula.first<<endl;
                    cout<<"Comeco: "<<aula.second.getStart()<<"h\t"<<"FIm: "<<aula.second.get_end()<<"h\t"<<"Duracao: "<<aula.second.getDuration()<<"h\t"<<"Tipo: "<<aula.second.getType()<<endl;
                    cout<<"\n";
                }
                return 0;
            }
        }
    }


    //Menu das alteracoes
    else if(userInput=="2"){
        menuAlteracoes0: string criteria, option,y_n,operation;
        string identity, uc,turma,student;
        cout<<"Introduzir o numero da opcao:\n\t1.Iniciar bloco de pedidos\n\t2.Processar um bloco de pedido\n\t3.Processar todos os blocos de pedidos\n\t0.Voltar"<<endl;
        cin>>operation;
        while(!is_in(operation,0,3)){
            cout<<"Sintase errada, por favor reintroduzir:"<<endl;
            cin>>operation;
        }
        if(operation=="0"){
            goto MenuPrincipal;
        }


        //caso Iniciar bloco de pedidos
        if(operation=="1"){
            menuAlteracoes_aluno:cout << "Introduza o numero de estudante para efetuar alteracoes sobre este: \n\t0.Para voltar" << endl;
            cin >> identity;

            //verificar se existe o aluno na base de dados;
            Student search = database->get_student_by_num(stoi(identity));
            if (identity == "0") goto MenuPrincipal;
            while(search.get_num() == 0) {
                cout << "Codigo de estudante nao existente, reintroduzir:" << endl;
                cin >> identity;
                while (!is_number(identity)) {
                    cout << "Codigo invalido,reintroduzir:" << endl;
                    cin >> identity;
                }
                search = database->get_student_by_num(stoi(identity));
                if (identity == "0") goto MenuPrincipal;
            }

            maisAlteracoesMesmoAluno:
            cout<< "Introduza o numero do criterio de alteracoes:\n\t1.Adicionar aluno a turma para determinada UC\n\t2.Remover aluno de uma turma para determinada UC\n\t3.Remover todas UCs relacionadas com uma turma do aluno\n\t4.Remover todas Turmas relacionadas com UC do aluno\n\t0.Voltar"<<endl;
            cin >> criteria;
            while (!is_in(criteria, 0, 4)) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> criteria;
            }
            if (criteria == "0") goto menuAlteracoes0;


            //adicionar uma UCTurma em especifico a um estudante
            if (criteria == "1") {

                cout << "Introduza: " << endl;
                cout<<"UC: "<<endl;
                cin >> uc;
                cout<<"Turma: "<<endl;
                cin>>turma;
                Request request= Request("add",stoi(identity),uc,turma);
                processes.push_back(request);
            }

            //remover uma UCTurma em especifico de um estudante
            if (criteria == "2") {
                cout << "Introduza: " << endl;
                cout<<"UC: "<<endl;
                cin >> uc;
                cout<<"Turma: "<<endl;
                cin>>turma;
                Request request= Request("remove",stoi(identity),uc,turma);
                processes.push_back(request);

            }

            //remover todas as UCTurmas com uma certa turma de um estudante (type é "remove", uc fica em branco)
            if (criteria == "3") {
                cout << "Introduza a turma para que o aluno deixe de estar em todas as UC relacionados com essa turma: " << endl;
                cout<<"Turma: "<<endl;
                cin>>turma;
                Request request= Request("remove",stoi(identity),"",turma);
                processes.push_back(request);
            }

            //remover todas as UCTurmas com uma certa UC de um estudante(type é "remove", turma fica em branco)
            if (criteria == "4") {
                cout << "Introduza a UC para que o aluno deixe de estar em todas as turmas relacionados com ela: " << endl;
                cin >> uc;
                Request request= Request("remove",stoi(identity),uc,"");
                processes.push_back(request);
            }
            cout<<"Mais alteracoes?\n\t1.Sim\n\t2.Nao"<<endl;
            cin>>option;
            while (!is_in(option, 1, 2)) {
                cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                cin >> option;
            }
            if(option=="1"){
                cout<<" Do mesmo aluno?\n\t 1.Sim\n\t2.Nao"<<endl;
                cin>>y_n;
                while (!is_in(option, 1, 2)) {
                    cout << "Sintaxe errada.\nPor favor, reintroduzir:" << endl;
                    cin >> y_n;
                }
                if(y_n=="1"){
                    goto maisAlteracoesMesmoAluno;
                }
                else{
                    goto menuAlteracoes_aluno;
                }
            }
            else if(option=="2") {
                requestProcesser->add_request_list(processes);
                processes.clear();
                goto menuAlteracoes0;
            }
            return 0;
        }


        //caso user pretenda processar um bloco de pedidos
        else if(operation=="2"){
            if(requestProcesser->queue_empty()){
                cout<<"Ainda nao ha processos para executar, a voltar..."<<"\n"<<endl;
                return 0;
            }
            int process_path=requestProcesser->process_next_request_block();
            if(process_path==0){
                int conflicts=requestProcesser->check_for_problems();
                if(conflicts==0){
                    cout<<"O ultimo bloco de pedidos sera processado: "<<endl;
                    requestProcesser->save_changes();
                }
                else if(conflicts==1){
                cout<<"Error, sobreposicao de horario ou UC-Turma incorreto,alteracoes nao foram feitas"<<endl;
                requestProcesser->discard_changes();
                }
                else if (conflicts==2){
                    cout<<"Este bloco de pedidos ira causar um desequilibrio de turmas e UCs, pretende continuar?: \n\t1.Sim\n\t2.Nao"<<endl;
                    cin>>y_n;
                    if(y_n=="1"){
                        cout<<"O ultimo bloco de pedidos sera processado com o desequilibrio"<<endl;
                        requestProcesser->save_changes();
                    }
                    else if(y_n=="2"){
                        cout<<"O ultimo bloco de pedidos nao sera processado, alteracoes nao foram feitas"<<endl;
                        requestProcesser->discard_changes();
                    }
                }
            }
            if(process_path==1){
                cout<<"Error, UC-Turma incorreto,alteracoes nao foram feitas"<<endl;
                requestProcesser->discard_changes();
            }
            cout<<"\n"<<endl;
            return 0;
        }


        //caso user queira processar todos os blocos de pedidos
        if(operation=="3"){
            if(requestProcesser->queue_empty()){
                cout<<"Ainda nao ha processos para executar,a voltar..."<<"\n"<<endl;
                return 0;
            }
            int block_count=1;
            while(!requestProcesser->queue_empty()){
                int process_path=requestProcesser->process_next_request_block();
                if(process_path==0){
                    int conflicts=requestProcesser->check_for_problems();
                    if(conflicts==0){
                        cout<<"O ultimo bloco de pedidos sera processado: "<<endl;
                        requestProcesser->save_changes();

                    }
                    else if(conflicts==1){
                        cout<<"Error, sobreposicao de horario ou UC-Turma incorreto no bloco "<<block_count<<",alteracoes nao foram feitas para esse bloco de pedidos"<<endl;
                        requestProcesser->discard_changes();
                    }
                    else if (conflicts==2){
                        cout<<"O bloco de pedidos "<<block_count<<" ira causar um desequilibrio de turmas e UCs, pretende continuar?: \n\t1.Sim\n\t2.Nao"<<endl;
                        cin>>y_n;
                        if(y_n=="1"){
                            cout<<"O ultimo bloco de pedidos sera processado com o desequilibrio"<<endl;
                            requestProcesser->save_changes();
                        }
                        else if(y_n=="2"){
                            cout<<"O bloco de pedidos "<<block_count<<" nao sera processado, alteracoes nao foram feitas para esse bloco de pedidos"<<endl;
                            requestProcesser->discard_changes();
                        }
                    }
                }
                if(process_path==1){
                    cout<<"Error, UC-Turma incorreto no bloco de pedidos "<<block_count<<",alteracoes nao foram feitas nela para esse bloco de pedidos"<<endl;
                    requestProcesser->discard_changes();
                }
                block_count++;
            }
        }
        cout<<"\n";
        return 0;
    }


    //if user chooses to load state from previous execution
    if(userInput=="3"){
        requestProcesser->read_requests_from_file();
        cout<<"O estado da execucao anterior do programa foi carregado"<<"\n"<<endl;
        return 0;
    }


    //if user chooses to save the current program state
    if(userInput=="4"){
        requestProcesser->write_requests_to_file();
        database->write_students_to_file();
        cout<<"O estado do programa foi guardado para uma proxima utilizacao"<<"\n"<<endl;
        return 0;
    }
    return 0;
}


