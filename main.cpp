// in CmakeList.txt change final to Main (vice versa)
// and final.cpp to main.cpp (vice versa)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

char prompt();
void viewTasks();
void addTasks();

fstream file;
string directoryPath;
string fileName;
string fullPath;
vector<string> toFile;

int main() {

    char choice;
    bool done = false;
    cout << "Welcome to your To Do list Application!" << endl;
    cout << "----------------------------------------" << endl;
    // users have to specify the entire path name
    // remember to add the / at the end of the directory path
    cout << "Enter the full path to the directory you want to store the file." << endl;
    cout << "Enter: ";
    getline(cin, directoryPath);
    cout << "Enter the name of the file." << endl;
    cout << "Enter: ";
    getline(cin, fileName);
    fullPath = directoryPath + fileName;
    cout << fullPath << endl;

    do {
        choice = prompt();

        switch (choice) {
            case '1':
                viewTasks();
                cout << endl;
            break;
            case '2':
                addTasks();
                break;
            case '3':
                // delete line function
                // research how to delete / replace a specific line in a file
                break;
            case '4':
                cout << "Goodbye!" << endl;
                done = true;
                break;
            default:
                cout << "Invalid Choice!" << endl;
                break;
        }
    } while (done != true);

    return 0;
}

char prompt() {
    char choice;
    cout << "Enter one of the following:" << endl;
    cout << "1) View tasks" << endl;
    cout << "2) Add a task" << endl;
    cout << "3) Delete a task" << endl;
    cout << "4) Exit" << endl;
    cout << "Your Choice: ";
    cin >> choice;
    cin.ignore(choice, '\n');

    return choice;
}

void viewTasks() {
    string line;
    file.open(fullPath, ios::in);

    if (!file.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void addTasks() {
    string line;
    file.open(fullPath, ios::out | ios::app);

    if (!file.is_open()) {
        cout << "Unable to open file!" << endl;
        return;
    }

    cout << "Enter what you need to do: ";
    getline(cin, line);
    file << line << endl;

    file.close();

}