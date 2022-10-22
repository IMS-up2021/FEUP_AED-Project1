#include <iostream>
#include "Headers/CSVReader.h"
#include "Headers/ProcessingTool.h"
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    CSVReader reader;
    /*reader.populate();*/
    string userInput;
    ProcessingTool interface;
    interface.initiate();
    while(true){
        cout<<"Introduza um comando"<<endl;
        cin>>userInput;
        if (userInput=="quit"){
            break;
        }
        interface.addProcess(userInput);
        interface.executeProcess();

    }
    return 0;

}
