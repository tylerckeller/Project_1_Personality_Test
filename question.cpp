//
// Created by unknown on 9/5/2021.
//

#include "question.h"


int question::get_category_id() {
    return category_id;
}

string question::get_question() {
    return question_str;
}

char question::get_no_answer() {
    return no_answer;
}

char question::get_yes_answer() {
    return yes_answer;
}