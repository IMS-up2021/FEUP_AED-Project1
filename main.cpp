#include <iostream>
#include "Headers/CSVReader.h"
#include "Headers/Interface.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    CSVReader reader;
    Interface interface;
    interface.initiate();

    while(true){
        bool terminated;
        terminated=interface.listShow();
        if(terminated) break;
    }
    return 0;

}
