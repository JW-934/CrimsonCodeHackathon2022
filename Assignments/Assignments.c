/*
* Programmer: Jesse Watson
* Current Class: CptS 122, Spring 2022; Lab Section 6
* Assignment: CrimsonCode Hackathon 2022
* Date: February 19, 2022
* Description: This program takes a .csv of a student's past and upcoming assignments for the semester and allows them
*			   to view the assignments by date, priority, class, upcoming, and past.
*/

#include "Assignments.h"

int promptForOption(int lowerBound, int upperBound)
{
	int option = 0;

	printf("Make your selection > ");

	do
	{
		scanf(" %d", &option);
	} while (option < lowerBound || option > upperBound);

	return option;
}

Node* makeNode()

void printMenu()
{
	printf("******************** Assignment Manager ********************\n*                                                          *\n");
	printf("*                1. Display all assignments                *\n*           2. Print upcoming week of assignments          *\n*                 3. Print past assignments                *\n*                          4. Exit                         *\n*                                                          *\n");
	printf("************************************************************\n");
}