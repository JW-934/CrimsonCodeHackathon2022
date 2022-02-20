/*
* Programmer: Jesse Watson
* Current Class: CptS 122, Spring 2022; Lab Section 6
* Assignment: CrimsonCode Hackathon 2022
* Date: February 19, 2022
* Description: This program takes a .csv of a student's past and upcoming assignments for the semester and allows them
*			   to view the assignments by date, priority, class, upcoming, and past. The .csv file is intended to be
*			   stored in Microsoft Onedrive so the program will be kept up to date through their cloud service.
* 
*			   The overall intent is to allow students to effectively manage their time by showing what would be the 
*			   most beneficial things for them to work on at any given time by analysing priority and due dates.
*/

#include "Assignments.h"

int main()
{
	int option = 0, numAssignments = 0;
	char line[100] = "", newDate[10] = "", newStatus[15] = "", newType[15] = "", newTopic[50] = "", newCourse[15] = "";
	Node* pHead = NULL;

	system("color 0c"); // Red text because Coug

	FILE* infile = NULL;

	infile = fopen("Assignments Spring 2022.csv", "r");

	if (infile != NULL) // File opened
	{
		// discards header
		fgets(line, 100, infile);
		// puts(line);
		line[0] = '/0';
		// Loads contents of file into linked list
		while (fgets(line, 100, infile) != NULL)
		{
			puts(line);
			scanLine(line, newDate, newStatus, newType, newTopic, newCourse);

			insertFront(&pHead, newDate, newStatus, newType, newTopic, newCourse);

			setVarsToDefault(line, newDate, newStatus, newType, newTopic, newCourse);

			++numAssignments;
		}
		fclose(infile);
		printf("Playlist loaded!\n\n");

		do
		{
			printMenu();
			option = promptForOption(1, 4);

			switch (option)
			{
			case 1: // Print all
				printListRec(pHead);
				break;
			case 2: // Print upcoming week of assignments

				break;
			case 3: // Print past assignments

				break;

			case 4: // Exit
				break;
			}
		} while (option != 4);




		//fclose(infile);
	}
	else // File not opened
	{
		printf("File could not be opened!");
	}

	return 0;
}