//
// Created by Afonso on 30/10/2022.
//

#include "../Headers/RequestProcesser.h"

void RequestProcesser::add_request_list(list<Request> requests) {
    request_blocks.push(requests);
}

void RequestProcesser::process_next_request_block() {
    set<Student> new_students = database->getStudents();

}
