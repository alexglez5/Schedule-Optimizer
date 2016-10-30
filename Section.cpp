//
//  Section.cpp
//  MasterSchedule
//
//  Team #9 Semester Project COP3503
//  Created by Kimberly Price, Alexander Gonzalez, Andrew Chabab, and Jamal West
//  Documented by Kaji Rashad and Alberto Molina
//  Copyright © 2016. All rights reserved.

#include <stdio.h>
#include "Section.h"

/* Alexander Gonzalez
* Section objects and class implementation
*/


/*
The section class handles the different sections a class
can have; each section will have a day array and a time
array for the different possible meeting times and days
each section can have. When the information is passed to
the constructor (the section number and the days/times)
the different day/time combinations are stored into their
respective arrays.
*/

//Creates an empty section necessary for potential sections
//that are not needed by the user
Section::Section() {//dummy section edited by Kim
	sectionNum = "";
	for (int i = 0; i < 10; i++) {
		days[i] = -1;
		periods[i] = -1;
	}
}

//Setter method used as constructor
void Section::set(string sectionNum, string timeAvbl, string day[], string period[]) {
	this->timeAvbl = timeAvbl;
	this->sectionNum = sectionNum;
	string temp;
	for (int i = 0; i < 10; i++) {
		//switch statement created by Kim
		switch (day[i][0]) {  //check the first character of the string at index i of day array
		case 'm':
		case 'M': days[i] = 0; break;
		case 't':
		case 'T': days[i] = 1; break;
		case 'w':
		case 'W': days[i] = 2; break;
		case 'r':
		case 'R': days[i] = 3; break;
		case 'f':
		case 'F': days[i] = 4; break;
		default: days[i] = -1; break;
		}
		//edited by Kim
		periods[i] = atoi(period[i].c_str()) - 1;
	}
}

//Setter methods
void Section::setSectionNum(string sectionNum) {
	this->sectionNum = sectionNum;
}
void Section::setDays(string day[]) {
	for (int i = 0; i < 10; i++) {
		//switch statement created by Kim
		switch (day[i][0]) { //check the first character of the string at index i of day array
		case 'm':
		case 'M': days[i] = 0; break;
		case 't':
		case 'T': days[i] = 1; break;
		case 'w':
		case 'W': days[i] = 2; break;
		case 'r':
		case 'R': days[i] = 3; break;
		case 'f':
		case 'F': days[i] = 4; break;
		default: days[i] = -1; break;
		}
	}
}
void Section::setPeriods(string period[]) {
	for (int i = 0; i < 10; i++) {
		//edited by Kim
		periods[i] = atoi(period[i].c_str()) - 1;
	}
}
void Section::setTimeAvbl(string timeAvbl) {
	this->timeAvbl = timeAvbl;
}

//Getter methods
string Section::getSectionNum() {
	return this->sectionNum;
}
int Section::getDays(int index) {
	return this->days[index];
}
string Section::getTimeAvbl() {
	return this->timeAvbl;
}
int Section::getPeriods(int index) {
	return this->periods[index];
}