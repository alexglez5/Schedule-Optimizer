//
//  Preferences.h
//  MasterSchedule
//
//  Team #9 Semester Project COP3503
//  Created by Kimberly Price, Alexander Gonzalez, Andrew Chabab, and Jamal West
//  Documented by Kaji Rashad and Alberto Molina
//  Copyright © 2016. All rights reserved.

#ifndef Preferences_h
#define Preferences_h
#include <string>
#include <iostream>

using namespace std;

/* Jamal West
* Preference objects and class implementation
*/

class Preferences {

private:
	int numHolder;
	string minCredits;
	string maxCredits;
	bool anyDaysOff;
	string maxPeriodsRow;
	string maxPeriodsDay;
	string numHandler;
	bool boolHandler;
	//string unwantedPeriod; //may be used in future updates

public:

	void getPrefs();

	// Function to print out preferences in numerical order.
	void printPrefs();

	//Function to decide if a string is a digit. Two #s separated by white space
	//will not be taken as a digit
	bool isAllDigit(string input);

	//Function to cast string to int and throw exception if wrong input
	//It also confirms if the input is correct by referencing variable wrongInput
	int stoi(string input, bool &wrongInput);


	// Checks input to make sure its between 1 and 30 and non-negative
	void checkInput();

	// Checks input to make sure its between 1 and 5 and non-negative
	void checkSwitch();


	// Series of setter functions for the class
	void setMinCredits(string p);
	void setMaxCredits(string p);
	void setAnyDaysOff(bool p);
	void setMaxPeriodsRow(string p);
	void setMaxPeriodsDay(string p);

	// Series of getter functions for the class
	string getMinCredits();
	string getMaxCredits();
	static bool getAnyDaysOff(bool anyDaysOff);
	//Kim added the following method
	bool getAnyDaysOff();
	string getMaxPeriodsRow();
	string getMaxPeriodsDay();

};
/**********************>>  Preference class ends here  <<*******************(Jamal W.)*/

#endif /* Preferences_h */
