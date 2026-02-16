#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/**
 * StudentNode: Represents a single slot in the Hash Table.
 * Uses 'isOccupied' to track slots and 'isDeleted' for lazy deletion support.
 */
struct StudentNode {
    int rollNumber;
    string name;
    bool isOccupied;
    bool isDeleted;

    StudentNode() : rollNumber(-1), name(""), isOccupied(false), isDeleted(false) {}
};

/**
 * StudentHashTable: A Hash Table implementation using Quadratic Probing.
 * Formula: (Hash + attempt^2) % TableSize
 */
class StudentHashTable {
private:
    static const int TABLE_SIZE = 15;
    StudentNode* table[TABLE_SIZE];

    // Basic Modulo Hash Function
    int hashFunction(int roll) const {
        return roll % TABLE_SIZE;
    }

public:
    // Constructor: Allocates memory for each bucket
    StudentHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = new StudentNode();
        }
    }

    // Destructor: Properly cleans up the heap to prevent memory leaks
    ~StudentHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            delete table[i];
        }
    }

    // Inserts a record into the table using Quadratic Probing
    void insertRecord(int roll, const string& name) {
        int baseHash = hashFunction(roll);

        for (int attempt = 0; attempt < TABLE_SIZE; attempt++) {
            int index = (baseHash + (attempt * attempt)) % TABLE_SIZE;

            // Insert if the slot is never used or was previously deleted
            if (!table[index]->isOccupied || table[index]->isDeleted) {
                table[index]->rollNumber = roll;
                table[index]->name = name;
                table[index]->isOccupied = true;
                table[index]->isDeleted = false;
                cout << "[System] Record for '" << name << "' inserted at index " << index << ".\n";
                return;
            }

            // Prevent duplicate roll numbers
            if (table[index]->rollNumber == roll && !table[index]->isDeleted) {
                cout << "[Error] Roll number " << roll << " already exists in the system.\n";
                return;
            }
        }
        cout << "[Error] Table Overflow! Cannot insert " << name << ".\n";
    }

    // Searches for a record using Quadratic Probing
    void searchRecord(int roll) const {
        int baseHash = hashFunction(roll);

        for (int attempt = 0; attempt < TABLE_SIZE; attempt++) {
            int index = (baseHash + (attempt * attempt)) % TABLE_SIZE;

            // If we find an empty slot that was never occupied, the record doesn't exist
            if (!table[index]->isOccupied && !table[index]->isDeleted) {
                break;
            }

            if (table[index]->isOccupied && !table[index]->isDeleted && table[index]->rollNumber == roll) {
                cout << "[Found] Roll: " << roll << " | Student Name: " << table[index]->name << "\n";
                return;
            }
        }
        cout << "[Not Found] No record exists for Roll Number: " << roll << "\n";
    }

    // Visualizes the Hash Table structure
    void displayTable() const {
        cout << "\n" << string(45, '=') << "\n";
        cout << left << setw(8) << "Index" << setw(12) << "Status" << setw(15) << "Roll No" << "Name" << "\n";
        cout << string(45, '-') << "\n";

        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << left << setw(8) << i;
            if (!table[i]->isOccupied) {
                cout << setw(12) << "EMPTY" << "---" << endl;
            } else if (table[i]->isDeleted) {
                cout << setw(12) << "DELETED" << "---" << endl;
            } else {
                cout << setw(12) << "ACTIVE" << setw(15) << table[i]->rollNumber << table[i]->name << endl;
            }
        }
        cout << string(45, '=') << "\n";
    }
};

/**
 * Main function handles dynamic user input and program flow.
 */
int main() {
    StudentHashTable studentDb;
    int choice;

    cout << "STUDENT DATABASE SYSTEM (HASH TABLE - QUADRATIC PROBING)\n";

    while (true) {
        cout << "\n1. Insert Record\n2. Search Record\n3. Display Table\n4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            int r;
            string n;
            cout << "Enter Roll Number: ";
            cin >> r;
            cin.ignore(); // Clear buffer
            cout << "Enter Name: ";
            getline(cin, n);
            studentDb.insertRecord(r, n);
        } 
        else if (choice == 2) {
            int r;
            cout << "Enter Roll Number to Search: ";
            cin >> r;
            studentDb.searchRecord(r);
        } 
        else if (choice == 3) {
            studentDb.displayTable();
        } 
        else if (choice == 4) {
            cout << "Exiting system. Goodbye!\n";
            break;
        } 
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
