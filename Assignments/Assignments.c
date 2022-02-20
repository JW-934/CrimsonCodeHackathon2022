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
*			   most beneficial things for them to work on at any given time by analysing priority and due dates.
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

void insertFront(Node** pList, char* newDate, char* newStatus, char* newType, char* newTopic, char* newCourse) 
{
	Node* newNode = makeNode(newDate, newStatus, newType, newTopic, newCourse);

	if (newNode != NULL) // successfully allocated space on heap for Node
	{
		if (*pList != NULL) // non empty list
		{
			newNode->pNext = *pList;
		}
		else 
		{

		}
	}
	*pList = newNode;
}

Node* makeNode(char* newDate, char* newStatus, char* newType, char* newTopic, char* newCourse)
{
	// Allocates memory for Node, Assignment, and Date
	Node* newNode = (Node*)malloc(sizeof(Node));
	Assignment* newAssign = (Assignment*)malloc(sizeof(Assignment) * 2); // 2 * sizeof because for some reason every few executions 
	Date* newDateStruct = (Date*)malloc(sizeof(Date));					 // line 50 would "trigger a breakpoint" so somehow it 
																		 // wasn't allocating enough space some of the time?
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
		strcpy(newAssign->course, newCourse);

		// Put Assignment into Node
		newNode->assignment = *newAssign;

		newNode->pNext = NULL;
	}
	return newNode;
}

void printMenu()
{
	printf("******************** Assignment Manager ********************\n*                                                          *\n");
	printf("*                1. Display all assignments                *\n*           2. Print upcoming week of assignments          *\n*                 3. Print past assignments                *\n*                          4. Exit                         *\n*                                                          *\n");
	printf("************************************************************\n");
}

void scanLine(char* line, char* newDate, char* newStatus, char* newType, char* newTopic, char* newCourse)
{
	char tempStatus[15] = "";
	// Populates new node variables with corresponding values from line
	strcpy(newDate, strtok(line, ","));
	strcpy(tempStatus, strtok(NULL, ","));

	if (strcmp(tempStatus, "*") == 0)
	{
		strcpy(newStatus, "INCOMPLETE");
	}
	else
	{
		if (strcmp(tempStatus, "Complete") == 0)
		{
			strcpy(newStatus, "~COMPLETE~");
		}
		else
		{
			strcpy(newStatus, tempStatus);
		}
	}

	strcpy(newType, strtok(NULL, ","));
	strcpy(newTopic, strtok(NULL, ","));
	strcpy(newCourse, strtok(NULL, "\n"));
}

void setVarsToDefault(char* line, char* newDate, char* newStatus, char* newType, char* newTopic, char* newCourse)
{
	line[0] = '\0';
	newDate[0] = '\0';
	newStatus[0] = '\0';
	newType[0] = '\0';
	newCourse[0] = '\0';
}

void starsInEmptyFields(char* str, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (str[i] == ',' && str[i + 1] == ',') // back to back commas (empty field)
		{
			for (int j = 0; j < length - i; j++)
			{
				str[(length - j) + 1] = str[length - j];
			}
			str[i + 1] = '*';
		}
		if (str[i] == ',' && str[i + 1] == '\n') // comma at the end of a line (missing sleep level)
		{
			str[i + 1] = '*';
			str[i + 2] = '/n';
		}
	}
	return;
}

void printList(Node *pHead)
{
	Node* pCur = pHead;
	while (pCur != NULL)
	{
		printf("%d/%d/%d %s %s %s %s\n", pCur->assignment.dueDate.month, pCur->assignment.dueDate.day, pCur->assignment.dueDate.year,
			pCur->assignment.status, pCur->assignment.type, pCur->assignment.topic, pCur->assignment.course);
		pCur = pCur->pNext;
	}
	putchar('\n');
}

void printListRec(Node* pHead)
{
	if (pHead != NULL)
	{
		printf("--> %d/%d/%d %s %s %s %s\n", pHead->assignment.dueDate.month, pHead->assignment.dueDate.day, pHead->assignment.dueDate.year,
			pHead->assignment.status, pHead->assignment.type, pHead->assignment.topic, pHead->assignment.course);
		printListRec(pHead->pNext);
	}
	else 
	{
		printf("\n");
	}
}

void printUpcomings(Node* pHead, int curMonth, int curDay, int curYear)
{
	Node* pCur = pHead;

	if (pCur != NULL)
	{
		while (pCur != NULL)
		{
			if ((pCur->assignment.dueDate.month == curMonth && pCur->assignment.dueDate.day == curDay 
				&& pCur->assignment.dueDate.year == curYear) || (pCur->assignment.dueDate.month == curMonth 
				&& pCur->assignment.dueDate.year == curYear && (pCur->assignment.dueDate.day == curDay + 1
				|| pCur->assignment.dueDate.day == curDay + 2 || pCur->assignment.dueDate.day == curDay + 3
				|| pCur->assignment.dueDate.day == curDay + 4 || pCur->assignment.dueDate.day == curDay + 5
				|| pCur->assignment.dueDate.day == curDay + 6 )))
			{
				printf("%d/%d/%d %s %s %s %s\n", pCur->assignment.dueDate.month, pCur->assignment.dueDate.day, pCur->assignment.dueDate.year,
					pCur->assignment.status, pCur->assignment.type, pCur->assignment.topic, pCur->assignment.course);
			}
			pCur = pCur->pNext;
		}
	}
}