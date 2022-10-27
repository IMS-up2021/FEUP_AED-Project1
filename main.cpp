#include <iostream>
#include "Headers/CSVReader.h"
#include "Headers/ProcessingTool.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    CSVReader reader;
    /*reader.populate();*/
    int userInput;
    ProcessingTool interface;
    UCTurma ucturma= *(reader.getUcTurmas().begin());
    cout<<ucturma.get_uc_turma().first<<endl;
    while(true){
        cout<<"Introduza o numero do comando:\n\t1.Listagem\n\t2.Alteracoes\n\t0.Sair do programa"<<endl;
        cin>>userInput;
        if (userInput==0){
            break;
        }
        interface.listShow(userInput);

    }
    return 0;

}
