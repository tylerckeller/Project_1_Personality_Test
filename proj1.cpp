#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "personality_test.h"

using namespace std;

void load_file(personality_test&);

/* main
 * Calls necessary functions in this file as well as functions in personality_test
 * @param None
 * @return None, Text to Console
 */
int main () {
    bool play_again = true;
    while(play_again) {
        cout << "====================================" << endl;
        cout << "Welcome to CSCI262 Personality Test!" << endl;
        cout << "====================================" << endl << endl;

        personality_test test;

        // Uncomment the below methods as you complete them
        load_file(test);
        test.printout(test.get_questions());
        test.run_test();

        while (true) {
            cout << "Would you like to play again?" << endl;
            string ans;
            cin >> ans;

            if (ans == "y" || ans == "yes" || ans == "Y" || ans == "YES") {

                break;

            } else if (ans == "n" || ans == "no" || ans == "N" || ans == "NO") {

                play_again = false;
                break;

            } else {

                cout << "Sorry, I didn't recognize your input, please type again" << endl;

            }
        }

    }


}

/* Load File Method
 * 1) Prompt the user for a file name. 
 * 2) Confirm that the file can be loaded
 * 3) Run personality_test::load to load in the data
 * 4) If personality_test::load fails, report this and retry
 * @param personality_test object (by reference)
 * @return None, Text to Console
 */
void load_file(personality_test& test) {
    ifstream fin;
    bool again = false;

    while (!fin.eof()) {

        string fileName;
        cout << "Please enter the input file name, e.g., \"questions.txt\": ";
        cin >> fileName;
        fin.open(fileName);

        if (!fin.is_open()){

            cout << "Error opening file \"" << fileName << "\"" << endl;
            again = true;
            break;

        }

        if (!test.load(fin)) {

            cout << "Input file \"" << fileName << "\" appears to not be a proper file!" << endl;
            again = true;
            break;

        }
    }
    if (again) {
        load_file(test);
    }
}
