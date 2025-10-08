#include <iostream>
#include <string>
#include <fstream>      // read/write files
#include <limits>

using namespace std;

// display any message
void displayMessage(const string& msg) {
    cout << msg << endl;
}

// display menu
void displayMenu() {
    displayMessage("\n Password Manager");
    displayMessage("1. Add Password");
    displayMessage("2. View Passwords");
    displayMessage("3. Exit");
    displayMessage("Enter your choice: ");
}

void savePassword(const string& site, const string& password) {
    ofstream file("password.txt", ios::app);    // ios::app so it appends the file instead of overwriting every time it opens
    if (file.is_open()) {
        file << site << " " << password << "\n";
        file.close();       // close file
        displayMessage("Password saved successfully!");
    }
    else {
        cerr << "Error: unable to open file!\n";
    }
}

void viewPassword() {
    ifstream file("password.txt");
    if (file.is_open()) {
        string site, password;
        displayMessage("\nSaved Passwords: ");
        while (file >> site >> password) {
            cout << "Site: " << site << "\nPassword: " << password << '\n';
        }
        file.close();
    }
    else {
        cerr << "\nNo passwords saved yet!\n";
    }
}

int main() {

    int choice;
    string site, password;
    
    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    switch(choice) {
        case 1:
            displayMessage("Enter the site name: ");
            cin >> site;
            displayMessage("Enter password: ");
            cin >> password;
            savePassword(site, password);
            break;
        case 2:
            viewPassword();
            break;
        case 3:
            cout << "Bye Bye!";
            break;
        default:
            cerr << "Invalid choice, please try again.\n";
            break;
    }
    
        
    } while (choice != 3);

    return 0;
}