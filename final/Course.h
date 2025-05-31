#pragma once
#include "Teacher.h"
#include "Student.h"
#include "Task.h"

class Course
{
private:
	MyString courseName;
	const Teacher* teacher;
	MyVector<Student*> students;
	MyVector<Task> tasks;
	MyString password;

	bool contains(const Student& student) const;
public:
	Course() = default;
	Course(const MyString& courseName, const Teacher& teacher, const MyString& password);

	int findStudentBId(unsigned id) const;
	int findTaskByDescription(const MyString& taskDescription) const;

	const MyString getCourseName() const;
	unsigned getTeacherId() const;
	void createInitialPassword(const MyString& password);

	void addTask(const Task& task);
	void addTask(Task&& task);
	void printTaskSubmissions(const MyString& taskName) const;

	void addTaskSubmission(const MyString& taskDescription, const Answer& answer);
	void addTaskSubmission(const MyString& taskDescription, Answer&& answer);

	void addStudent(Student& student);
	void addStudent(Student& student, const MyString& password);
	void gradeStudent(unsigned id, const MyString& task);

	void saveToFile(std::ofstream& ofs) const;
	void readFromFile(std::ifstream& ifs, MyVector<User*>& users);

};



