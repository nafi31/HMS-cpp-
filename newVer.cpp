/*
	Title: Hotel Management System
*/


#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class hotel {
private:
    int room_no;
    char name[50];
    char address[50];
    char phone[15];
    int days;
    float fare;

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};

void hotel::main_menu() {
    int choice = 0;
    while (choice != 5) {
        cout << "\n\t\t\t\t*************";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t\t*************";
        cout << "\n\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Record";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                display();
                break;
            case 3:
                rooms();
                break;
            case 4:
                edit();
                break;
            case 5:
                break;
            default: {
                cout << "\n\n\t\t\tWrong choice.....!!!";
                cout << "\n\t\t\tPress any key to continue....!!";
                cin.ignore();
                cin.get();
            }
        }
    }
}

void hotel::add() {
    int r, flag;
    ofstream fout("Record.txt", ios::app);
    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cin >> r;
    cin.ignore(); // Ignore the newline character

    flag = check(r);
    if (flag)
        cout << "\n Sorry..!!! Room is already booked";
    else {
        room_no = r;
        cout << " Name: ";
        cin.getline(name, 30);
        cout << " Address: ";
        cin.getline(address, 50);
        cout << " Phone No: ";
        cin.getline(phone, 15);
        cout << " No of Days to Checkout: ";
        cin >> days;
        cin.ignore(); // Ignore the newline character
        fare = days * 900.0; // 900 is currently set as the default price per day
        fout << room_no << ' ' << name << ' ' << address << ' ' << phone << ' ' << days << ' ' << fare << '\n';
        cout << "\n Room is booked...!!!";
    }

    cout << "\n Press any key to continue.....!!";
    cin.ignore();
    cin.get();
    fout.close();
}
void hotel::display() {
    int r, flag = 0;
    ifstream fin("Record.txt", ios::in);
    cout << "\n Enter room no: ";
    cin >> r;

    while (!fin.eof()) {
        fin >> room_no >> name >> address >> phone >> days >> fare;

        if (room_no == r) {
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            flag = 1;
            break; // Stop the loop once a match is found
        }
    }

    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant....!!";

    cout << "\n\n Press any key to continue....!!";
    cin.get();
    fin.close();
}

void hotel::rooms() {
    ifstream fin("Record.txt", ios::in);
    int encounteredRoom = -1;  // To store encountered room number

    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";

    while (fin >> room_no >> name >> address >> phone >> days >> fare) {
        if (room_no == encounteredRoom) {
            // Skip if it's a duplicate room number
            continue;
        }

        encounteredRoom = room_no;

        cout << "\n Room no: " << room_no << "\n Name: " << name;
        cout << "\n Address: " << address << "\n Phone: " << phone;
        cout << "\n Days: " << days << "\n Total: " << fare;
        cout << "\n**********************************";
    }

    cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    cin.ignore();
    cin.get();
    fin.close();
}
void hotel::edit() {
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n Enter your choice: ";
    cin >> choice;

    cout << "\n Enter room no: ";
    cin >> r;
    switch (choice) {
        case 1:
            modify(r);
            break;
        case 2:
            delete_rec(r);
            break;
        default:
            cout << "\n Wrong Choice.....!!";
    }
    cout << "\n Press any key to continue....!!!";
    cin.ignore();
    cin.get();
}

int hotel::check(int r) {
    int flag = 0;
    int encounteredRoom = 0;  // To store encountered room number
    ifstream fin("Record.txt", ios::in);

    while (!fin.eof()) {
        fin >> room_no >> name >> address >> phone >> days >> fare;
        if (room_no == r && room_no != encounteredRoom) {
            flag = 1;
            encounteredRoom = room_no;
            break;
        }
    }

    fin.close();
    return flag;
}

void hotel::modify(int r) {
    long pos;
    int flag = 0;
    fstream file("Record.txt", ios::in | ios::out);
    while (!file.eof()) {
        pos = file.tellg(); //stores the current stream position
        file >> room_no >> name >> address >> phone >> days >> fare;
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n -----------------";
            cout << "\n Name: ";
            cin.ignore();
            cin.getline(name, 30);
            cout << " Address: ";
            cin.getline(address, 50);
            cout << " Phone no: ";
            cin.getline(phone, 15);
            cout << " Days: ";
            cin >> days;
            fare = days * 900.0;
            file.seekg(pos); // accesses the first position in the stream
            file << room_no << ' ' << name << ' ' << address << ' ' << phone << ' ' << days << ' ' << fare << '\n';
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        cout << "\n Sorry Room no. not found or vacant...!!";
    file.close();
}
void hotel::delete_rec(int r) {
    int flag = 0;
    char ch;
    ifstream fin("Record.txt");
    ofstream fout("temp.txt");

    while (fin >> room_no >> name >> address >> phone >> days >> fare) {
        if (room_no == r) {
            if (flag == 1) {
                // Skip saving the record if it's a duplicate
                break;
            }

            flag = 1;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n Days: " << days;
            cout << "\n Total Fare: " << fare;
            cout << "\n\n Do you want to delete this record (y/n): ";
            cin >> ch;

            if (ch == 'y') {
                // Delete the record
                flag = 1;
                continue;
            }
        }

        fout << room_no << ' ' << name << ' ' << address << ' ' << phone << ' ' << days << ' ' << fare << '\n';
    }

    fin.close();
    fout.close();

    if (flag == 0)
        cout << "\n Sorry, room no. not found or vacant...!!";
    else {
        remove("Record.txt");
        rename("temp.txt", "Record.txt");
        cout << "\n Operation Complete.";
    }
}
int main() {
    hotel h;
    cout << "\n\n\n";
    cout << "\n\n\n\t\t\tPress Enter to continue....!!";
    cin.ignore();
    cin.get();
    h.main_menu();
    cout << "\n Press Enter to continue....!!!";
    cin.ignore();
    cin.get();

    return 0;
}
