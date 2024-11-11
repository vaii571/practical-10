//File handling 
#include <iostream> #include <fstream> using namespace std; struct Student { 
    int roll; 
    char name[50];     char division[10];     char address[100]; 
}; 
 
void addStudent() {     Student s;     ofstream outFile("students.dat", ios::app); // Open file in append mode 
 
    cout << "Enter Roll Number: "; 
    cin >> s.roll;     cin.ignore(); // Ignore newline after roll number     cout << "Enter Name: ";     cin.getline(s.name, 50);     cout << "Enter Division: ";     cin.getline(s.division, 10);     cout << "Enter Address: "; 
    cin.getline(s.address, 100); 
 
    outFile.write((char*)&s, sizeof(s));     outFile.close();     cout << "Student record added.\n"; 
} 
 
void displayStudent(int roll) {     Student s;     ifstream inFile("students.dat", ios::binary);     bool found = false; 
 
    while (inFile.read((char*)&s, sizeof(s))) { 
        if (s.roll == roll) { 
            cout << "Roll Number: " << s.roll << "\nName: " << s.name  
                 << "\nDivision: " << s.division << "\nAddress: " << s.address << endl;             found = true;             break; 
        } 
    } 
 
    if (!found) cout << "Student record not found.\n";     inFile.close(); 
} 
 
void deleteStudent(int roll) {     Student s;     ifstream inFile("students.dat", ios::binary);     ofstream outFile("temp.dat", ios::binary);     bool found = false; 
 
    while (inFile.read((char*)&s, sizeof(s))) { 
        if (s.roll != roll) {             outFile.write((char*)&s, sizeof(s)); // Copy to temp file 
        } else { 
            found = true; // Record found for deletion 
        } 
    } 
    inFile.close();     outFile.close();     remove("students.dat"); // Remove original file     rename("temp.dat", "students.dat"); // Rename temp file to original 
 
    if (found) cout << "Student record deleted.\n";     else cout << "Student record not found.\n"; 
} 
int main() {     int choice, roll;       do { 
        cout << "\n1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\nEnter your choice: ";         cin >> choice; 
 
        switch (choice) {             case 1: addStudent(); break; 
            case 2: 
                cout << "Enter Roll Number to display: "; 
                cin >> roll;                 displayStudent(roll);                 break;             case 3: 
                cout << "Enter Roll Number to delete: "; 
                cin >> roll;                 deleteStudent(roll);                 break;             case 4: cout << "Exiting...\n"; break;             default: cout << "Invalid choice!\n"; break; 
        } 
    } while (choice != 4);
 return 0; 
} 
