#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Student {
    int id;
    string name;
    int age;
    string grade;
};

const string DATA_FILE = "students.txt";

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file(DATA_FILE);
    if (!file.is_open()) {
        return students;
    }

    Student student;
    while (file >> student.id) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, student.name);
        file >> student.age;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, student.grade);
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        students.push_back(student);
    }

    file.close();
    return students;
}

void saveStudents(const vector<Student>& students) {
    ofstream file(DATA_FILE, ios::trunc);
    for (const auto& student : students) {
        file << student.id << "\n";
        file << student.name << "\n";
        file << student.age << "\n";
        file << student.grade << "\n";
    }
    file.close();
}

int findStudentIndex(const vector<Student>& students, int id) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void addStudent(vector<Student>& students) {
    Student student;
    cout << "Enter student ID: ";
    cin >> student.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (findStudentIndex(students, student.id) != -1) {
        cout << "A student with this ID already exists.\n";
        return;
    }

    cout << "Enter student name: ";
    getline(cin, student.name);
    cout << "Enter student age: ";
    cin >> student.age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter student grade: ";
    getline(cin, student.grade);

    students.push_back(student);
    saveStudents(students);
    cout << "Student added successfully.\n";
}

void updateStudent(vector<Student>& students) {
    int id;
    cout << "Enter student ID to update: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int index = findStudentIndex(students, id);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Current name: " << students[index].name << "\n";
    cout << "Enter new name (leave blank to keep current): ";
    string input;
    getline(cin, input);
    if (!input.empty()) {
        students[index].name = input;
    }

    cout << "Current age: " << students[index].age << "\n";
    cout << "Enter new age (0 to keep current): ";
    int age;
    cin >> age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (age > 0) {
        students[index].age = age;
    }

    cout << "Current grade: " << students[index].grade << "\n";
    cout << "Enter new grade (leave blank to keep current): ";
    getline(cin, input);
    if (!input.empty()) {
        students[index].grade = input;
    }

    saveStudents(students);
    cout << "Student updated successfully.\n";
}

void deleteStudent(vector<Student>& students) {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int index = findStudentIndex(students, id);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    students.erase(students.begin() + index);
    saveStudents(students);
    cout << "Student deleted successfully.\n";
}

void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }

    cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(8) << "Age" << setw(10) << "Grade" << "\n";
    cout << string(53, '-') << "\n";
    for (const auto& student : students) {
        cout << left << setw(10) << student.id
             << setw(25) << student.name
             << setw(8) << student.age
             << setw(10) << student.grade << "\n";
    }
}

void showMenu() {
    cout << "\n--- Student Management System ---\n";
    cout << "1. Add Student\n";
    cout << "2. Update Student\n";
    cout << "3. Delete Student\n";
    cout << "4. Display All Students\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    vector<Student> students = loadStudents();
    int choice;
    bool running = true;

    while (running) {
        showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                updateStudent(students);
                break;
            case 3:
                deleteStudent(students);
                break;
            case 4:
                displayStudents(students);
                break;
            case 5:
                running = false;
                cout << "Exiting Student Management System.\n";
                break;
            default:
                cout << "Invalid option. Please choose a number between 1 and 5.\n";
                break;
        }
    }
    return 0;
}
