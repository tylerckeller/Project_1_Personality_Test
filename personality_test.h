#ifndef _PERSONALITY_TEST_H
#define _PERSONALITY_TEST_H

#include <string>
#include <vector>
#include <iostream>
#include "question.h"

using namespace std;

// personality test class
class personality_test {
    public:
        bool load(istream&);
        void printout(vector<question> questions);
        void run_test();
        string analyze_personality();
        void categorize_output(string);
        void save_output(string);
        vector<question> get_questions();
        void questions_add(question q);
        string get_type();
        string get_category();
        string get_role();
        string get_description();
        void set_type(string s);
        void set_category(string s);
        void set_role(string s);
        void set_description(string s);
        vector<string> scores = {"", "", "", ""};

    private:
        vector<question> questions = {};
        string type;
        string category;
        string role;
        string description;
};

#endif
