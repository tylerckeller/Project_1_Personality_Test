#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "personality_test.h"

using namespace std;


vector<question> personality_test::get_questions() {
    return questions;
}

string personality_test::get_category() {
    return category;
}

string personality_test::get_type() {
    return type;
}

string personality_test::get_role() {
    return role;
}

string personality_test::get_description() {
    return description;
}

void personality_test::set_category(string s) {
    this->category = s;
}

void personality_test::set_type(string s) {
    this->type = s;
}

void personality_test::set_role(string s) {
    this->role = s;
}

void personality_test::set_description(string s) {
    this->description = s;
}

void personality_test::questions_add(question q) {
    questions.push_back(q);
}


/* Load method
 * 1) Provided an istream object, read in each line and process them accordingly
 * 2) Ensure to see if the input is "correct" (do at least one simple check, like first character is a number)
 * Input: istream object
 * Output: Boolean
 */
bool personality_test::load(istream &in) {
    bool b = false;
    bool first = true;
    string s;
    int cID;
    char y;
    char n;
    while(!in.eof()) {

        string q;

        getline(in, s);

        //skips first line
        if (first) {
            first = false;
            continue;
        }

        //skips credits line
        if (s[0] == '@') {
            continue;
        }

        //checks first char is int and third and fifth chars are alphabetic
        if (isdigit(s[0]) && isalpha(s[2]) && isalpha(s[4])) {

            //b set to true bc we read in a question line
            b = true;
            istringstream sin(s);
            sin >> cID;
            sin >> y;
            sin >> n;
            while (!sin.eof()) {
                string temp;
                sin >> temp;
                q += temp + " ";
            }

            //question is appended to the questions vector
            this->questions_add(question(cID, q, y, n));
        } else {
            //questions line is broken and file can't be read in
            b = false;
            break;
        }
    }
    cout << "called load" << endl;
    cout << "returned " << b << endl;
    return b;
}

        
/* personality_test::printout method
 * 1) Printout the questions to ensure that the load method was written correctly
 * This part will not be graded, just for your own check
 */
void personality_test::printout(vector<question> questions) {
    for (question q : questions) {
        cout << q.get_category_id() << " " << q.get_yes_answer() << " " << q.get_no_answer() << " " << q.get_question() << endl;
    }
    cout << "called printout" << endl;
}


/* Run Test method
 * 1) Call proper methods in order to run the test
 * @param: None
 * @return: None, Text to Console
 */
void personality_test::run_test() {
    string output = analyze_personality();
    categorize_output(output);
    save_output(output);
}


/* Analyze Personality Method
 * 1) Ask user one question at a time
 * 2) Read in user's response and construct a vector containing the responses
 * 3) Analyze the responses to construct a personality type (eg. ENFJ)
 * @param None
 * @return string
 */
string personality_test::analyze_personality() {
    int i = 0;

    while (i < questions.size()) {

        string ans;
        cout << this->get_questions()[i].get_question() + "y/n" << endl;
        cin >> ans;

        if (ans == "y" || ans == "Y" || ans == "yes" || ans == "YES") {
            this->scores[this->get_questions()[i].get_category_id()-1] += this->get_questions()[i].get_yes_answer();
            i++;
        }

        else if (ans == "n" || ans == "N" || ans == "no" || ans == "NO") {
            this->scores[this->get_questions()[i].get_category_id()-1] += this->get_questions()[i].get_no_answer();
            i++;
        }

        else {
            cout << "Sorry, I didn't recognize your input, please type again" << endl;
        }
    }
    string output;

    for (int j = 0; j < this->scores.size(); j++) {

        char char1 = scores[j][0];

        int count_1 = 0;

        int count_2 = 0;

        for (int n = 0; n < this->scores[j].length(); n++) {

            if (this->scores[j][n] == char1) {
                count_1++;
            }

            else {
                count_2++;
            }
        }
        if (count_1 > count_2) {
            output += char1;
        }
        else {
            output += this->scores[j][1];
        }

    }

    cout << "\n" << output << endl;

    return output;
}


/* Categorize Output Method
 * 1) Read in the analysis.txt file
 * 2) Provided a user's personality type, print out to console the user's personality description
 * @param Personality type string (eg. "ENFJ")
 * @return None, Text to console
 */
void personality_test::categorize_output(string my_personality) {
    string filename;
    bool again = false;

    cout << endl;
    cout << "Please enter the analysis file name, e.g., \"analysis.txt\": ";

    cin >> filename;

    ifstream fin;

    bool first = true;
    string c;
    string t = my_personality;
    string r;
    string d;

    fin.open(filename);

    if (!fin.is_open()) {
        cout << endl;
        cout << "Error opening file \"" << filename << "\": " << endl;
        again = true;
    }

    if (again) {

        categorize_output(my_personality);

    }

    while (!fin.eof()) {

        if (again) {

            break;

        }

        string s;

        getline(fin, s);

        if (first) {
            first = false;
            continue;
        }

        istringstream sin(s);

        string type_input;

        sin >> type_input;

        if (type_input != t) {

            continue;

        }

        sin >> c;

        sin >> r;

        string temp;

        while (!sin.eof()) {

            sin >> d;

            temp += d + " ";

        }

        d = temp;

        this->set_type(my_personality);
        this->set_category(c);
        this->set_role(r);
        this->set_description(d);

        cout << endl;
        cout << "=====================" << endl;
        cout << "Your personality type is: " << this->get_type() << endl;
        cout << "The category is: " << this->get_category() << endl;
        cout << "You are: " << this->get_role() << endl;
        cout << "Description: " << this->get_description() << endl;
        cout << "=====================" << endl;

        break;
    }
}

/* Save Output
 * 1) Ask user to save or not
 * 2) If yes, ask for a file name and save the results
 * @param string (the thing to write)
 * @return None, creates a file
 */
void personality_test::save_output(string output) {
    string s;
    cout << "\nWould you like to save?" << endl;
    cin >> s;

    if (s == "y" || s == "yes" || s == "Y" || s == "YES") {

        string filename;

        cout << "Please enter a file name" << endl;

        cin >> filename;

        ofstream fout(filename);

        fout << "Your personality type is: " << this->get_type() << endl;
        fout << "\nThe category is: " << this->get_category() << endl;
        fout << "\nYou are: " << this->get_role() << endl;
        fout << "\nDescription: " << this->get_description() << endl;

    }

    else if (s == "n" || s == "no" || s == "N" || s == "NO") {

    }

    else {

        cout << "Wrong input, please try again" << endl;

        save_output(output);

    }
}
