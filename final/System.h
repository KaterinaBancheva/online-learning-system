#pragma once
#include "Course.h"
#include "LoggedUser.h"
#include "UserFactory.h"

namespace FileNames
{
	static const MyString courses = "Courses.dat";
	static const MyString users = "Users.dat";
	static const MyString admin = "Admin.dat";
}

class System
{
protected:
	Administrator admin;
	MyVector<Course> courses;
	MyVector<User*> users;
	LoggedUser loggedUser;

	void freeUsers();

	void loadCourses(const MyString& filename, MyVector<User*> users);
	void loadUsers(const MyString& filename);

	void saveCoursesToFile(const MyString& filename) const;
	void saveUsersToFile(const MyString& filename) const;
	void saveAdminToFile(const MyString& filename) const;

	System();
	~System();
public:
	System(const System& other) = delete;
	System(System&& other) noexcept = delete;

	static System& getInstance();

	// get set
	const LoggedUser& getLogedUser() const;
	Student* getStudentById(unsigned id) const;
	int getUserIndexByName(const MyString& name, const MyString& familyName);
	int getUserIndexById(unsigned id) const;
	int findCourseByName(const MyString& courseName) const;

	void load();
	LoggedUser logIn(unsigned id, const MyString& password);
	void logOut();
	//void saveMessage(const MailBox& mail);

	void sendMessageTo(const MyString& userName, const MyString& familyName, const MyString& message);
	void checkMailbox() const;
	void printInfo() const;

	//students
	void enterCourse(const MyString& courseName, const MyString& password);
	void submitTask(const MyString& course, const MyString& taskDescription, const Answer& answer);
	void reviewGrades();

	//teachers
	void createCourse(const MyString& coursename, const MyString& password);
	void addToCourse(const MyString& course, Student& student);
	void createTask(const MyString& description, const MyString& course);
	void createInitialPassword(const MyString& course, const MyString& password);
	void gradeTask(const MyString& course, const MyString& task, unsigned studentId);
	void viewTaskSubmissions(const MyString& task, const MyString& course) const;

	//administrator
	void createTeacher(const MyString& name, const MyString& familyName, const MyString& password);
	void deleteTeacher(unsigned id);
	void createStudent(const MyString& name, const MyString& familyName, const MyString& password);
	void deleteStudent(unsigned id);
};



