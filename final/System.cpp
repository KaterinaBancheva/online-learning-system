#include "System.h"
#include <iostream>
#include <fstream>

System& System::getInstance() 
{
	static System instance;
	return instance;
}

void System::load()
{
	loadUsers(FileNames::users);
	loadCourses(FileNames::courses, users);
}

LoggedUser System::logIn(unsigned id, const MyString& password)
{ 
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (id == users[i]->getId() && users[i]->matchingPass(password) == true)
		{
			loggedUser = users[i];
			if(users[i]->getId() != 0)
			{
				users[i]->printInfo();
			}
			return loggedUser;
		}
	}

	throw std::invalid_argument("Invalid login data!");
}

void System::logOut()
{
	if (loggedUser.getPtr() != nullptr)
	{
		/*saveAdminToFile(FileNames::admin);
		saveCoursesToFile(FileNames::courses);
		saveUsersToFile(FileNames::users);*/

		loggedUser.setAllPoinetersToNull();
		std::cout << "Logout successful! \n";
	}
	else
	{
		throw std::logic_error("No user is logged in!");
	}
}

void System::exit() const
{
	saveAdminToFile(FileNames::admin);
	saveCoursesToFile(FileNames::courses);
	saveUsersToFile(FileNames::users);
}

void System::sendMessageTo(const MyString& userName, const MyString& familyName, const MyString& message)
{
	int indx = getUserIndexByName(userName, familyName);

	if (indx == -1) 
	{
		throw std::invalid_argument("User not found!");
	}

	//MyString firstName = userName;
	MyString userNameeee = loggedUser.getPtr()->getName() + " " + loggedUser.getPtr()->getFamilyName();
	//MyString userNameeee = userName + " " + familyName;
	Message m = Message(message, userNameeee);
	loggedUser.getPtr()->sendMessageTo(users[indx], m);
	std::cout << "Message sent to " << userName << " " << familyName << "\n";
}

void System::checkMailbox() const
{
	loggedUser.getPtr()->checkMailbox();
}

void System::printInfo() const
{
	loggedUser.getPtr()->printInfo();
}

void System::enterCourse(const MyString& courseName, const MyString& password)
{
	if (loggedUser.getStudentPtr() == nullptr)
	{
		throw std::logic_error("Only students can enter courses!");
	}

	int index = findCourseByName(courseName);
	if (index != -1)
	{
		courses[index].addStudent(*loggedUser.getStudentPtr());
	}
	else
	{
		throw std::logic_error("Invalid course");
	}
}

void System::submitTask(const MyString& course, const MyString& taskDescription, const Answer& answer)
{
	if (loggedUser.getStudentPtr() == nullptr)
	{
		throw std::logic_error("Only students can enter courses!");
	}

	int index = findCourseByName(course);
	if (index != -1)
	{
		if(courses[index].findStudentBId(loggedUser.getPtr()->getId()) != -1)
		{
			if(courses[index].findTaskByDescription(taskDescription) != -1)
			{
				courses[index].addTaskSubmission(taskDescription, answer); 
				std::cout << "Task submission added! \n";
			}
			else
			{
				throw std::logic_error("Invalid task!");
			}
		}
		else
		{
			throw std::logic_error("Invalid course!");
		}
	}
	else
	{
		throw std::logic_error("Invalid course!");
	}
}

void System::reviewGrades()
{
	if (loggedUser.getStudentPtr() == nullptr)
	{
		throw std::logic_error("Only students can enter courses!");
	}

	loggedUser.getStudentPtr()->reviewGrades();
}

void System::createCourse(const MyString& courseName, const MyString& password)
{
	if (loggedUser.getTeacherPtr() == nullptr)
	{
		throw std::logic_error("Only teachers can create courses!");
	}

	if (findCourseByName(courseName) != -1)
	{
		throw std::logic_error("This course already exists!");
	}

	Course c(courseName, *loggedUser.getTeacherPtr(), password);
	courses.push_back(std::move(c));
	std::cout << courseName << " created! \n";
}

void System::addToCourse(const MyString& course, Student& student)
{
	if (loggedUser.getTeacherPtr() == nullptr)
	{
		throw std::logic_error("Only teachers can add students to courses!");
	}
	else
	{
		unsigned id = findCourseByName(course);
		if (id == -1)
		{
			throw std::logic_error("This course does not exists!");
		}
		
		courses[id].addStudent(student);
		std::cout << "Student with id " << student.getId() << " added to course!\n";
	}
	//sortUsersById();
}

void System::createTask(const MyString& description, const MyString& course)
{
	if (loggedUser.getTeacherPtr() == nullptr)
	{
		throw std::logic_error("Only teachers can create tasks!");
	}

	int indx = findCourseByName(course);
	if (indx == -1)
	{
		throw std::logic_error("This course does not exists!");
	}

	if (courses[indx].getTeacherId() == loggedUser.getTeacherPtr()->getId())
	{
		Task temp = Task(description);
		courses[indx].addTask(std::move(temp));
		std::cout << description << " added! \n";
	}
	else
	{
		throw std::logic_error("No access to this course!");
	}
}

void System::createInitialPassword(const MyString& course, const MyString& password)
{
	if (loggedUser.getTeacherPtr() == nullptr)
	{
		throw std::logic_error("Only teachers can create tasks!");
	}

	int indx = findCourseByName(course);
	if (indx == -1)
	{
		throw std::logic_error("This course does not exists!");
	}

	if (courses[indx].getTeacherId() == loggedUser.getTeacherPtr()->getId())
	{
		courses[indx].createInitialPassword(password);
	}
	else
	{
		throw std::logic_error("No access to this course!");
	}
}

void System::gradeTask(const MyString& course, const MyString& task, unsigned studentId)
{
	if (loggedUser.getTeacherPtr() == nullptr)
	{
		throw std::logic_error("Only teachers can create tasks!");
	}

	int courseIndx = findCourseByName(course);
	if (courseIndx == -1)
	{
		throw std::logic_error("This course does not exists!");
	}

	if (courses[courseIndx].getTeacherId() == loggedUser.getTeacherPtr()->getId())
	{
		courses[courseIndx].gradeStudent(studentId, task);
		std::cout << task << " graded! \n";
	}
	else
	{
		throw std::logic_error("No access to this course!");
	}
}

void System::viewTaskSubmissions(const MyString& task, const MyString& course) const
{
	if (loggedUser.getTeacherPtr() == nullptr)
	{
		throw std::logic_error("Only teachers can create tasks!");
	}

	int courseIndx = findCourseByName(course);
	if (courseIndx == -1)
	{
		throw std::logic_error("This course does not exists!");
	}
	
	if (courses[courseIndx].getTeacherId() == loggedUser.getTeacherPtr()->getId())
	{
		int indx = courses[courseIndx].findTaskByDescription(task);
		if (indx == -1)
		{
			throw std::logic_error("This task does not exists!");
		}

		courses[courseIndx].printTaskSubmissions(task);
	}
	else
	{
		throw std::logic_error("No access to this course!");
	}
}

void System::createTeacher(const MyString& name, const MyString& familyName, const MyString& password)
{
	Teacher* ptr = new Teacher(name, familyName, password);
	users.push_back(ptr);
	std::cout << "Teacher with id " << ptr->getId() << " created!\n";
}

void System::deleteTeacher(unsigned id)
{
	int indx = getUserIndexById(id);
	if (indx != -1)
	{
		users.erase(indx);
		std::cout << "Deleted teacher with id " << id << "! \n";
	}
	else
	{
		throw std::invalid_argument("Invalid teacher id!");
	}
}

void System::createStudent(const MyString& name, const MyString& familyName, const MyString& password)
{
	Student* ptr = new Student(name, familyName, password);
	users.push_back(ptr);
	std::cout << "Student  with id " << ptr->getId() << " created!\n";
}

void System::deleteStudent(unsigned id)
{
	int indx = getUserIndexById(id);
	if (indx != -1)
	{
		users.erase(indx);
		std::cout << "Deleted student with id " << id << "! \n";
	}
	else
	{
		throw std::invalid_argument("Invalid teacher id!");
	}
}

const LoggedUser& System::getLoggedUser() const
{
	return loggedUser;
}

Student* System::getStudentById(unsigned id) const
{
	int i = getUserIndexById(id);
	if (i != -1)
		return dynamic_cast<Student*>(users[i]);
	else
		throw std::logic_error("Invalid student id!\n");
}

int System::getUserIndexByName(const MyString& name, const MyString& familyName)
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getName() == name && users[i]->getFamilyName() == familyName)
			return i;
	}

	return -1;
}

int System::getUserIndexById(unsigned id) const
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i]->getId() == id)
			return i;
	}

	return -1;
}

int System::findCourseByName(const MyString& courseName) const
{
	for (size_t i = 0; i < courses.getSize(); i++)
	{
		if (courses[i].getCourseName() == courseName)
			return i;
	}

	return -1;
}

void System::freeUsers()
{
	users.clear();
}

void System::loadCourses(const MyString& filename, MyVector<User*>& users)
{
	std::ifstream ifs(filename.c_str(), std::ios::binary);

	size_t size = 0;
	ifs.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		Course temp;
		temp.readFromFile(ifs, users);
		courses.push_back(temp); 
	}
}

void System::loadUsers(const MyString& filename)
{
	std::ifstream ifs((const char*)&filename, std::ios::binary);
	
	size_t size = 0;
	ifs.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		UserFactory factory;
		User* toAdd = factory.createUser(ifs);
		if(toAdd->getId() != 0)
			users.push_back(toAdd);
	}
}

void System::saveCoursesToFile(const MyString& filename) const
{	
	std::ofstream ofs(filename.c_str(), std::ios::binary);
	size_t coursesSize = courses.getSize();
	ofs.write((const char*)&coursesSize, sizeof(size_t));
	for (size_t i = 0; i < courses.getSize(); i++)
	{
		courses[i].saveToFile(ofs);
	}
}


void System::saveUsersToFile(const MyString& filename) const
{
	std::ofstream ofs(filename.c_str(), std::ios::binary);
	size_t usersSize = users.getSize();
	ofs.write((const char*)&usersSize, sizeof(size_t));
	for (size_t i = 0; i < users.getSize(); i++)
	{
		users[i]->saveToFile(ofs);
	}
}

void System::saveAdminToFile(const MyString& filename) const
{
	std::ofstream ofs(filename.c_str(), std::ios::binary);
	admin.saveToFile(ofs);
}

System::System()
{
	std::ifstream ifs("Admin.bin", std::ios::binary);
	if (ifs.is_open()) 
	{
		admin.readFromFile(ifs);
		ifs.close();
	}
	else
	{
		ifs.close();
		
		std::ofstream ofs("Admin.bin", std::ios::binary);
		if (!ofs.is_open()) 
		{
			throw std::exception("Could not open admin file!");
		}
		admin.saveToFile(ofs);
	}

	admin.setId();
	admin.setPassword("0000");
	admin.setNames("Administrator", " ");

	load();
	users.push_back(&admin);
}

System::~System()
{
	saveAdminToFile(FileNames::admin);
	saveCoursesToFile(FileNames::courses);
	saveUsersToFile(FileNames::users);
	freeUsers();
}
