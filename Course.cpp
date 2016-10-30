//
//  Course.cpp
//  MasterSchedule
//
//  Team #9 Semester Project COP3503
//  Created by Kimberly Price, Alexander Gonzalez, Andrew Chabab, and Jamal West
//  Documented by Kaji Rashad and Alberto Molina
//  Copyright © 2016. All rights reserved.
//

#include "Course.h"

/* Alexander Gonzalez
* Course objects and class implementation
*/

/*
The Course class is used to create the objects of each class
the user inputs, it has a name, a number, a number of credits
and different sections that define the days and times of the
class (using the Section class).
*/

void Course::set(string courseName, string courseNum, Section section[],
	int credits) {
	this->courseName = courseName;
	this->courseNum = courseNum;
	this->credits = credits;
	for (int i = 0; i < 10; i++) {
		this->section[i] = section[i];
	}
}

//Setter methods for each variable
void Course::setCourseName(string courseName) {
	this->courseName = courseName;
}
void Course::setCourseNum(string courseNum) {
	this->courseNum = courseNum;
}
void Course::setSection(Section section[]) {
	for (int i = 0; i <= 10; i++) {
		this->section[i] = section[i];
	}
}
void Course::setCredits(int credits) {
	this->credits = credits;
}

//Getter methods for each variable
string Course::getCourseName() {
	return this->courseName;
}
string Course::getCourseNum() {
	return this->courseNum;
}
Section Course::getSection(int index) {
	return this->section[index];
}
int Course::getCredits() {
	return this->credits;
}

//Convert user input for time availability to two arrays of days
//and corresponding periods. Referencing wrongInput variable to
//determine if user should be asked again.
void Course::processTimeAvbl(string timeAvbl, string *days, string *periods, bool &wrongInput) {
	//Initialize days and periods arrays to nothing
	for (int i = 0; i < 10; i++) {
		periods[i] = "";
		days[i] = "";
	}

	//Delete white spaces and punctuation from input
	for (int n = 0; n < timeAvbl.length(); ++n) {//We need to increment before assigning since timeAvbl.length() changes
		if (ispunct(timeAvbl[n]) || isspace(timeAvbl[n]))
			timeAvbl.erase(n--, 1);//Erase value at n--.
	}

	//Variables
	int index = 0, digits = 0, letters = 0, temp = 0, daysIndex = 0, periodsIndex = 0;
	string subString = "", subString2 = "";
	bool invalid = false;
	bool correctDays[timeAvbl.length()];
	bool correctPeriods[timeAvbl.length()];
	//Initializing both arrays to false
	for (int k = 0; k < timeAvbl.length(); k++) {
		correctDays[k] = false;
		correctPeriods[k] = false;
	}

	//Check if the first character of input is a digit which is not valid
	if (isdigit(timeAvbl[0])) {
		invalid = true;
	}

	//Go through each character of string
	for (int i = 0; i < timeAvbl.length(); i++) {
		subString = timeAvbl.at(i);
		//Check if it's and it's one of the expected letters
		if (timeAvbl[i] == 'M' || timeAvbl[i] == 'T' || timeAvbl[i] == 'W' || timeAvbl[i] == 'R' || timeAvbl[i] == 'F'
			|| timeAvbl[i] == 'm' || timeAvbl[i] == 't' || timeAvbl[i] == 'w' || timeAvbl[i] == 'r' || timeAvbl[i] == 'f') {
			correctDays[daysIndex] = true; //Record that this character is correct
			daysIndex++; //Increment index of array to record if each character is correct
			days[index] = subString; //Add day to array
			letters++; //Add one to counter of days saved
		}
		//If it's a number
		else if (isdigit(timeAvbl[i])) {
			subString = timeAvbl[i];
			digits++; //Add one to counter of periods saved

					  //Check if two consecutive numbers
			if (i != 0)//Avoid error in case digit is at position zero
				subString2 = timeAvbl[i - 1];
			if (isdigit(timeAvbl[i - 1])) { //If previous character was a digit
				periods[index - 1] = subString2 + subString; //Form 2 digit single #
				temp = atoi(periods[index - 1].c_str()); //Convert to int
														 //Check that it's not greater than 14
				if (temp <= 14) {
					correctPeriods[periodsIndex] = true; //Record that number is correct
				}
				//Account for double counting when two numbers are merged into one
				digits--;
				index--;
			}

			else { //With no consecutive #s
				temp = atoi(subString.c_str()); //Convert to int
				if (temp == 0) {
					invalid = true;
					break;
				}
				periods[index] = subString; //Add number to array of periods
				correctPeriods[periodsIndex] = true; //Record that number is correct
			}
			index++; //Go to next column of both arrays
			periodsIndex++; //Increment index of array to record if each # is correct
		}
		else {
			invalid = true;
			break;
		}
	}

	//If timeAvbl.length() is 0 because all characters were deleted
	if (timeAvbl.length() == 0) {
		invalid = true;
	}

	if (!invalid) {
		//Check that there are no consecutive letters
		for (int i = 0; i < timeAvbl.length() - 1; i++) {
			if (!isdigit(timeAvbl[i]) && !isdigit(timeAvbl[i + 1])) {
				invalid = true; //Record that input is invalid
			}
		}

		//Check that all days entered are correct
		for (int i = 0; i < daysIndex; i++) {
			if (!correctDays[i]) {
				invalid = true; //Record that input is invalid
			}
		}

		//Check that all the numbers for periods are correct
		for (int i = 0; i < periodsIndex; i++) {
			if (!correctPeriods[i]) {
				invalid = true; //Record that input is invalid
			}
		}

		//There shouldn't be more than 10 periods per days
		if (digits > 10 || letters > 10) {
			invalid = true;
		}

		//If input hasn't been found invalid yet
		if (!invalid) {
			if (digits == letters) { //And there is a period for every day entered
				wrongInput = false; //Then the input is correct
			}
		}
	}
}

//Function to decide if a string is a digit. Two #s separated by white space
//will not be taken as a digit
bool Course::isAllDigit(string input) {
	for (int i = 0; i < input.length(); i++) {
		if (!isdigit(input[i])) {
			return false;
		}
	}
	return true;
}

//Function to cast string to int and throw exception if wrong input
//It also confirms if the input is correct by referencing variable wrongInput
int Course::stoi(string input, bool &wrongInput) {
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
		//cout << "Invalid input. Please try again" << endl;
	}
	return 0;
}

/*
The next function will get the course's info and store it an array of
Course objects. All there is left to do in main is: Course course[5]; and
getCourseInfo(course);. Calling this function and passing arrays of
Courses then we can get info from each object by using: course[0].getCourseName();
*/

//Function to get course info and store it in array of Course objects
void Course::getCourseInfo(Course course[]) {
	//Variables
	string courseName = "", courseNum = "", sect = "", time = "", line = "", in = "", timeCopy = "";
	int numberOfSections = 0, numberOfCourses = 0, credits = 0, choice = 0;
	bool wrongInput = true, before = true;
	bool confirmation = false;
	Section section[10];
	string sections[10];
	string days[10];
	string periods[10];
	string timeAvbl[10];

	//Get number of courses to be added from the user
	while (wrongInput) { //Validate input
		cout << "How many courses would you like to add?" << endl;
		cin >> in;
		getline(cin, line);
		in += line;
		//Convert string in to int
		numberOfCourses = stoi(in, wrongInput);
		if (numberOfCourses > 5) { //Limit # of courses to 5
			wrongInput = true;
			cout << "You can not add more than 5 courses. Please try again. " << endl;
		}
		if (numberOfCourses <= 0) { //# can't be negative
			wrongInput = true;
			cout << "Do you want to add a schedule or not? Please enter a positive number." << endl;
		}
	}

	//Ask the same info for every course to be added
	for (int i = 0; i < numberOfCourses; i++) {
		confirmation = false; //In case the user wants to edit info
		while (!confirmation) { //While users wants to edit
			cout << "Enter course name: ";
			cin >> courseName;
			getline(cin, line);
			courseName += line;
			cout << "\nEnter course number: ";
			cin >> courseNum;
			getline(cin, line);
			courseNum += line;

			//Get # of credits as int with validation
			wrongInput = true;
			while (wrongInput) {
				cout << "\nEnter number of credits: ";
				cin >> in;
				getline(cin, line);
				in += line;
				credits = stoi(in, wrongInput);
				if (credits > 10) {
					wrongInput = true;
					cout << "Courses can have a maximum of 10 credits." << endl;
				}
				if (credits <= 0) { //
					wrongInput = true;
					cout << "Wrong input. Please try again." << endl;
				}
			}

			//Get # of sections as int with validation
			wrongInput = true;
			while (wrongInput) {
				cout << "\nHow many sections of " << courseName << " would you like to add? ";
				cin >> in;
				getline(cin, line);
				in += line;
				numberOfSections = stoi(in, wrongInput);
				if (numberOfSections > 3) { //Limit # of sections to 3
					wrongInput = true;
					cout << "You can not add more than 3 sections. Please try again. " << endl;
				}
				if (numberOfSections <= 0) {
					wrongInput = true;
					cout << "Do you want to add a schedule or not? Please enter a positive number." << endl;
				}
			}

			//Ask the same info for every section to be added
			for (int j = 0; j < numberOfSections; j++) {
				cout << "\nEnter section number: ";
				cin >> sect;
				getline(cin, line);
				sect += line;
				sections[j] = sect; //Save section to array

									//Get time availability of each section with validation
				cout << "\nEnter class availability in the following form: "
					<< "\nM,T,W,R or F for Monday,Tuesday,...,Friday respectively"
					<< "\nfollowed by the period number. Separate each period with commas "
					<< "\nin the following manner T6,R6,R7: ";
				wrongInput = true;
				before = false;
				while (wrongInput) {
					if (before) {
						cout << "Enter class availability: ";
					}
					before = true;
					cin >> time;
					getline(cin, line);
					time += line;
					timeAvbl[j] = time; //Add to array with time availabilities of a course
					timeCopy = time;
					//Call function to convert time availability and assign values to arrays of days & periods
					processTimeAvbl(time, days, periods, wrongInput);
					if (wrongInput) {
						cout << "Invalid input. Please try again." << endl;
					}
				}

				//Creating object for section and adding it to array of Sections
				section[j].set(sect, timeCopy, days, periods);
			}
			for (int j = numberOfSections; j < 10; j++) {
				//take care of the sections not being used by creating dummy section
				section[j] = *new Section();
			}

			//Creating object for course and adding it to array of Courses
			course[i].set(courseName, courseNum, section, credits);

			//Confirm info of current course being entered
			cout << "" << endl;
			//Printing out stored info for the course
			cout << "Information for course " << course[i].getCourseName() << endl;
			cout << "Course number: " << course[i].getCourseNum() << endl;
			cout << "Credits: " << course[i].getCredits() << endl;

			//Going through every section
			for (int j = 0; j < numberOfSections; j++) {
				//Print time availability enter for this section
				cout << "    - Section " << course[i].getSection(j).getSectionNum()
					<< " at times: " << timeAvbl[j] << endl;
			}
			cout << "" << endl;

			//Ask user if they want to edit the info entered for this course
			wrongInput = true;
			while (wrongInput) { //Validating user's input is an integer
				cout << "Enter 1 to continue or 2 to edit this information: ";
				cin >> in;
				getline(cin, line);
				in += line;
				cout << "" << endl;
				choice = stoi(in, wrongInput);
				if (choice == 1) {
					//Information is correct and the program will continue
					confirmation = true;
				}
				else if (choice == 2) {
					//Information needs to be edited
					confirmation = false;
					cout << "Re-enter the information for the current course." << endl;
				}
				else { //User entered none of the choices given
					cout << "Invalid input. Please try again." << endl;
					cout << "" << endl;
					wrongInput = true;
				}
			}

		}
	}
	/********************************Testing code ****************************************************
	//Code to test course class
	//this how you will get to any of the variables
	cout << "\nTesting" << endl;
	for(int i = 0; i < numberOfCourses; i++){
	cout << "Course " << i+1 << " name: " << course[i].getCourseName() << endl;
	cout << "Course " << i+1 << " number: " << course[i].getCourseNum() << endl;
	cout << "Course " << i+1 << " credits: " << course[i].getCredits() << endl;
	for(int j = 0; j < numberOfSections; j++){
	cout << "Section " << i+1 << " number: " << course[i].getSection(j).getSectionNum() << endl;
	cout << "Times available: " << course[i].getSection(j).getTimeAvbl() << endl;
	cout << "Periods list:";
	for(int n = 0; n < 10; n++){
	cout << " " << course[i].getSection(j).getPeriods(n);
	}
	cout << "\nDays list:";
	for(int p = 0; p < 10; p++){
	cout << " " << course[i].getSection(j).getDays(p);
	}
	cout << "" << endl;
	}
	cout << "" << endl;
	}
	**************************End of testing code**************************************************/
}