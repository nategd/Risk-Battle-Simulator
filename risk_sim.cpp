//
//  main.cpp
//  Risk Simulator
//
//  Created by Nathan Donaldson on 11/24/16.
//  Copyright © 2016 Nathan Donaldson. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <time.h> 
#include <stdlib.h>

const int MAX_ATTACK = 3; //this way the number of dice can be changed easily
const int MAX_DEFENSE = 2;

using namespace std;

//mini helpers
bool is_number(const string& s) {
    return !s.empty() && find_if(s.begin(),
                                 s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

int get_and_parse(string type) {
    cout << "What is the " + type + "? ";
    string temp;
    getline(cin, temp);
    cout << endl;
    int x = 1;
    if (temp[0] == '-') {
        x = -1;
        temp = temp.substr(1);
    }
    if (is_number(temp)) {
        return x * atoi(temp.c_str());
    }
    return 0;
}

bool contin(string question) {
    string go_again;
    cout << question;
    getline(cin, go_again);
    cout << endl;
    return go_again == "y" || go_again == "Y" || go_again == "yes" || go_again == "Yes";

}

void state(int attack, int defense) {
    cout << "Current state: " << endl;
    cout << "Attack: " + to_string(attack) << endl;
    cout << "Defense: " + to_string(defense) << endl << endl;
}

//core declarations
void run(int attack, int defense);


int main() {
    bool cont = true;
    while (cont) {
        
        int attack = get_and_parse("attack number");
        if (attack > 0) {
            
            int defense = get_and_parse("defense number");
            if (defense > 0) {
                run(attack, defense);
            }
            else {
                cout << "invalid defense argument" << endl;
            }
        }
        else {
            cout << "invalid attack argument" << endl;
        }
        cont = contin("Prepare for new round (y/n)? ");
    }
    
    cout << "Exiting the program" << endl;
    return 0;
}


void run(int att, int def) {
    int threshold = get_and_parse("threshold");
    vector<int> attack;
    vector<int> defense;
    int seed = rand() % 42;
    bool cont = true;
    srand((time(NULL) + seed * 15 + att * 6 + def) % 12453);
    while (cont && att > 1 && def > 0) {
        int draws = 0;
        while (draws < att && draws < MAX_ATTACK) {
            attack.push_back(rand() % 6 + 1);
            ++draws;
            ++seed;
        }
        sort(attack.begin(), attack.end(), greater<int>());
        draws = 0;
        while (draws < def && draws < MAX_DEFENSE) {
            defense.push_back(rand() % 6 + 1);
            ++draws;
            ++seed;
        }
        sort(defense.begin(), defense.end(), greater<int>());
        
        for (int i = 0; i < defense.size() && i < attack.size(); ++i) {
            if (defense[i] < attack[i]) def--;
            else att--;
        }
        
        if (att <= def + threshold) {
            cout << "Threshold reached" << endl;
            state(att, def);
            if (!contin("Continue (y/n)? ")) {
                cont = false;
            }
            else {
                threshold = get_and_parse("new threshold");
            }
        }
        
        attack.clear();
        defense.clear();
        attack.resize(0);
        defense.resize(0);
    }
    state(att, def);
}





















