/*
* Programmer: Jesse Watson
* Current Class: CptS 122, Spring 2022; Lab Section 6
* Assignment: CrimsonCode Hackathon 2022
* Date: February 19, 2022
* Description: This program takes a .csv of a student's past and upcoming assignments for the semester and allows them
*			   to view the assignments by date, priority, class, upcoming, and past.
*/

#include "Assignments.h"

int main()
{
	int option = 0;

	system("color 0c"); // Red text because coug

	FILE* infile = NULL;

	infile = fopen("Assignments Spring 2022.csv", "r");

	if (infile != NULL) // File opened
	{











		do
		{
			printMenu();
			option = promptForOption(1, 4);

			switch (option)
			{
			case 1: // Print all

				break;
			case 2: // Print upcoming week of assignments

				break;
			case 3: // Print past assignments

				break;

			case 4: // Exit
				break;
			}
		} while (option != 4);




		fclose(infile);
	}
	else // File not opened
	{
		printf("File could not be opened!");
	}

	return 0;
}