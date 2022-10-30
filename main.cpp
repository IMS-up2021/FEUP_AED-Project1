#include <iostream>
#include "Headers/CSVReader.h"
#include "Headers/Interface.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    CSVReader reader;
    reader.populate();
    Interface interface = Interface(reader);

    while(true){
        bool terminated;
        terminated=interface.listShow();
        if(terminated) break;
    }
    return 0;

}
