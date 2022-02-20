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

#ifndef ASSIGNMENTS_H

#define ASSIGNMENTS_H
#define _CRT_SECURE_NO_WARNINGS
//#define INPUTFILE "Assignments Spring 2022.csv"
#define INPUTFILE "Testing.csv"

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>

typedef struct date
{
	int month;
	int day;
	int year;
}Date;

typedef struct assignment
{
	Date dueDate;
	char status[15];
	char type[15];
	char topic[50];
	char course[20];
}Assignment;

typedef struct node
{
	Assignment assignment;
	struct node* pNext;
}Node;

int promptForOption(int lowerBound, int upperBound);

Node* makeNode(char* newDate, char* newStatus, char* newType, char* newTopic, char* newCourse);

void printMenu();
void scanLine(char* line, char* newDate, char* newStatus, char* newType, char* newTopic, char* newCourse);
void setVarsToDefault(char* line, char* newDate, char* newStatus, char* newType, char* newTopic, char* newCourse);
void starsInEmptyFields(char* str, int length);
void insertFront(Node** pList, char* newDate, char* newStatus, char* newType, char* newTopic, char* newCourse);
void printList(Node* pHead);
void printListRec(Node* pHead);
#endif