//
//  Course.h
//  MasterSchedule
//
//  Team #9 Semester Project COP3503
//  Created by Kimberly Price, Alexander Gonzalez, Andrew Chabab, and Jamal West
//  Documented by Kaji Rashad and Alberto Molina
//  Copyright © 2016. All rights reserved.


#ifndef Course_h
#define Course_h

/* Alexander Gonzalez
* Course objects and class implementation
*/

#include <stdio.h>
#include "Section.h"
#include <iostream>

class Course {
private:
	//Member Variables
	string courseName;
	string courseNum;
	Section section[10];
	int credits;
	int amountOfSect;

public:
	//Setter method used as constructor
	void set(string courseName, string courseNum, Section section[],
		int credits);

	//Setter methods for each variable
	void setCourseName(string courseName);
	void setCourseNum(string courseNum);
	void setSection(Section section[]);
	void setCredits(int credits);

	//Getter methods for each variable
	string getCourseName();
	string getCourseNum();
	Section getSection(int index);
	int getCredits();

	//static methods for implementation
	static void processTimeAvbl(string timeAvbl, string *days, string *periods, bool &wrongInput);
	static bool isAllDigit(string input);
	static int stoi(string input, bool &wrongInput);
	static void getCourseInfo(Course course[]);


};

#endif /* Course_h */
