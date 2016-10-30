//
//  Preferences.cpp
//  MasterSchedule
//
//  Team #9 Semester Project COP3503
//  Created by Kimberly Price, Alexander Gonzalez, Andrew Chabab, and Jamal West
//  Documented by Kaji Rashad and Alberto Molina
//  Copyright © 2016. All rights reserved.

#include <stdio.h>
#include <limits>
#include "Preferences.h"

/* Jamal West
* Preference objects and class implementation
*/

void Preferences::getPrefs() {

	bool repeat = true;
	string answer = "";
	bool confirmed = false;

	// Prompting user with questions for preferences

	cout << "What is the minimum number of credit hours you prefer for your Schedule? ";
	checkInput();
	setMinCredits(numHandler);
	cout << "What is the maximum number of credit hours you prefer for your Schedule? ";
	checkInput();
	setMaxCredits(numHandler);
	cout << "Would you like any days off? (Y)/(N) ";

	while (repeat) {

		cin >> answer;
		if (answer == "Y" || answer == "y") {
			boolHandler = true;
			repeat = false;
			setAnyDaysOff(boolHandler);
			cin.clear();
		}
		else if (answer == "N" || answer == "n") {
			boolHandler = false;
			repeat = false;
			setAnyDaysOff(boolHandler);
			cin.clear();
		}
		else if (answer != "Y" || answer != "N") {
			cin.clear();
			cout << "Please enter a 'Y' for YES or an 'N' for NO " << endl;
			repeat = true;
		}
		// if it makes it this far then the input was invalid so it clears the buffer and repeats
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	cout << "What is the maximum number of periods you prefer in a row? ";
	checkInput();
	setMaxPeriodsRow(numHandler);
	cout << "What is the maximum number of periods your prefer in a day? ";
	checkInput();
	setMaxPeriodsDay(numHandler);
	cout << endl;

	printPrefs();
	bool valid = true;

	while (!confirmed) {
		if (valid) {
			cout
				<< "Would you like to change anything in your Preferences? (Y)/(N) ";

			cin >> answer;
		}
		if (answer == "N" || answer == "n") {
			confirmed = true;
			return;

		}
		else if (answer == "Y" || answer == "y") {
			confirmed = false;

			cout << "Select which preference you would like to change: "
				<< endl;
			printPrefs();

			checkSwitch();

			switch (numHolder) {
			case 1:
				cout << "What is the minimum number of credit hours you prefer for your Schedule? ";
				checkInput();
				setMinCredits(numHandler);
				valid = true;
				break;
			case 2:
				cout << "What is the maximum number of credit hours you prefer for your Schedule? ";
				checkInput();
				setMaxCredits(numHandler);
				valid = true;
				break;
			case 3:
				cout << "Would you like any days off? (Y)/(N) ";
				repeat = true;

				while (repeat) {

					cin >> answer;
					if (answer == "Y" || answer == "y") {
						boolHandler = true;
						repeat = false;
						setAnyDaysOff(boolHandler);
						cin.clear();
					}
					else if (answer == "N" || answer == "n") {
						boolHandler = false;
						repeat = false;
						setAnyDaysOff(boolHandler);
						cin.clear();
					}
					else if (answer != "Y" || answer != "N") {
						cin.clear();

						cout
							<< "Please enter a 'Y' for YES or an 'N' for NO "
							<< endl;
						repeat = true;
					}
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				valid = true;
				break;
			case 4:
				cout << "What is the maximum number of periods you prefer in a row? ";
				checkInput();
				setMaxPeriodsRow(numHandler);
				valid = true;
				break;
			case 5:
				cout << "What is the maximum number of periods you prefer in a day? ";
				checkInput();
				setMaxPeriodsDay(numHandler);
				valid = true;
				break;
			default:
				cout << "Invalid input!!!" << endl;
				cout << "Please select from the options 1 - 5 " << endl;
				cout << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores any input after a space
				cin.clear(); // clears buffer
				valid = false;

				break;

			}

		}
		else if (answer != "Y" || answer != "N" || cin.fail()) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores any input after a space
			cin.clear(); // clears buffer
			cout << "Please enter a 'Y' for YES or an 'N' for NO " << endl;
			repeat = true;
		}
	}

}
// Function to print out preferences in numerical order.

void Preferences::printPrefs() {
	cout << "------- Schedule Preferences -------" << endl;
	cout << "(1) Minimum Credits: " << getMinCredits() << endl;
	cout << "(2) Maximum Credits: " << getMaxCredits() << endl;
	cout << "(3) Requested Days Off: ";
	if (getAnyDaysOff(boolHandler) == true) {
		cout << "YES" << endl;
	}
	else if (getAnyDaysOff(boolHandler) == false) {
		cout << "NO" << endl;
	}
	cout << "(4) Maximum Periods in a Row: " << getMaxPeriodsRow() << endl;
	cout << "(5) Maximum Periods in a Day: " << getMaxPeriodsDay() << endl;

}

//Function to decide if a string is a digit. Two #s separated by white space
//will not be taken as a digit

bool Preferences::isAllDigit(string input) {
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			return false;
		}
	}
	return true;
}

//Function to cast string to int and throw exception if wrong input
//It also confirms if the input is correct by referencing variable wrongInput

int Preferences::stoi(string input, bool &wrongInput) {
	int value = 0;

	try {
		if (!isAllDigit(input)) {
			throw 0;
		}
		value = atoi(input.c_str());
		wrongInput = false;
		return value;

	}
	catch (int x) {
		cout << "Error >>> Invalid input!!!" << endl;
	}
	return 0;
}


// Checks input to make sure its between 1 and 30 and non-negative

void Preferences::checkInput() {
	bool wrongInput = true;
	string numResult = "";
	while (wrongInput) {
		numHolder = -1;
		cin >> numHandler;
		getline(cin, numResult);
		numHandler += numResult;
		numHolder = stoi(numHandler, wrongInput);

		if (numHolder <= 0 || numHolder > 30) {
			wrongInput = true;
			cout << "Please enter a positive integer between 1 and 30" << endl;
		}
	}
}

// Checks input to make sure its between 1 and 5 and non-negative

void Preferences::checkSwitch() {
	bool wrongInput = true;
	string numResult = "";
	while (wrongInput) {
		numHolder = -1;
		cin >> numHandler;
		getline(cin, numResult);
		numHandler += numResult;
		numHolder = stoi(numHandler, wrongInput);

		if (numHolder <= 0 || numHolder > 30) {
			wrongInput = true;
			cout << "Please enter a positive integer between 1 and 5" << endl;
		}
	}
}


// Series of setter functions for the class

void Preferences::setMinCredits(string p) {
	minCredits = p;
}

void Preferences::setMaxCredits(string p) {
	maxCredits = p;

}

void Preferences::setAnyDaysOff(bool p) {
	anyDaysOff = p;
}

void Preferences::setMaxPeriodsRow(string p) {
	maxPeriodsRow = p;
}

void Preferences::setMaxPeriodsDay(string p) {
	maxPeriodsDay = p;
}


// Series of getter functions for the class

string Preferences::getMinCredits() {
	return minCredits;

}

string Preferences::getMaxCredits() {
	return maxCredits;
}

bool Preferences::getAnyDaysOff(bool anyDaysOff) {
	return anyDaysOff;

}
//Kim added the following method
bool Preferences::getAnyDaysOff() {
	return anyDaysOff;
}

string Preferences::getMaxPeriodsRow() {
	return maxPeriodsRow;
}

string Preferences::getMaxPeriodsDay() {
	return maxPeriodsDay;
}

/**********************>>  Preference class ends here  <<*******************(Jamal W.)*/
