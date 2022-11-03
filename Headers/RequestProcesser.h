//
// Created by Afonso on 30/10/2022.
//

#ifndef AEDOUTRO_REQUESTPROCESSER_H
#define AEDOUTRO_REQUESTPROCESSER_H

#include "Request.h"
#include "CSVReader.h"
#include <list>
#include <queue>

class RequestProcesser {
private:
    queue<list<Request>> request_blocks;
    CSVReader* database;
    set<string> affected_uc;
    set<Student> new_students;
    set<pair<string,string>> affected_uc_turma;
public:
    RequestProcesser(CSVReader& reader);
    void add_request_list(list<Request> requests);
    int process_next_request_block();
    int check_for_problems();
    void save_changes();
    void discard_changes();
    void write_requests_to_file();
    int read_requests_from_file();
    bool queue_empty() const;
};

#endif //AEDOUTRO_REQUESTPROCESSER_H
