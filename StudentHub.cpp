#include <iostream>
#include <string>
#include <fstream>

struct student {
    std::string first_name;
    std::string last_name;
    int roll_number;
    double cgpa;
    int course_id[10];
} students[110];

int number_of_students = 0;

// Save student data to a file
void saveToFile() {
    std::ofstream file("student.txt", std::ios::out);
    if (!file) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }
    file << number_of_students << "\n"; // Save the number of students
    for (int i = 0; i < number_of_students; i++) {
        file << students[i].first_name << " " << students[i].last_name << " "
             << students[i].roll_number << " " << students[i].cgpa;
        for (int j = 0; j < 5; j++) { // Assuming 5 course IDs per student
            file << " " << students[i].course_id[j];
        }
        file << "\n";
    }
    file.close();
}

// Load student data from a file
void loadFromFile() {
    std::ifstream file("student.txt", std::ios::in);
    if (!file) {
        std::cerr << "No existing data found. Starting fresh.\n";
        return;
    }
    file >> number_of_students; // Read the number of students
    for (int i = 0; i < number_of_students; i++) {
        file >> students[i].first_name >> students[i].last_name
             >> students[i].roll_number >> students[i].cgpa;
        for (int j = 0; j < 5; j++) { // Assuming 5 course IDs per student
            file >> students[i].course_id[j];
        }
    }
    file.close();
}

// Add a new student's details
void addStudentDetails() {
    std::cout << "Enter the new student details\n";
    std::cout << "Enter the Roll Number of the student: ";
    int roll_no;
    std::cin >> roll_no;

    // Check if roll number already exists
    for (int i = 0; i < number_of_students; i++) {
        if (students[i].roll_number == roll_no) {
            std::cout << "Student with the given roll number already exists in the database.\n";
            return;
        }
    }

    // Add new student details
    std::cout << "Enter the first name of the student: ";
    std::cin >> students[number_of_students].first_name;

    std::cout << "Enter the last name of the student: ";
    std::cin >> students[number_of_students].last_name;

    students[number_of_students].roll_number = roll_no;

    std::cout << "Enter the CGPA of the student: ";
    std::cin >> students[number_of_students].cgpa;

    std::cout << "Enter the course ID of each course in which the student is enrolled (5 courses): ";
    for (int i = 0; i < 5; i++) {
        std::cin >> students[number_of_students].course_id[i];
    }

    number_of_students++;
    saveToFile();
}

// Find student by roll number
void findStudentByRollNumber() {
    int roll_no;
    std::cout << "Enter the Roll Number of the student: ";
    std::cin >> roll_no;

    bool found = false;
    for (int i = 0; i < number_of_students; i++) {
        if (students[i].roll_number == roll_no) {
            found = true;
            std::cout << "The Student Details are:\n";
            std::cout << "First Name: " << students[i].first_name << "\n";
            std::cout << "Last Name: " << students[i].last_name << "\n";
            std::cout << "CGPA: " << students[i].cgpa << "\n";
            std::cout << "Course IDs: ";
            for (int j = 0; j < 5; j++) {
                std::cout << students[i].course_id[j] << " ";
            }
            std::cout << "\n";
            break;
        }
    }

    if (!found) {
        std::cout << "No student found with the given roll number.\n";
    }
}

// Find students enrolled in a specific course
void findStudentByCourseId() {
    int course_id;
    std::cout << "Enter the Course ID: ";
    std::cin >> course_id;

    bool found = false;
    for (int i = 0; i < number_of_students; i++) {
        for (int j = 0; j < 5; j++) {
            if (students[i].course_id[j] == course_id) {
                found = true;
                std::cout << "Student Details:\n";
                std::cout << "First Name: " << students[i].first_name << "\n";
                std::cout << "Last Name: " << students[i].last_name << "\n";
                std::cout << "Roll Number: " << students[i].roll_number << "\n";
                std::cout << "CGPA: " << students[i].cgpa << "\n\n";
                break;
            }
        }
    }

    if (!found) {
        std::cout << "No student found enrolled in this course.\n";
    }
}

// Find total number of students
void findTotalStudents() {
    std::cout << "Total number of students: " << number_of_students << "\n";
}

// Delete a student by roll number
void deleteStudentByRollNumber() {
    int roll_no;
    std::cout << "Enter the Roll Number that you want to delete: ";
    std::cin >> roll_no;

    bool found = false;
    for (int i = 0; i < number_of_students; i++) {
        if (students[i].roll_number == roll_no) {
            found = true;
            for (int j = i; j < number_of_students - 1; j++) {
                students[j] = students[j + 1];
            }
            number_of_students--;
            break;
        }
    }

    if (found) {
        std::cout << "The Roll Number is removed successfully.\n";
        saveToFile();
    } else {
        std::cout << "Roll number not found in the database.\n";
    }
}

// Update student details
void updateStudentDetails() {
    int roll_no;
    std::cout << "Enter the Roll Number of the student to update: ";
    std::cin >> roll_no;

    bool found = false;
    for (int i = 0; i < number_of_students; i++) {
        if (students[i].roll_number == roll_no) {
            found = true;
            std::cout << "1. Update First Name\n"
                         "2. Update Last Name\n"
                         "3. Update Roll Number\n"
                         "4. Update CGPA\n"
                         "5. Update Courses\n";
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                std::cout << "Enter the new First Name: ";
                std::cin >> students[i].first_name;
                break;
            case 2:
                std::cout << "Enter the new Last Name: ";
                std::cin >> students[i].last_name;
                break;
            case 3:
                std::cout << "Enter the new Roll Number: ";
                std::cin >> students[i].roll_number;
                break;
            case 4:
                std::cout << "Enter the new CGPA: ";
                std::cin >> students[i].cgpa;
                break;
            case 5:
                std::cout << "Enter the new Course IDs: ";
                for (int j = 0; j < 5; j++) {
                    std::cin >> students[i].course_id[j];
                }
                break;
            default:
                std::cout << "Invalid choice.\n";
            }
            break;
        }
    }

    if (found) {
        std::cout << "Details updated successfully.\n";
        saveToFile();
    } else {
        std::cout << "Student not found in the database.\n";
    }
}

int main() {
    loadFromFile();

    int taskToPerform;
    while (1) {
        std::cout << "\nEnter the task that you want to perform\n";
        std::cout << "1. Add a new Student Detail\n";
        std::cout << "2. Find the details of a Student using Roll Number\n";
        std::cout << "3. Find the details of Students enrolled in a specific course\n";
        std::cout << "4. Find Total number of Students\n";
        std::cout << "5. Delete the details of a Student\n";
        std::cout << "6. Update the details of a Student\n";
        std::cout << "7. Exit\n";
        std::cin >> taskToPerform;

        switch (taskToPerform) {
        case 1:
            addStudentDetails();
            break;
        case 2:
            findStudentByRollNumber();
            break;
        case 3:
            findStudentByCourseId();
            break;
        case 4:
            findTotalStudents();
            break;
        case 5:
            deleteStudentByRollNumber();
            break;
        case 6:
            updateStudentDetails();
            break;
        case 7:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid input. Try again.\n";
        }
    }
    return 0;
}
