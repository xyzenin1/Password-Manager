#include "encdec.h"

encdec manager;

// display any message
void displayMessage(const string& msg) {
    cout << msg << endl;
}

// display menu
void displayMenu() {
    displayMessage("\n Password Manager");
    displayMessage("1. Add Password");
    displayMessage("2. View Passwords");
    displayMessage("3. Encrypt Passwords");
    displayMessage("4. Decrypt Passwords");
    displayMessage("5. Set Master Key");

    displayMessage("6. Exit");
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
    bool encryptStatus;
    manager.loadMasterKey();
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
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
            encryptStatus = manager.isEncrypted();
            if (encryptStatus == false) {
                manager.encrypt();
            }
            else {
                cerr << "Passwords are already encrypted!" << endl;
                break;
            }
            break;
        case 4:
            encryptStatus = manager.isEncrypted();
            if (encryptStatus == true) {
                manager.decrypt();
            }
            else {
                cerr << "Passwords are already decrypted!" << endl;
                break;
            }
            break;
        case 5:
            manager.setMasterKey();
            break;
        case 6:
            cout << "Bye Bye!";
            break;
        default:
            cerr << "Invalid choice, please try again.\n";
            break;
    }
    
        
    } while (choice != 6);

    return 0;
}