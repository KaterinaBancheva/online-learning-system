#include "Course.h"
#include <iostream>

int Course::findTaskByDescription(const MyString& description) const
{
	for (size_t i = 0; i < students.getSize(); i++)
	{
		if (tasks[i].getDescription() == description)
		{
			return i;
		}
	}

	return -1;
}

int Course::findStudentBId(unsigned id) const
{
	for (size_t i = 0; i < students.getSize(); i++)
	{
		if (students[i]->getId() == id)
		{
			return i;
		}
	}

	return -1;
}

bool Course::contains(const Student& student) const
{
	for (size_t i = 0; i < students.getSize(); i++)
	{
		if (students[i]->getId() == student.getId())
		{
			return true;
		}
	}
	return false;
}

//int Course::findStudentByIdBinary(MyVector<User*>& users, unsigned id)
//{
//	int left = 0;
//	int right = users.getSize() - 1;
//	
//	while (left <= right)
//	{
//		int middle = left + (right - left) / 2;
//		if (users[middle]->getId() == id)
//		{
//			return middle;
//		}
//		else if (users[middle]->getId() < id)
//		{
//			left = middle + 1;
//		}
//		else
//		{
//			right = middle - 1;
//		}
//	}
//
//	return -1;
//}

Course::Course(const MyString& courseName, const Teacher& teacher, const MyString& password)
{
	this->courseName = courseName;
	this->teacher = &teacher;
	this->password = password;
}

const MyString Course::getCourseName() const
{
	return courseName;
}

unsigned Course::getTeacherId() const
{
	return teacher->getId();
}

void Course::createInitialPassword(const MyString& password)
{
	if (password.getSize() == 0)
		this->password = password;
	else
		throw std::logic_error("Password is already created");
}

void Course::addTask(const Task& task)
{
	tasks.push_back(task);
}

void Course::addTask(Task&& task)
{
	tasks.push_back(std::move(task));
}

void Course::printTaskSubmissions(const MyString& taskName) const
{
	int indx = findTaskByDescription(taskName);
	if (indx == -1)
		throw std::logic_error("Invalid task desription");
	else
		tasks[indx].printTaskSubmissions();
}

void Course::addTaskSubmission(const MyString& taskDescription, const Answer& answer)
{
	for (size_t i = 0; i < tasks.getSize(); i++)
	{
		if (tasks[i].getDescription() == taskDescription)
		{
			tasks[i].addAnswer(answer);
			return;
		}
	}

	std::cout << "Task does not exist!";
}

void Course::addTaskSubmission(const MyString& taskDescription, Answer&& answer)
{
	for (size_t i = 0; i < tasks.getSize(); i++)
	{
		if (tasks[i].getDescription() == taskDescription)
		{
			tasks[i].addAnswer(std::move(answer));
			return;
		}
	}

	std::cout << "Task does not exist!";
}

void Course::addStudent(Student& student)
{
	if (!contains(student))
	{
		students.push_back(&student);
	}
}

void Course::addStudent(Student& student, const MyString& password)
{
	if (!contains(student) && password == this->password)
	{
		students.push_back(&student);
	}
}

void Course::gradeStudent(unsigned id, const MyString& task)
{
	if (findTaskByDescription(task) >= 0)
	{
		double grade = 0;
		MyString description;
		std::cin >> grade >> description;
		Grade temp(courseName, task, grade, description);

		int index = findStudentBId(id);
		if (index >= 0)
		{
			students[index]->addGrade(std::move(temp));
		}
		else
		{
			throw std::invalid_argument("Invalid id");
		}
	}

	else
	{
		throw std::invalid_argument("Invalid task description");
	}
}

void Course::saveToFile(std::ofstream& ofs) const
{
	courseName.write(ofs);

	ofs.write((const char*)teacher->getId(), sizeof(unsigned));

	ofs.write((const char*)students.getSize(), sizeof(size_t));
	for (size_t i = 0; i < students.getSize(); i++)
	{
		ofs.write((const char*)students[i]->getId(), sizeof(unsigned));
	}

	ofs.write((const char*)tasks.getSize(), sizeof(size_t));
	for (size_t i = 0; i < tasks.getSize(); i++)
		tasks[i].saveToFile(ofs);

	password.write(ofs);
}

void Course::readFromFile(std::ifstream& ifs, MyVector<User*>& users)
{
	courseName.read(ifs);

	size_t size = 0;
	ifs.read((char*)&size, sizeof(size));
	unsigned id = 0;
	for (size_t i = 0; i < size; i++)
	{
		ifs.read((char*)&id, sizeof(id));

		int indx = -1;

		for (size_t i = 0; i < users.getSize(); i++)
		{
			if (users[i]->getId() == id)
			{
				indx = i;
			}
		}

		if (indx != -1)
		{
			students.push_back(dynamic_cast<Student*>(users[indx]));
		}

	}

	ifs.read((char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		tasks[i].readFromFile(ifs);
	}

	ifs.read((char*)&password, sizeof(password));
}
