#ifndef encdec_h
#define encdec_h

#include <iostream>
#include <string>
#include <fstream>      // read/write files
#include <limits>
#include <vector>

using namespace std;

class encdec {
private:
    int key;
    bool keyIsSet;

public:

    encdec(): key(0), keyIsSet(false) {};

    void encrypt();
    void decrypt();
    void setMasterKey();
    void loadMasterKey();

};

void encdec::encrypt() {
    if (keyIsSet == false) {
        cerr << "No key set! Please set one up first!";
        return;
    }

    // open file to read
    ifstream inFile("password.txt");
    if (!inFile.is_open()) {
        cerr << "Could not open password" << endl;
        return;
    }

    // create array, push passwords into array
    vector<string> lines;  
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    inFile.close();

    // if array is empty, then there are no passwords
    if (lines.empty()) {
        cerr << "No passwords set to encrypt!";
        return;
    }

    ofstream outFile("password.txt");
    if (!outFile.is_open()) {
        cerr << "File could not be opened to be written in";
        return;
    }

    for (const string& l : lines) {
        string encrypted = "";
        // XOR each character with key
        for (char ch : l) {
            encrypted += char(ch ^ key);
        }
        outFile << encrypted << "\n";
    }
    cout << "Passwords encrypted!";
    outFile.close();
}

void encdec::decrypt() {
    if (keyIsSet == false) {
        cerr << "No key set! Please set one up first!";
        return;
    }

    ifstream inFile("password.txt");
    if (!inFile.is_open()) {
        cerr << "Could not open password" << endl;
        return;
    }

    // read all lines
    vector<string> lines;  
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    inFile.close();

    // if there are no lines
    if (lines.empty()) {
        cerr << "No passwords set to decrypt!";
        return;
    }

    // decrypt and write back
    ofstream outFile("password.txt");
    if (!outFile.is_open()) {
        cerr << "File could not be opened to be written in";
        return;
    }

    for (const string& l : lines) {
        string decrypted = "";
        for (char ch : l) {
            decrypted += char(ch ^ key);
        }
        outFile << decrypted << "\n";
    }
    outFile.close();
    cout << "File decrypted successfully!" << endl;

}


void encdec::setMasterKey() {
    // check if master key already exists
    ifstream checkFile("masterkey.txt");
    if (checkFile.is_open()) {
        int existingkey;
        bool setKey = false;
        if (checkFile >> existingkey) {
            checkFile.close();
            cerr << "There already is a master key set!\n";

            char overwrite;
            cout << "Do you want to overwrite key? (y/n)" << endl;
            cin >> overwrite;

            while (!setKey) {
                if (overwrite == 'y') {
                    cout << "Enter an encryption key: ";
                    cin >> key;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max());
                        cerr << "Invalid Key! has to be a numebr!";
                        return;
                    }

                    ofstream keyfile("masterkey.txt");
                    if (keyfile.is_open()) {
                        keyfile << key;
                        keyfile.close();
                        cout << "Master key successfully set!" << endl;
                        setKey = true;
                        keyIsSet = true;
                    }
                    else {
                        cerr << "Could not save master key!" << endl;
                    }
                }
                else if (overwrite == 'n') {
                    cout << "Master key not overwritten." << endl;
                    return;
                }
                else {
                    cerr << "Not a valid choice!\n";
                }
            }


        }
        else {      // if file exists but does not have an existing key
            checkFile.close();
            cout << "Enter an encryption key: ";
            cin >> key;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max());
                cerr << "Invalid Key! has to be a numebr!";
                return;
            }

            ofstream keyfile("masterkey.txt");
            if (keyfile.is_open()) {
                keyfile << key;
                keyfile.close();
                keyIsSet = true;
                cout << "Master key successfully set!" << endl;
            }
            else {
                cerr << "Could not save master key!" << endl;
            }
            keyfile.close();
        }
        
    }
    else {      // if no file exists
        cout << "Enter an encryption key: ";
        cin >> key;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
            cerr << "Invalid Key! has to be a numebr!";
            return;
        }

        ofstream keyfile("masterkey.txt");
        if (keyfile.is_open()) {
            keyfile << key;
            keyfile.close();
            keyIsSet = true;
            cout << "Master key successfully set!" << endl;
        }
        else {
            cerr << "Could not save master key!" << endl;
        }
    }
    
}


void encdec::loadMasterKey() {
    ifstream keyfile("masterkey.txt");
    if (keyfile.is_open()) {
        keyfile >> key;
        keyfile.close();
        keyIsSet = true;
    }
    else {
        keyIsSet = false;
    }
}


#endif