//
//  Section.h
//  MasterSchedule
//
//  Team #9 Semester Project COP3503
//  Created by Kimberly Price, Alexander Gonzalez, Andrew Chabab, and Jamal West
//  Documented by Kaji Rashad and Alberto Molina
//  Copyright © 2016. All rights reserved.

#ifndef Section_h
#define Section_h
#include <string>
#include <stdlib.h>

using namespace std;
/* Alexander Gonzalez
* Section objects and class implementation
*/

class Section {
private:
	//Member Variables
	string sectionNum;
	string timeAvbl;
	int days[10];
	int periods[10];

public:
	//Creates an empty section necessary for potential sections
	//that are not needed by the user
	Section();

	//Setter method used as constructor
	void set(string sectionNum, string timeAvbl, string day[], string period[]);

	//Setter methods
	void setSectionNum(string sectionNum);
	void setDays(string day[]);
	void setPeriods(string period[]);
	void setTimeAvbl(string timeAvbl);

	//Getter methods
	string getSectionNum();
	int getDays(int index);
	string getTimeAvbl();
	int getPeriods(int index);
};

#endif /* Section_h */
