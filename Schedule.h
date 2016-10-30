//
//  Schedule.h
//  MasterSchedule
//
//  Team #9 Semester Project COP3503
//  Created by Kimberly Price, Alexander Gonzalez, Andrew Chabab, and Jamal West
//  Documented by Kaji Rashad and Alberto Molina
//  Copyright © 2016. All rights reserved.

#ifndef Schedule_h
#define Schedule_h
#include <iomanip>
#include <fstream>
#include "Course.h"
#include "Preferences.h"

using namespace std;
/* Kimberly Price
* Schedule objects and class implementation
*/

//all methods and data members of Schedule class authored by Kimberly Price excluding
//those used for exporting files (saveCSV(), saveTXT())

class Schedule {
private:
	string classSched[14][5]; //matrix of course names in corresponding periods for when they meet
	bool isOccupied[14][5]; //matrix indicating which periods are already taken
	string incl[5]; //Names of courses included in the schedule
	string notIncl[5];  //Names of courses not included in the schedule
	Course courseIncl[5]; //Course objects included in the schedule
	Section sectionIncl[5]; //Corresponding section objects included in the schedule
	int numCredits = 0;     //number of total credits the schedule has
	int numCourses = 0;     //number of courses the schedule has successfully added
	int attemptCourses = 0; //number of courses the schedule has attempted to add
	bool dayOff = false; //will be updated appropriately after calling maxPeriodsDay method
	int numPref; //number of preferences met by the schedule

public:
	Schedule();
	void addClass(Course course, int section);
	void displaySched();

	int getNumCredits();
	int maxPeriodsRow();
	int maxPeriodsDay();

	//dayOff is only accurate after maxPeriodsDay() method is called
	bool isDayOff();

	int numPrefMet(Preferences pref);

	//returns the number of courses in the schedule
	int getNumCourses();

	//returns the array of course objects represented in the schedule
	Course * getCourses();

	//returns the specific section objects of the course objects represented in the schedule
	Section * getSections();

	//checks whether a schedule includes all the courses input by the user
	bool completeSched();

	/* Andrew Chabab
	* all exporting methods saveCSV() and saveTXT()
	*/
	void saveCSV();

	void saveTXT(string first, string last, string id);

	/* Sort the schedules in order of number of preferences met, so that the schedules with the
	most preferences met are in the beginning of the array and the ones that have the least
	preferences met are in the end of the array */
	void static sortSchedules(Preferences pref, Schedule *array);

	//Future work: could go through and delete duplicate schedules
	//Displays 3 schedules at a time
	void static print3Sched(Schedule *array, int index);

};


#endif /* Schedule_h */

