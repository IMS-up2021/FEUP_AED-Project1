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
    /*list<Request> reqs;
    reqs.emplace_back("remove",202020047,"L.EIC003", "");
    reqs.emplace_back("remove",202020047,"L.EIC001","1LEIC07");
    reqs.emplace_back("remove",202020047, "", "1LEIC07");
    processer.add_request_list(reqs);
    int doot = processer.process_next_request_block();
    int doot2 = processer.check_for_problems();
    processer.save_changes();
    reader.write_students_to_file();*/


    while(true){
        bool terminated;
        terminated=interface.initiate();
        if(terminated) break;
    }
    return 0;

}
