#ifndef PROJECT_1___PERSONALITY_TEST_QUESTION_H
#define PROJECT_1___PERSONALITY_TEST_QUESTION_H
#include <string>

using namespace std;

class question {
public:
    int get_category_id();
    string get_question();
    char get_yes_answer();
    char get_no_answer();

    question() {
        category_id = -1;
        question_str = "";
        yes_answer = 'Z';
        no_answer = 'Y';
    }

    question(int catID, string q, char yes, char no) {
        category_id = catID;
        question_str = q;
        yes_answer = yes;
        no_answer = no;
    }

private:
    int category_id;
    string question_str;
    char yes_answer;
    char no_answer;
};


#endif //PROJECT_1___PERSONALITY_TEST_QUESTION_H
