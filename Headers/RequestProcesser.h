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
public:
    RequestProcesser(CSVReader& reader);
    void add_request_list(list<Request> requests);
    int process_next_request_block();
    void save_changes() const;
};

#endif //AEDOUTRO_REQUESTPROCESSER_H
