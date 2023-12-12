#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>
#include <fstream>
using namespace std;


union Date {
    struct {
        int day;
        int month;
        int year;
    } components;
    long long int serial;
};

struct Note {
    string lastName;
    string firstName;
    string phoneNumber;
    Date birthdate;
};

bool IfFileOpen(const string& filename);
void ReadTheFile(const string& filename, Note list[], int& n);
void AddFriend(const string& filename, Note list[], int& n, int& s);
void People_SearchFor_Month(Note list[], int n);
void CoutInfo(Note list[], int n);



int main() {
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    if (!IfFileOpen(filename)) {
        return 1;
    }

    ifstream F(filename);
    Note list[100];
    int n = 0;
    int s = 0;

    ReadTheFile(filename, list, n);

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Choose exercise" << endl << endl;
        cout << " [3] - Search from month" << endl;
        cout << " [4] - Add to list" << endl;
        cout << " [5] - View list" << endl;
        cout << " [0] - Exit" << endl << endl;
        cout << "Input value: "; cin >> menuItem;
        cout << endl << endl << endl;


        switch (menuItem) {
        case 3:
            People_SearchFor_Month(list, n);
            break;
        case 4:
            AddFriend(filename, list, n, s);
            break;
        case 5:
            CoutInfo(list, n);
            break;
        case 0:
            return 0;
        default:
            cout << "You wrote mistake value!" << endl;
        }
    } while (true);

    F.close();
    return 0;
}

bool IfFileOpen(const string& filename) {
    ifstream F(filename);
    if (!F.is_open()) {
        cout << "Can't open the file" << endl;
        return false;
    }
    return true;
}

void ReadTheFile(const string& filename, Note list[], int& n) {
    ifstream F(filename);
    if (!F.is_open()) {
        cout << "Can't open the file" << endl;
        return;
    }
    F >> n;
    for (int i = 0; i < n; i++) {
        if (F >> list[i].lastName >> list[i].firstName >> list[i].phoneNumber >> list[i].birthdate.components.day >> list[i].birthdate.components.month >> list[i].birthdate.components.year) {
        }
        else {
            cout << "Invalid data in the file." << endl;
            return;
        }
    }
    F.close();
}

void AddFriend(const string& filename, Note list[], int& n, int& s) {
    if (n >= 100) {
        cout << "Cannot add more friends. The limit is reached." << endl;
        return;
    }

    if (s >= 100000000000) {
        cout << "Cannot add more friends. The limit is reached." << endl;
        return;
    }

    ofstream outFile(filename, ios::app);

    if (!outFile.is_open()) {
        cout << "Can't open the file" << endl;
        return;
    }

    cout << "Enter the surname: ";
    cin >> list[n].lastName;

    cout << "Enter the name: ";
    cin >> list[n].firstName;

    cout << "Enter the phone number: ";
    cin >> list[s].phoneNumber;

    cout << "Enter the date of birth (day month year): ";
    cin >> list[n].birthdate.components.day >> list[n].birthdate.components.month >> list[n].birthdate.components.year;

    outFile << list[n].lastName << " " << list[n].firstName << " " << list[n].phoneNumber << " "
        << list[n].birthdate.components.day <<"/"<< list[n].birthdate.components.month <<"/"<< list[n].birthdate.components.year << endl;

    n++;
    s++;

    outFile.close();
}

void CoutInfo(Note list[], int n) {
    cout << "-------------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Surname: " << list[i].lastName << endl;
        cout << "Name: " << list[i].firstName << endl;
        cout << "Number: " << list[i].phoneNumber << endl;
        cout << "Date of birth: " << list[i].birthdate.components.day << "." << list[i].birthdate.components.month << "." << list[i].birthdate.components.year << endl;
        cout << "------------------------" << endl;
    }
}

void Input_And_Print_Data(Note* notes, int numNotes) {
    for (int i = 0; i < numNotes; ++i) {
        cout << "Note #" << i + 1 << endl << endl;
        cout << "Last Name: ";
        cin >> notes[i].lastName;
        cout << "Name: ";
        cin >> notes[i].firstName;
        cout << "Phone number: ";
        cin >> notes[i].phoneNumber;
        cout << "Birthday (day, month, year): " << endl;
        cin >> notes[i].birthdate.components.day >> notes[i].birthdate.components.month >> notes[i].birthdate.components.year;
    }
}


void People_SearchFor_Month(Note list[], int n) {
    int month;
    cout << "Enter the month to find: ";
    cin >> month;

    cout << "Friends born in month " << month << ":" << endl;
    cout << "-------------------------" << endl;
    for (int i = 0; i < n; i++) {
        if (list[i].birthdate.components.month == month) {
            cout << "Surname: " << list[i].lastName << endl;
            cout << "Name: " << list[i].firstName << endl;
            cout << "Number: " << list[i].phoneNumber << endl;
            cout << "Date of birth: " << list[i].birthdate.components.day << "." << list[i].birthdate.components.month << "." << list[i].birthdate.components.year << endl;
            cout << "------------------------" << endl;
        }
    }
}

