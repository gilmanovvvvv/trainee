#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

struct Student {
    int id;
    std::string name;
    int age;
};

class StudentDatabase {
public:
    void addStudent(int id, std::string name, int age) {
        if (id <= 0) {
            throw std::invalid_argument("Students id must be natural integer");
        }
        std::shared_ptr<Student> student = std::make_shared<Student>();
        student->id = id;
        student->name = name;
        student->age = age;
        {
            std::lock_guard<std::mutex> lock(students_mutex);
            students.push_back(student);
        }
    }

    void removeStudent(int id) {
        std::shared_ptr<Student> student;
        {
            std::lock_guard<std::mutex> lock(students_mutex);
            auto it = std::find_if(students.begin(), students.end(), [id](std::shared_ptr<Student> student) { return student->id == id; });
            if (it != students.end()) {
                student = *it;
                students.erase(it);
            }
        }
        if (student) {
            std::thread([&student]() { student.reset(); }).detach();
        }
    }

    std::shared_ptr<Student> getStudent(int id) {
        if (id <= 0) {
            throw std::invalid_argument("Students id must be natural integer");
        }
        std::shared_ptr<Student> student;
        {
            std::lock_guard<std::mutex> lock(students_mutex);
            auto it = std::find_if(students.begin(), students.end(), [id](std::shared_ptr<Student> student) { return student->id == id; });
            if (it != students.end()) {
                student = *it;
            }
        }
        return student;
    }

private:
    std::vector<std::shared_ptr<Student>> students;
    std::mutex students_mutex;
};
