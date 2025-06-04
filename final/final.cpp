//Katerina Bancheva 
//1MI0600482

#include <iostream>
#include "MyString.h"
#include "System.h"

void adminFunctions(System& s)
{
	std::cout << "Create/delete teacher/student \n";

	MyString buffer;
	std::cout << ">";
	std::cin >> buffer;
	if (buffer == "create_teacher")
	{
		std::cin >> buffer;
		MyString name;
		std::cin >> name;
		MyString pass;
		std::cin >> pass;
		s.createTeacher(buffer, name, pass);
	}
	else if (buffer == "create_student")
	{
		std::cin >> buffer;
		MyString name;
		std::cin >> name;
		MyString pass;
		std::cin >> pass;
		s.createStudent(buffer, name, pass);
	}
	else if (buffer == "delete_teacher")
	{
		std::cin >> buffer;
		unsigned id;
		std::cin >> id;
		s.deleteTeacher(id);
	}
	else if (buffer == "delete_student")
	{
		std::cin >> buffer;
		unsigned id;
		std::cin >> id;
		s.deleteStudent(id);
	}
	else if (buffer == "send_message_to")
	{
		std::cin >> buffer;
		MyString familyName, mess;
		std::cin >> familyName;
		std::cin >> mess;
		s.sendMessageTo(buffer, familyName, mess);
	}
	else if (buffer == "check_mailbox")
	{
		s.checkMailbox();
	}
	else if (buffer == "change_password")
	{
		std::cin >> buffer;
		s.getLoggedUser().getPtr()->changePassword(buffer);
	}
	std::cout << std::endl;
}

void teacherFunctions(System& s)
{
	std::cout << "Create course/task/initial_password \nAdd student to course \nView task submissions \nGrade task \n";

	MyString buffer;
	std::cout << ">";
	std::cin >> buffer;
	if (buffer == "create_course")
	{
		std::cin >> buffer;
		MyString pass;
		std::cin >> pass;
		s.createCourse(buffer, pass);
	}
	else if (buffer == "create_task")
	{
		std::cin >> buffer;
		MyString course;
		std::cin >> course;
		s.createTask(buffer, course);
	}
	else if (buffer == "create_initial_password")
	{
		std::cin >> buffer;
		MyString pass;
		std::cin >> pass;
		s.createInitialPassword(buffer, pass);
	}
	else if (buffer == "add_student_to_course")
	{
		std::cin >> buffer;
		unsigned ID;
		std::cin >> ID;
		s.addToCourse(buffer, *s.getStudentById(ID));
	}
	else if (buffer == "view_task_submissions")
	{
		std::cin >> buffer;
		MyString course;
		std::cin >> course;
		s.viewTaskSubmissions(buffer, course);
	}
	else if (buffer == "grade_task")
	{
		std::cin >> buffer;
		MyString task;
		std::cin >> task;
		unsigned ID;
		std::cin >> ID;
		s.gradeTask(buffer, task, ID);
	}
	else if (buffer == "send_message_to")
	{
		std::cin >> buffer;
		MyString familyName, mess;
		std::cin >> familyName;
		std::cin >> mess;
		s.sendMessageTo(buffer, familyName, mess);
	}
	else if (buffer == "check_mailbox")
	{
		s.checkMailbox();
	}
	else if (buffer == "change_password")
	{
		std::cin >> buffer;
		s.getLoggedUser().getPtr()->changePassword(buffer);
	}
	std::cout << std::endl;
}

void studentFunctions(System& s)
{
	std::cout << "Enter course \nSubmit task \nReview grades \n";

	MyString buffer;
	std::cout << ">";
	std::cin >> buffer;

	if (buffer == "enter_course")
	{
		std::cin >> buffer;
		MyString pass;
		std::cin >> pass;
		s.enterCourse(buffer, pass);
	}
	else if (buffer == "submit_task")
	{
		std::cin >> buffer;
		MyString description, ans;
		std::cin >> description;
		std::cin >> ans;
		Answer a(s.getLoggedUser().getStudentPtr()->getName(), ans);
		s.submitTask(buffer, description, a);
	}
	else if (buffer == "review_grades")
	{
		s.reviewGrades();
	}
	else if (buffer == "send_message_to")
	{
		std::cin >> buffer;
		MyString familyName, mess;
		std::cin >> familyName;
		std::cin >> mess;
		s.sendMessageTo(buffer, familyName, mess);
	}
	else if (buffer == "check_mailbox")
	{
		s.checkMailbox();
	}
	else if (buffer == "change_password")
	{
		std::cin >> buffer;
		s.getLoggedUser().getPtr()->changePassword(buffer);
	}
	std::cout << std::endl;
}

void helpMenu(UserType user, System& s)
{
	std::cout << "Send message to \nCheck mailbox \nChange password \n";

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
		try {
			std::cout << ">";
			std::cin >> buffer;

			if (system.getLoggedUser().getPtr() != nullptr)
			{
				if (buffer == "logout")
				{
					system.logOut();
				}
				else
				{
					helpMenu(system.getLoggedUser().getUserType(), system);
				}
			}
			else if (buffer == "login")
			{
				unsigned id;
				std::cin >> id;
				if (system.getUserIndexById(id) != -1)
				{
					std::cin >> buffer;
					system.logIn(id, buffer);
					std::cout << "Login successful! \n";
					helpMenu(system.getLoggedUser().getUserType(), system);
				}
			}
			else if (buffer == "exit")
			{
				system.exit();
				break;
			}
			else
			{
				std::cout << "Invalid command!\n";
			}
		}
		catch (std::invalid_argument& ex) {
			std::cout << ex.what() << "\n";
		}
		catch (std::logic_error& ex) {
			std::cout << ex.what() << "\n";
		}
	}

}
