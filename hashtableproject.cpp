#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;
const int tablesize = 10;

class Node { //class node
public:
    string key;
    int value;
    Node* next;
    int scope;
    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
        this->next = NULL;
        this->scope = 1;
    }
};

class HashMap { //class hashmap
private:
    Node** htable;

public:
    HashMap() {
        htable = new Node * [tablesize];
        for (int i = 0; i < tablesize; i++)
            htable[i] = NULL;
    }

    int HashFunc(string);
    void Insert(string, int, bool);
    void Search(string, int, bool, int, char);
    string Operators(int, char, string);
    void PlusMinus(char, string);
};

int HashMap::HashFunc(string key) { //hashes the key
    int count = 1;
    int hashNum = 0;
    for (int i = 0; i < key.length(); i++) {
        char x = key.at(i);
        hashNum += int(x) * count;
        count++;
    }
    return hashNum % tablesize;
}

void HashMap::Insert(string key, int value, bool out) { //stores the variable in the hash table and its respective value
    int hash = HashFunc(key);
    Node* entry = htable[hash];
    bool inserted = false;

    if (htable[hash] == NULL) { // if there is nothing in the entry for the hash value index
        htable[hash] = new Node(key, value);
        htable[hash]->next = NULL;
        if (out == true) {
            htable[hash]->scope++;
        }
    }
    else { //replace value if value was reassigned a new value or add it to the next node in the chain
        Node* entry = new Node(key, value);
        while (htable[hash]->next != NULL) {
            if (htable[hash]->key == key) {
                htable[hash]->value = value;
                inserted = true;
                break;
            }
            htable[hash] = htable[hash]->next;
        }
        if (inserted == false) {
            if (out == true) {
                entry->scope++;
            }
            htable[hash]->next = entry;
        }
    }
}

void HashMap::Search(string key, int start, bool oprtr, int y, char z) { //searches for the variable
    int hash = HashFunc(key);
    bool found = false;
    Node* entry = htable[hash];
    if (entry == NULL) {
        cout << key << " IS UNDEFINED " << endl;
    }
    while (entry != NULL) //traverse through hash table
    {
        if (entry->key == key)
        {
            if (start < entry->scope) { //if the entry isn't in the same scope
                cout << key << " IS UNDEFINED " << endl;
                found = true;
                break;
            }
            if (oprtr && start >= entry->scope) { // if there are no operators and if it is in the same scope
                cout << key << " IS " << entry->value << endl;
                found = true;
                break;
            }
            else if (!oprtr) { // if there is an operator
                cout << Operators(y, z, key) << endl;
                found = true;
                break;
            }
        }
        entry = entry->next;
    }
    if (found ==  false) {
        cout << key << " IS UNDEFINED " << endl;
    }
}

string HashMap::Operators(int x, char s, string key) { //performs the respective operator task
    int a = HashFunc(key);
    Node* entry = htable[a];
    if (entry == NULL) {
        return (key + " IS UNDEFINED ");
    }
    if (entry->key == key) {
        int val = entry->value;
        string output;
        if (s == '+') { //addition
            val += x;
            output = (key + " + " + to_string(x) + " IS " + to_string(val));
            return output;
        }
        else if (s == '-') { //subtraction
            val -= x;
            output = (key + " - " + to_string(x) + " IS " + to_string(val));
            return output;
        }
        else if (s == '*') { //multiplication
            val *= x;
            output = (key + " * " + to_string(x) + " IS " + to_string(val));
            return output;
        }
        else if (s == '/') { //division
            val /= x;
            output = (key + " / " + to_string(x) + " IS " + to_string(val));
            return output;
        }
        else if (s == '^') { //exponent
            val ^= x;
            output = (key + " ^ " + to_string(x) + " IS " + to_string(val));
            return output;
        }
        else if (s == '%') { //modulo
            val %= x;
            output = (key + " % " + to_string(x) + " IS " + to_string(val));
            return output;
        }
    }
    return "";
}

void HashMap::PlusMinus(char s, string key) { //performs increment/decrement
    int hash = HashFunc(key);
    Node* entry = htable[hash];
    if (entry == NULL) {
        cout << key << " IS UNDEFINED " << endl;
    }
    if (entry->key == key) {
        if (s == '+') { //increment
            entry->value += 1;
        }
        else if (s == '-') { //decrement
            entry->value -= 1;
        }
    }
}

int main() {
    string cmd, name, num;
    int start = 0, i = 0, x = 0;
    HashMap table;
    size_t pos;

    ifstream borg("borg2.txt");
    while (getline(borg, cmd)) {
        name = "";
        num = "";
        i = 0;

        if ((pos = cmd.find("START")) != string::npos) { //START ______________________________________
            start += 1;
        }

        else if (((pos = cmd.find("VAR")) != string::npos) && start >= 1) { //VAR ______________________________________
            i = 4;
            while (cmd[i] != ' ') {
                name += cmd[i];
                i++;
            }
            i += 3;
            while (i != cmd.length()) {
                num += cmd[i];
                i++;
            }
            x = 0;
            stringstream val(num);
            val >> x;
            if (start > 1) {
                table.Insert(name, x, true);
            }
            else {
                table.Insert(name, x, false);
            }

        }

        else if ((pos = cmd.find("PRINT")) != string::npos) //PRINT ______________________________________
        {
            int first = cmd.find(" ");
            int len = cmd.length() - 1;
            first++;
            if (!isdigit(cmd[len])) { //if no operators exist
                while (first != cmd.length()) {
                    name += cmd[first];
                    first++;
                }
                table.Search(name, start, true, 0, ' ');
            }
            else {
                while (cmd[first] != ' ' && cmd[first] != '+' && cmd[first] != '-' && start == 1) {
                    name += cmd[first];
                    first++;
                }
                pos = cmd.find(" + "); //addition
                if (pos != string::npos) {
                    i = cmd.find("+") + 2;
                    while (i != cmd.length()) {
                        num += cmd[i];
                        i++;
                    }
                    x = 0;
                    stringstream val(num);
                    val >> x;
                    table.Search(name, start, false, x, '+');
                }

                pos = cmd.find(" / "); //division
                if (pos != string::npos) {
                    i = cmd.find("/") + 2;
                    while (i != cmd.length()) {
                        num += cmd[i];
                        i++;
                    }
                    x = 0;
                    stringstream val(num);
                    val >> x;
                    table.Search(name, start, false, x, '/');
                }

                pos = cmd.find(" - "); //subtraction
                if (pos != string::npos) {
                    i = cmd.find("-") + 2;
                    while (i != cmd.length()) {
                        num += cmd[i];
                        i++;
                    }
                    x = 0;
                    stringstream val(num);
                    val >> x;
                    table.Search(name, start, false, x, '-');
                }

                pos = cmd.find(" * "); //multiplication
                if (pos != string::npos) {
                    i = cmd.find("*") + 2;
                    while (i != cmd.length()) {
                        num += cmd[i];
                        i++;
                    }
                    x = 0;
                    stringstream val(num);
                    val >> x;
                    table.Search(name, start, false, x, '*');
                }
            }
        }
        else if ((pos = cmd.find("++")) != string::npos || (pos = cmd.find("--")) != string::npos) { //INCREMENT/DECREMENT___________________
            while (cmd[i] != '+' && cmd[i] != '-') {
                name += cmd[i];
                i++;
            }
            pos = cmd.find("++"); //increment
            if (pos != string::npos) {
                table.PlusMinus('+', name);
            }
            pos = cmd.find("--"); //decrement
            if (pos != string::npos) {
                table.PlusMinus('-', name);
            }
        }
        else if ((pos = cmd.find(" = ")) != string::npos) { //CHANGING VALUES________________________________________
            while (cmd[i] != ' ') {
                name += cmd[i];
                i++;
            }
            i = cmd.find("=");
            i += 2;
            while (i != cmd.length()) {
                num += cmd[i];
                i++;
                x = 0;
            }
            stringstream val(num);
            val >> x;
            table.Insert(name, x, false);
        }
        else if (cmd[0] == 'C' && cmd[2] == 'M') //COMMENTS_________________________________________________
        {
            continue;
        }
        else if (cmd[0] == 'F' && cmd[5] == 'H') { //FINISH______________________________________________
            start -= 1;
        }
    }
    borg.close();
    return 0;
}

/* OUTPUT FOR SAMPLE SOURCE PROGRAM
BORAMIR IS 25
LEGOLAS IS 101
GANDALF IS UNDEFINED
BORAMIR * 2 IS 52
GANDALF IS 49
BORAMIR IS 26
GANDALF IS UNDEFINED
LEGOLAS IS 1000
LEGOLAS IS 1000
LEGOLAS IS 999
*/
