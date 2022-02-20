/*
* Programmer: Jesse Watson
* Current Class: CptS 122, Spring 2022; Lab Section 6
* Assignment: CrimsonCode Hackathon 2022
* Date: February 19, 2022
* Description: This program takes a .csv of a student's past and upcoming assignments for the semester and allows them
*			   to view the assignments by date, priority, class, upcoming, and past. The .csv file is intended to be
*			   stored in Microsoft Onedrive so the program will be kept up to date through their cloud service.
*/

#ifndef ASSIGNMENTS_H

#define ASSIGNMENTS_H
#define _CRT_SECURE_NO_WARNINGS

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
	char* type[15];
	char* topic[50];
	char* class[15];
}Assignment;

typedef struct node
{
	Assignment assignment;
	struct node* pNext;
}Node;

int promptForOption(int lowerBound, int upperBound);
int insertFront(Node** pList, char* newDate, char* newStatus, char* newType, char* newTopic, char* newClass);

Node* makeNode(char* newDate, char* newStatus, char* newType, char* newTopic, char* newClass);

void printMenu();
void scanLine(char* line, char* newDate, char* newStatus, char* newType, char* newTopic, char* newClass);
void setVarsToDefault(char* line, char* newDate, char* newStatus, char* newType, char* newTopic, char* newClass);
#endif