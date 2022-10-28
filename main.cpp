#include <iostream>
#include "Headers/CSVReader.h"
#include "Headers/Interface.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    CSVReader reader;

    reader.populate();

    Interface interface;
    UCTurma ucturma= *(reader.getUcTurmas().begin());
    cout<<ucturma.get_uc_turma().first<<endl;

    while(true){
        bool terminated;
        terminated=interface.listShow();
        if(terminated) break;
    }
    return 0;

}
