#include <iostream>
#include "Headers/CSVReader.h"
#include "Headers/Interface.h"
#include "Headers/RequestProcesser.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    CSVReader reader;
    reader.populate();
    RequestProcesser processer = RequestProcesser(reader);
    Interface interface = Interface(reader,&processer);


    while(true){
        bool terminated;
        terminated=interface.initiate();
        if(terminated) break;
    }
    return 0;

}
