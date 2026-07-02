# Student Management System

A console-based Student Management System in C++.

## Features
- Add student records
- Update student records
- Delete student records
- Display all students
- Persistent storage using `students.txt`

## Build & Run
1. Compile with a C++ compiler, for example:
   ```bash
   g++ StudentManagementSystem.cpp -o StudentManagementSystem
   ```
2. Run the executable:
   ```bash
   ./StudentManagementSystem
   ```

## Notes
- Student records are stored in `students.txt` in the same directory.
- The app automatically loads existing records at startup and saves changes after add, update, or delete operations.
