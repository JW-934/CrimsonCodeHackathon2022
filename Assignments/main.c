/*
* Programmer: Jesse Watson
* Current Class: CptS 122, Spring 2022; Lab Section 6
* Assignment: CrimsonCode Hackathon 2022
* Date: February 19, 2022
* Description: This program takes a .csv of a student's past and upcoming assignments for the semester and allows them
*			   to view the assignments by date, priority, class, upcoming, and past. The .csv file is intended to be
*			   stored in Microsoft Onedrive so the program will be kept up to date through their cloud service. I would
*			   also like to include some other elements like on campus resources and a list of the user's friends that
*			   are in the same classes for support but I doubt I will have the time to get it all working.
* 
*			   The overall intent is to allow students to effectively manage their time by showing what would be the 
*			   most beneficial things for them to work on at any given time by analyzing priority and due dates. 
*/

#include "Assignments.h"

int main()
{
	int option = 0, numAssignments = 0, currentMonth = 0, currentDay = 0, currentYear = 0;
	char line[100] = "", newDate[10] = "", newStatus[15] = "", newType[15] = "", newTopic[50] = "", newCourse[20] = "", targetCourse[20] = "", targetPriority[30] = "";
	Node* pHead = NULL;
	
	time_t now;
	time(&now);
	struct tm* local = localtime(&now);

	// Gets current date to show upcoming assignments
	currentMonth = local->tm_mon + 1;
	currentDay = local->tm_mday;
	currentYear = local->tm_year + 1900;

	system("color 0c"); // Red text because Coug

	FILE* infile = NULL;

	infile = fopen(INPUTFILE, "r");

	if (infile != NULL) // File opened
	{
		// discards header
		fgets(line, 100, infile);
		
		// puts(line);
		line[0] = '/0';

		// Loads contents of file into linked list
		while (fgets(line, 100, infile) != NULL)
		{
			// Replaces empty fields with a *
			starsInEmptyFields(line, strlen(line));

			//puts(line);
			scanLine(line, newDate, newStatus, newType, newTopic, newCourse);
			//printf("%s, %s, %s, %s, %s", newDate, newStatus, newType, newTopic, newCourse);
			insertFront(&pHead, newDate, newStatus, newType, newTopic, newCourse);

			setVarsToDefault(line, newDate, newStatus, newType, newTopic, newCourse);

			++numAssignments;
		}
		fclose(infile);
		printf("Assignments loaded!\n\n");

		do
		{
			printMenu();
			option = promptForOption(1, 7);

			switch (option)
			{
			case 1: // Print all
				system("cls");
				//printListRec(pHead);
				printList(pHead);
				break;
			case 2: // Print upcoming week of assignments
				system("cls");

				printUpcomings(pHead, currentMonth, currentDay, currentYear);
				break;
			case 3: // Print past assignments
				system("cls");

				printPasts(pHead, currentMonth, currentDay, currentYear);
				break;

			case 4: // Print assignments from a certain course
				system("cls");

				strcpy(targetCourse, promptForCourse(pHead));
				puts(targetCourse);
				printCourseAssignments(pHead, targetCourse);

				targetCourse[0] = '\0';
				break;
			case 5: // Print by priority
				printByPriority(pHead);
				break;
			case 6: // Help
				system("cls");

				printResources();
				break;
			case 7: // Exit
				break;
			}
		} while (option != 7);
		//fclose(infile);
	}
	else // File not opened
	{
		printf("File could not be opened!");
	}

	return 0;
}