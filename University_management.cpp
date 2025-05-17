// University Management System - Full Implementation
// Includes Assignments 2, 3 & 4: OOP, Inheritance, Polymorphism, Exception Handling, Integration

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
using namespace std;

// -------------------- Custom Exceptions --------------------
class UniversitySystemException : public exception {
protected:
    string message;
public:
    UniversitySystemException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(const string& msg) : UniversitySystemException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(const string& msg) : UniversitySystemException("Grade Error: " + msg) {}
};

class PaymentException : public UniversitySystemException {
public:
    PaymentException(const string& msg) : UniversitySystemException("Payment Error: " + msg) {}
};

void logError(const string& error) {
    cerr << "[ERROR LOG] " << error << endl;
}

// -------------------- Person Base Class --------------------
class Person {
protected:
    string name, id, contactInfo;
    int age;

public:
    Person(string name, int age, string id, string contactInfo) : name(name), age(age), id(id), contactInfo(contactInfo) {
        if (name.empty()) throw UniversitySystemException("Name cannot be empty");
        if (age <= 0 || age > 120) throw UniversitySystemException("Invalid age");
    }
    virtual ~Person() {}

    virtual void displayDetails() const {
        cout << "Name: " << name << ", ID: " << id << ", Age: " << age << ", Contact: " << contactInfo << endl;
    }

    virtual double calculatePayment() const {
        return 0.0;
    }
};

// -------------------- Student Class Hierarchy --------------------
class Student : public Person {
protected:
    string enrollmentDate, program;
    double gpa;
public:
    Student(string name, int age, string id, string contact, string enrollDate, string program, double gpa)
        : Person(name, age, id, contact), enrollmentDate(enrollDate), program(program), gpa(gpa) {
        if (gpa < 0.0 || gpa > 4.0) throw UniversitySystemException("Invalid GPA");
    }
    void displayDetails() const override {
        Person::displayDetails();
        cout << "Program: " << program << ", GPA: " << gpa << endl;
    }
};

class UndergraduateStudent : public Student {
    string major, minor, expectedGradDate;
public:
    UndergraduateStudent(string name, int age, string id, string contact, string enrollDate,
        string program, double gpa, string major, string minor, string gradDate)
        : Student(name, age, id, contact, enrollDate, program, gpa), major(major), minor(minor), expectedGradDate(gradDate) {}

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Major: " << major << ", Minor: " << minor << ", Expected Grad: " << expectedGradDate << endl;
    }

    double calculatePayment() const override {
        return 20000.0 - (gpa * 1000.0); // example calculation
    }
};

class Professor; // forward declaration

class GraduateStudent : public Student {
    string researchTopic, thesisTitle;
    Professor* advisor;
public:
    GraduateStudent(string name, int age, string id, string contact, string enrollDate,
        string program, double gpa, string research, string thesis, Professor* advisor)
        : Student(name, age, id, contact, enrollDate, program, gpa), researchTopic(research), thesisTitle(thesis), advisor(advisor) {}

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Research: " << researchTopic << ", Thesis: " << thesisTitle << endl;
    }

    double calculatePayment() const override {
        return 10000.0 - (gpa * 500.0);
    }
};

// -------------------- Professor Class Hierarchy --------------------
class Professor : public Person {
protected:
    string department, specialization, hireDate;
public:
    Professor(string name, int age, string id, string contact, string dept, string spec, string hire)
        : Person(name, age, id, contact), department(dept), specialization(spec), hireDate(hire) {}

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Dept: " << department << ", Specialization: " << specialization << endl;
    }
};

class AssistantProfessor : public Professor {
public:
    AssistantProfessor(string name, int age, string id, string contact, string dept, string spec, string hire)
        : Professor(name, age, id, contact, dept, spec, hire) {}

    double calculatePayment() const override {
        return 60000.0;
    }
};

// -------------------- Course and Department --------------------
class Course {
    string code, title, description;
    int credits;
    Professor* instructor;
public:
    Course(string code, string title, int credits, string desc, Professor* instr)
        : code(code), title(title), credits(credits), description(desc), instructor(instr) {
        if (credits <= 0) throw UniversitySystemException("Credits must be positive");
    }
};

class Department {
    string name, location;
    double budget;
public:
    Department(string name = "", string location = "", double budget = 0.0)
        : name(name), location(location), budget(budget) {}
};

// -------------------- GradeBook and EnrollmentManager --------------------
class GradeBook {
    map<string, double> grades;
public:
    void addGrade(string studentID, double grade) {
        if (grade < 0.0 || grade > 100.0)
            throw GradeException("Invalid grade for student " + studentID);
        grades[studentID] = grade;
    }

    double calculateAverageGrade() {
        if (grades.empty()) throw GradeException("No grades to average.");
        double sum = 0;
        for (auto& p : grades) sum += p.second;
        return sum / grades.size();
    }

    double getHighestGrade() {
        if (grades.empty()) throw GradeException("No grades available.");
        double highest = 0.0;
        for (auto& p : grades) highest = max(highest, p.second);
        return highest;
    }

    vector<string> getFailingStudents() {
        vector<string> fail;
        for (auto& p : grades) {
            if (p.second < 50.0) fail.push_back(p.first);
        }
        return fail;
    }
};

class EnrollmentManager {
    map<string, vector<string>> courseEnrollments;
    const int MAX_COURSE_SIZE = 30;
public:
    void enrollStudent(string courseCode, string studentID) {
        if (courseEnrollments[courseCode].size() >= MAX_COURSE_SIZE)
            throw EnrollmentException("Course " + courseCode + " is full.");
        courseEnrollments[courseCode].push_back(studentID);
    }

    void dropStudent(string courseCode, string studentID) {
        auto& students = courseEnrollments[courseCode];
        auto it = remove(students.begin(), students.end(), studentID);
        if (it == students.end())
            throw EnrollmentException("Student " + studentID + " not found in course " + courseCode);
        students.erase(it, students.end());
    }

    int getEnrollmentCount(string courseCode) {
        return courseEnrollments[courseCode].size();
    }
};

// -------------------- UniversitySystem --------------------
class UniversitySystem {
    vector<Department> departments;
    vector<Course> courses;
    vector<Student*> students;
    vector<Professor*> professors;
    GradeBook gradebook;
    EnrollmentManager enrollmentManager;
public:
    void addDepartment(const Department& dept) { departments.push_back(dept); }
    void addCourse(const Course& course) { courses.push_back(course); }
    void addStudent(Student* student) { students.push_back(student); }
    void addProfessor(Professor* prof) { professors.push_back(prof); }

    void enrollStudentInCourse(string courseCode, string studentID) {
        enrollmentManager.enrollStudent(courseCode, studentID);
    }
    void enterGrade(string studentID, double grade) {
        gradebook.addGrade(studentID, grade);
    }
    void displayAllPeople() {
        for (auto* s : students) {
            s->displayDetails();
            cout << "Payment: $" << s->calculatePayment() << endl;
        }
        for (auto* p : professors) {
            p->displayDetails();
            cout << "Payment: $" << p->calculatePayment() << endl;
        }
    }
};

// -------------------- Main --------------------
int main() {
    try {
        UniversitySystem system;
        AssistantProfessor* ap = new AssistantProfessor("Dr. Kim", 40, "P003", "kim@univ.edu", "CS", "ML", "2020-09-01");
        system.addProfessor(ap);

        UndergraduateStudent* u1 = new UndergraduateStudent("Alice", 20, "S123", "alice@univ.edu", "2023-09-01", "CS", 3.8, "CS", "Math", "2026-06-01");
        GraduateStudent* g1 = new GraduateStudent("Bob", 24, "S124", "bob@univ.edu", "2022-09-01", "CS", 3.5, "AI", "AI Thesis", ap);

        system.addStudent(u1);
        system.addStudent(g1);

        Course cs101("CS101", "Intro to CS", 3, "Basics of CS", ap);
        system.addCourse(cs101);

        system.enrollStudentInCourse("CS101", "S123");
        system.enrollStudentInCourse("CS101", "S124");

        system.enterGrade("S123", 85);
        system.enterGrade("S124", 45);

        system.displayAllPeople();

        delete ap;
        delete u1;
        delete g1;

    } catch (UniversitySystemException& e) {
        logError(e.what());
    } catch (exception& e) {
        logError(string("Unexpected error: ") + e.what());
    }
    return 0;
}
