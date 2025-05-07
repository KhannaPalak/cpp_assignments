#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

class Course {
    string name;
    int credits;

public:
    // Default Constructor
    Course() : name("Unknown"), credits(0) {}

    // Parameterized Constructor
    Course(string name, int credits) : name(name), credits(credits) {}

    // Copy Constructor
    Course(const Course& other) : name(other.name), credits(other.credits) {}

    // Destructor
    ~Course() {
        // If there were dynamically allocated resources, clean them up here (not needed for this simple class)
        cout << "Course " << name << " is being destroyed." << endl;
    }

    string getName() const {
        return name;
    }

    void display() const {
        cout << "Course: " << name << ", Credits: " << credits << endl;
    }
};

class Student {
    string name;
    int rollNumber;
    double CGPA;
    vector<shared_ptr<Course>> enrolledCourses;  // Changed from Course* to shared_ptr<Course>

public:
    // Default Constructor
    Student() : name("Unknown"), rollNumber(0), CGPA(0.0) {}

    // Parameterized Constructor
    Student(string name, int rollNumber, double CGPA)
        : name(name), rollNumber(rollNumber), CGPA(CGPA) {}

    // Copy Constructor
    Student(const Student& other)
        : name(other.name), rollNumber(other.rollNumber), CGPA(other.CGPA) {
        
        for (const auto& course : other.enrolledCourses) {
            enrolledCourses.push_back(make_shared<Course>(*course)); // Copy the course objects
        }
    }

    // Destructor
    ~Student() {
        
        cout << "Student " << name << " is being destroyed." << endl;
    }

    int getRollNumber() const {
        return rollNumber;
    }

    double getCGPA() const {
        return CGPA;
    }

    void enrollInCourse(shared_ptr<Course> course) {
        
        if (find(enrolledCourses.begin(), enrolledCourses.end(), course) == enrolledCourses.end()) {
            enrolledCourses.push_back(course);
        } else {
            cout << "Student is already enrolled in " << course->getName() << endl;
        }
    }

    void updateCGPA(double newCGPA) {
        if (newCGPA >= 0.0 && newCGPA <= 10.0) {
            CGPA = newCGPA;
        } else {
            cout << "Invalid CGPA! Please enter a CGPA between 0.0 and 10.0." << endl;
        }
    }

    void displayDetails() const {
        cout << "Student Name: " << name << ", Roll Number: " << rollNumber << ", CGPA: " << CGPA << endl;
    }

    void displayEnrolledCourses() const {
        cout << "Enrolled Courses for " << name << ":" << endl;
        for (const auto& course : enrolledCourses) {
            course->display();
        }
    }
};

class StudentManagementSystem {
    vector<shared_ptr<Student>> students;

public:
    void addStudent(shared_ptr<Student> student) {
        students.push_back(student);
    }

    shared_ptr<Student> searchByRollNumber(int rollNumber) {
        for (const auto& student : students) {
            if (student->getRollNumber() == rollNumber) {
                return student;
            }
        }
        cout << "Student with Roll Number " << rollNumber << " not found." << endl;
        return nullptr;
    }

    void displayAllStudents() const {
        for (const auto& student : students) {
            student->displayDetails();
        }
    }
};

int main() {
    // Create courses
    shared_ptr<Course> course1 = make_shared<Course>("Data Structures", 4);
    shared_ptr<Course> course2 = make_shared<Course>("Web Development", 3);

    // Create students
    shared_ptr<Student> student1 = make_shared<Student>("Palak", 325, 8.9);
    shared_ptr<Student> student2 = make_shared<Student>("Akshat", 123, 9.0);

    // Enroll students in courses
    student1->enrollInCourse(course1);
    student1->enrollInCourse(course2);

    student2->enrollInCourse(course1);

    // Create Student Management System
    StudentManagementSystem sms;

    // Add students to the system
    sms.addStudent(student1);
    sms.addStudent(student2);

    // Display all students
    cout << "\nAll Students:\n";
    sms.displayAllStudents();

    // Search for a student by roll number
    cout << "\nSearching for student with roll number 325:\n";
    auto studentFound = sms.searchByRollNumber(325);
    if (studentFound) {
        studentFound->displayDetails();
        studentFound->displayEnrolledCourses();
    }

    // Update CGPA
    cout << "\nUpdating CGPA for student 325...\n";
    studentFound->updateCGPA(9.5);
    studentFound->displayDetails();

    // Clean-up (shared_ptr will handle memory management here)
    // Destructor will be called automatically for shared_ptr managed objects when they go out of scope.

    return 0;
}
