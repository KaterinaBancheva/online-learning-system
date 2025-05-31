#include <iostream>
#include "MyString.h"
#include "System.h"

void adminFunctions(System& s)
{
	std::cout << "Create/delete teacher/student \n";

	MyString buffer;
	std::cout << ">";
	std::cin >> buffer;
	if (buffer == "Create")
	{
		std::cin >> buffer;
		if (buffer == "teacher")
		{
			std::cin >> buffer;
			MyString name;
			std::cin >> name;
			MyString pass;
			std::cin >> pass;
			s.createTeacher(buffer, name, pass);
		}
		else if (buffer == "student")
		{
			std::cin >> buffer;
			MyString name;
			std::cin >> name;
			MyString pass;
			std::cin >> pass;
			s.createStudent(buffer, name, pass);
		}
	}
	else if (buffer == "Delete")
	{
		std::cin >> buffer;
		unsigned id;
		std::cin >> id;
		if (buffer == "teacher")
		{
			unsigned ID;
			std::cin >> ID;
			s.deleteTeacher(ID);
		}
		else if (buffer == "student")
		{
			unsigned ID;
			std::cin >> ID;
			s.deleteStudent(ID);
		}
	}
	else if (buffer == "Send")
	{
		std::cin >> buffer;
		if (buffer == "message")
		{
			std::cin >> buffer;
			if (buffer == "to")
			{
				std::cin >> buffer;
				MyString familyName, mess;
				std::cin >> familyName;
				std::cin >> mess;
				s.sendMessageTo(buffer, familyName, mess);
			}
		}
	}
	else if (buffer == "Check")
	{
		std::cin >> buffer;
		if (buffer == "mailbox")
		{
			s.checkMailbox();
		}
	}
	else if (buffer == "Change")
	{
		std::cin >> buffer;
		if (buffer == "password")
		{
			std::cin >> buffer;
			s.getLogedUser().getPtr()->changePassword(buffer);
		}
	}
}

void teacherFunctions(System& s)
{
	std::cout << "Create course/task/initial_password \n Add student to course \n View task submissions \n Grade task \n";

	MyString buffer;
	std::cout << ">";
	std::cin >> buffer;
	if (buffer == "Create")
	{
		std::cin >> buffer;
		if (buffer == "course")
		{
			std::cin >> buffer;
			MyString pass;
			std::cin >> pass;
			s.createCourse(buffer, pass);
		}
		else if (buffer == "task")
		{
			std::cin >> buffer;
			MyString course;
			std::cin >> course;
			s.createTask(buffer, course);
		}
		else if (buffer == "initial")
		{
			std::cin >> buffer;
			if (buffer == "password")
			{
				std::cin >> buffer;
				MyString pass;
				std::cin >> pass;
				s.createInitialPassword(buffer, pass);
			}
		}
	}
	else if (buffer == "Add")
	{
		std::cin >> buffer;
		if (buffer == "student")
		{
			std::cin >> buffer;
			if (buffer == "to")
			{
				std::cin >> buffer;
				if (buffer == "course")
				{
					std::cin >> buffer;
					unsigned ID;
					std::cin >> ID;
					s.addToCourse(buffer, *s.getStudentById(ID));
				}
			}
		}
	}
	else if (buffer == "View")
	{
		std::cin >> buffer;
		if (buffer == "task")
		{
			std::cin >> buffer;
			if (buffer == "submissions")
			{
				std::cin >> buffer;
				MyString course;
				std::cin >> course;
				s.viewTaskSubmissions(buffer, course);
			}
		}
	}
	else if (buffer == "Grade")
	{
		std::cin >> buffer;
		if (buffer == "task")
		{
			std::cin >> buffer;
			MyString task;
			std::cin >> task;
			unsigned ID;
			std::cin >> ID;
			s.gradeTask(buffer, task, ID);
		}
	}
	else if (buffer == "Send")
	{
		std::cin >> buffer;
		if (buffer == "message")
		{
			std::cin >> buffer;
			if (buffer == "to")
			{
				std::cin >> buffer;
				MyString familyName, mess;
				std::cin >> familyName;
				std::cin >> mess;
				s.sendMessageTo(buffer, familyName, mess);
			}
		}
	}
	else if (buffer == "Check")
	{
		std::cin >> buffer;
		if (buffer == "mailbox")
		{
			s.checkMailbox();
		}
	}
	else if (buffer == "Change")
	{
		std::cin >> buffer;
		if (buffer == "password")
		{
			std::cin >> buffer;
			s.getLogedUser().getPtr()->changePassword(buffer);
		}
	}
}

void studentFunctions(System& s)
{
	std::cout << "Enter course \n Submit task \n Review grades \n";

	MyString buffer;
	std::cout << ">";
	std::cin >> buffer;
	if (buffer == "Enter")
	{
		std::cin >> buffer;
		if (buffer == "course")
		{
			std::cin >> buffer;
			MyString pass;
			std::cin >> pass;
			s.enterCourse(buffer, pass);
		}

	}
	else if (buffer == "Submit")
	{
		std::cin >> buffer;
		if (buffer == "task")
		{
			std::cin >> buffer;
			MyString description, ans;
			std::cin >> description;
			std::cin >> ans;
			Answer a(s.getLogedUser().getStudentPtr()->getName(), ans);
			s.submitTask(buffer, description, a);
		}
	}
	else if (buffer == "Review")
	{
		std::cin >> buffer;
		if (buffer == "grades")
		{
			s.reviewGrades();
		}
	}
	else if (buffer == "Send") 
	{
		std::cin >> buffer;
		if (buffer == "message")
		{
			std::cin >> buffer;
			if (buffer == "to")
			{
				std::cin >> buffer;
				MyString familyName, mess;
				std::cin >> familyName;
				std::cin >> mess;
				s.sendMessageTo(buffer, familyName, mess);
			}
		}
	}
	else if (buffer == "Check")
	{
		std::cin >> buffer;
		if (buffer == "mailbox")
		{
			s.checkMailbox();
		}
	}
	else if (buffer == "Change")
	{
		std::cin >> buffer;
		if (buffer == "password")
		{
			std::cin >> buffer;
			s.getLogedUser().getPtr()->changePassword(buffer);
		}
	}
}

void helpMenu(UserType user, System& s)
{
	std::cout << "Send message to \n Check mailbox \n Change password \n";

	switch (user)
	{
	case UserType::admin:
		return adminFunctions(s);
	case UserType::teacher:
		return teacherFunctions(s);
	case UserType::student:
		return studentFunctions(s);
	}
}
int main()
{
	System& system = System::getInstance();
	
	MyString buffer;
	while (true)
	{
		std::cout << ">";
		std::cin >> buffer;
		if (buffer == "login")
		{
			unsigned id;
			std::cin >> id;
			if (system.getUserIndexById(id) != -1)
			{
				std::cin >> buffer;
				system.logIn(id, buffer);
				UserType type = system.getLogedUser().getUserType();

				while (true) {
					if (buffer == "logout") {
						system.logOut();
						break;
					}
					helpMenu(type, system);
				}
			}
		}
	}

}
