/*
* Programmer: Jesse Watson
* Current Class: CptS 122, Spring 2022; Lab Section 6
* Assignment: CrimsonCode Hackathon 2022
* Date: February 19, 2022
* Description: This program takes a .csv of a student's past and upcoming assignments for the semester and allows them
*			   to view the assignments by date, priority, class, upcoming, and past. The .csv file is intended to be 
*			   stored in Microsoft Onedrive so the program will be kept up to date through their cloud service.
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

int insertFront(Node** pList, char* newDate, char* newStatus, char* newType, char* newTopic, char* newClass)
{
	Node* newNode = makeNode(newDate, newStatus, newType, newTopic, newClass);
	int success = 0;

	if (newNode != NULL) // successfully allocated space on heap for Node
	{
		if (*pList != NULL) // non empty list
		{
			newNode->pNext = *pList;
		}
		*pList = newNode;
		success = 1;
	}
	return success;
}

Node* makeNode(char* newDate, char* newStatus, char* newType, char* newTopic, char* newClass)
{
	// Allocates memory for Node, Assignment, and Date
	Node* newNode = (Node*)malloc(sizeof(Node));
	Assignment* newAssign = (Assignment*)malloc(sizeof(Assignment));
	Date* newDateStruct = (Date*)malloc(sizeof(Date));

	if (newNode != NULL && newAssign != NULL && newDateStruct != NULL)
	{
		// Put date into Date
		newDateStruct->month = atoi(strtok(newDate, "/"));
		newDateStruct->day = atoi(strtok(NULL, "/"));
		newDateStruct->year = atoi(strtok(NULL, ",")) + 2000; // file uses last two numbers of the year so add 2000
	
		// Put Date into Assignment
		newAssign->dueDate = *newDateStruct;

		// Put strings into Assignment
		strcpy(newAssign->status, newStatus);
		strcpy(newAssign->type, newType);
		strcpy(newAssign->topic, newTopic);
		strcpy(newAssign->class, newClass);
	}
	return newNode;
}

void printMenu()
{
	printf("******************** Assignment Manager ********************\n*                                                          *\n");
	printf("*                1. Display all assignments                *\n*           2. Print upcoming week of assignments          *\n*                 3. Print past assignments                *\n*                          4. Exit                         *\n*                                                          *\n");
	printf("************************************************************\n");
}

void scanLine(char* line, char* newDate, char* newStatus, char* newType, char* newTopic, char* newClass)
{
	// Populates new node variables with corresponding values from line
	strcpy(newDate, strtok(line, ","));
	if (newStatus[0] == '\0')
	{
		strcpy(newStatus, "Incomplete");
	}
	else
	{
		strcpy(newStatus, newStatus);
	}
	// strcpy(newStatus, strtok(NULL, ","));
	strcpy(newType, strtok(NULL, ","));
	strcpy(newTopic, strtok(NULL, ","));
	strcpy(newClass, strtok(NULL, "\n"));
}

void setVarsToDefault(char* line, char* newDate, char* newStatus, char* newType, char* newTopic, char* newClass)
{
	line[0] = '\0';
	newDate[0] = '\0';
	newStatus[0] = '\0';
	newType[0] = '\0';
	newClass[0] = '\0';
}