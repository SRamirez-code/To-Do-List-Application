#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Function Prototypes:
char prompt();
void viewTasks();
void addTasks();
void editTasks();
void deleteTask();

// Global variables:
fstream file;
vector<string> vectorFile;
string pathName;

int main() {
    char choice;
    bool done = false;

    cout << "Welcome to your To Do list Application!" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter the full path or the name of the file to create or open: ";
    getline(cin, pathName); // get the name of the File

    do {
        choice = prompt(); // This will print the Menu options

        switch (choice) {
            case '1':
                viewTasks(); // to view the Tasks from the File
                cout << endl;
                break;
            case '2':
                addTasks(); // to add a Task to the file and the vector
                break;
            case '3':
                editTasks(); //edit task
                break;
            case '4':
                deleteTask(); // to delete a specific line from the file
                break;
            case '5':
                cout << "Goodbye!" << endl;
                done = true; // to exit the program
                break;
            default:
                cout << "Invalid Choice!" << endl; // error check
                break;
        }
    } while (done != true); // to break out the program

    return 0;
}

// The Menu Options
char prompt() {
    char choice;
    cout << "Enter one of the following:" << endl;
    cout << "1) View tasks" << endl;
    cout << "2) Add a task" << endl;
    cout << "3) Delete a task" << endl;
    cout << "4) Exit" << endl;
    cout << "Your Choice: ";
    cin.get(choice);
    cin.ignore(choice, '\n');

    return choice;
}

void viewTasks() {
    string line;
    file.open(pathName, ios::in); // input mode, to read from the file

    // error check
    if (!file.is_open()) {
        cout << "Cannot open file :(" << endl;
        return;
    }

    vectorFile.clear(); // clear vector everytime function is called

    int count = 0;
    cout << "Here's what you have to do:" << endl;
    while (getline(file, line)) {
        // populate vector and display contents of file
        vectorFile.push_back(line);
        cout << ++count << "). " << line << endl;
    }

    // if the vector is empty that mean the file is empty
    // display a nice message to user
    if (vectorFile.empty())
        cout << "You have nothing to do :)" << endl;

    file.close();
}

void addTasks() {
    string line;
    file.open(pathName, ios::out | ios::app); // mode is set to write out to file and append to file

    // error check
    if (!file.is_open()) {
        cout << "Unable to open file :(" << endl;
        return;
    }

    cout << "Enter what you need to do: ";
    getline(cin, line);
    file << line << endl; // append line to file
    vectorFile.push_back(line); // add to the vector

    file.close();
}

void editTasks() {
    string line;
    string edit;
    int editLine;

    if (vectorFile.empty()) {
        cout << "There is nothing to edit :)" << endl << endl;
        return;
    }

    int count = 0;
    for (const auto &i: vectorFile) {
        cout << ++count << "). " << i << endl;
    }

    cout << "Enter the line would you like to edit?: ";
    cin >> editLine;
    cin.ignore();

    while (editLine < 1 || editLine > vectorFile.size()) {
        cout << "Invalid line number!" << endl;
        cout << "Enter the line would you like to edit?: ";
        cin >> editLine;
        cin.ignore();
    }

    cout << "Enter what you would like to edit: ";
    getline(cin, edit);

    file.open(pathName, ios::in);

    if (!file.is_open) {
        cout << "Unable to open file :(" << endl;
        return;
    }

    vectorFile.clear();

    while (getline(file, line)) {
        vectorFile.push_back(line);
    }

    file.close();

    file.open(pathName, ios::out | ios::app);

    if (!file.is_open) {
        cout << "Unable to open file :(" << endl;
        return;
    }





}


void deleteTask() {
    string line;
    int deleteLine;

    if (vectorFile.empty()) {
        cout << "There is nothing to delete :)" << endl << endl;
        return;
    }

    int count = 0;
    for (const auto &i: vectorFile) {
        cout << ++count << "). " << i << endl;
    }

    cout << "Enter the line you want to delete: ";
    cin >> deleteLine; // the line the user wants to delete
    cin.ignore();

    // error check
    // make sure the line user wants to delete is a valid line
    while (deleteLine < 1 || deleteLine > vectorFile.size()) {
        cout << "Invalid line number!" << endl;
        cout << "Enter the line number you want to delete: ";
        cin >> deleteLine;
        cin.ignore();
    }

    // open file in input mode
    // clear and populate the vector
    file.open(pathName, ios::in); // set to input mode

    if (!file.is_open()) {
        cout << "Unable to open file :(" << endl;
        return;
    }

    vectorFile.clear(); // make sure to we are loading everything correctly

    while (getline(file, line)) {
        vectorFile.push_back(line); // reload everything back to vector
    }

    file.close();

    // delete the line from the vector
    vectorFile.erase(vectorFile.begin() + deleteLine - 1);

    // now we open file in output mode which will blow away the contents of the file
    // and rewrite the contents of the file with the deleted line gone
    file.open(pathName, ios::out);

    if (!file.is_open()) {
        cout << "Unable to open file :(" << endl;
        return;
    }

    for (const auto &i: vectorFile) {
        file << i << endl; // write to file with the deleted line gone
    }

    file.close();
}
