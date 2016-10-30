//
//  main.cpp
//  MasterSchedule
//
//  Team #9 Semester Project COP3503
//  Created by Kimberly Price, Alexander Gonzalez, Andrew Chabab, and Jamal West
//  Documented by Kaji Rashad and Alberto Molina
//  Copyright © 2016. All rights reserved.

/***************************** System Definition *******************************/
// This program will make an optimal academic schedule based on user preferences,
// class needs, and available meeting times. The user can export a chosen schedule
// to a csv and/or txt file.

#include <iostream>
#include "Schedule.h"
#include "Section.h"
#include "Preferences.h"
#include "Course.h"

using namespace std;

//method created by Kimberly Price
static void viewMenu() {
	cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~ Menu ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;;
	cout << "\n(1) Export a schedule to csv file (planner view)" << endl;
	cout << "(2) Export a schedule to txt file (list view)" << endl;
	cout << "(3) Display three more schedules" << endl;
	cout << "(4) Exit" << endl;
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	/*cout << "Export to csv (planner view) or txt (list view)\n(1)csv (planner view)\n(2)txt (list view)\n(3)Exit\n\tChoice: "; // menu for exporting*/
}

//method created by Andrew Chabab
string idChecker() // method to check validate the UFID for the student
{
	string UFID = "";
	bool ufloop = true;
	cout << "Enter your UFID (no dashes): ";
	while (ufloop)
	{
		cin >> UFID;

		if (UFID.length() < 8 || UFID.length() > 8) // if UFID is less than or more than eight characters goes to input again
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid ID\nEnter again: ";
			continue;
		}
		for (int i = 0; i<8; i++) // if any character is not a number then it runs input again
		{
			if (UFID.at(i)<48 || UFID.at(i)>57)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid ID\nEnter again: ";
				ufloop = true;
				break;
			}
			else
				ufloop = false;
		}
		if (ufloop == false) // if all is good it sets bool to false and breaks out of loop
			break;
	}
	return UFID; //returns the UFID
}

int main(int argc, const char * argv[]) {

	/* Andrew Chabab
	* Personal information input and menu options
	*/

	string first_name = "", last_name = "", UFID = ""; // objects for personal information

	cout << "\n**************************************************************************" << endl;
	cout << "***~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~***" << endl;
	cout << "***~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~***" << endl;
	cout << "***~~~~~~~~~~~~~~~~~~ Welcome to the Schedule Optimizer ~~~~~~~~~~~~~~~***" << endl;
	cout << "***~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~***" << endl;
	cout << "***~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~***" << endl;
	cout << "**************************************************************************" << endl;
	cout << "\nEnter your first name: ";
	getline(cin, first_name);
	cout << "Enter your last name: ";
	getline(cin, last_name);
	UFID = idChecker();

	bool bad = true, badNest = true, badSecInput = true; // bools and menu choices for loops
	int choice = 0, choiceSec = 0;
	while (bad)
	{
		cout << "\nThis is your current personal information.\n\n"; // simple menu for editing personal info
		cout << "First name: " << first_name << "\n" << "Last name: " << last_name << "\n" << "UFID: " << UFID << "\n\n";
		cout << "Would you like to edit your information?\n\n";
		cout << "Yes(1) or No(0): ";
		cin >> choice;
		if (cin.fail()) // if input is not an int it breaks and runs again
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Not a number, try again. ";
			continue;
		}
		else if (choice != 0 && choice != 1) // if not a choice breaks and goes again changed || to && *Edited by Kim
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Not a valid choice, try again. ";
			continue;
		}
		else if (choice == 1)
		{
			cout << "What would you like to edit?\n";
			badNest = true;
			while (badNest)
			{
				badSecInput = true;
				cout << "\n(1)First name\n(2)Last name\n(3)UFID\n(4)Exit\nChoice: "; //choose what to edit or exit
				cin >> choiceSec;
				if (cin.fail()) // if not an int it breaks and goes again
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Not a number, try again. ";
					continue;
				}
				else if (choiceSec != 1 && choiceSec != 2 && choiceSec != 3 && choiceSec != 4) // if not a choice it breaks and goes again
				{
					cout << "Not a valid choice. ";
					continue;
				}
				else if (choiceSec == 1)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Enter your first name: "; getline(cin, first_name);
				}
				else if (choiceSec == 2)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Enter your last name: "; getline(cin, last_name);
				}
				else if (choiceSec == 3)
				{
					UFID = idChecker();
				}
				else
					badNest = false;
			}
		}
		else if (choice == 0)
			bad = false;
	} cout << endl; cout << endl;

	/****************************>>  End Personal Info Input  <<***********************(Andrew C.)*/

	Course course[5]; //updated according to number of courses
	cout << "Course Information" << endl;
	cout << "Please enter the courses of interest in order of priority. " << endl;
	Course::getCourseInfo(course);

	/* Kimberly Price
	* Algorithm for all possible schedules
	*/
	Schedule schedArray[243];
	int count = 0;

	//Each nested for loop represents a course, with up to 3 sections each
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			for (int k = 0; k<3; k++)
				for (int l = 0; l<3; l++)
					for (int m = 0; m<3; m++) {
						//Systematically adds different sections of each course (if there is not a conflict)
						schedArray[count].addClass(course[0], i);
						schedArray[count].addClass(course[1], j);
						schedArray[count].addClass(course[2], k);
						schedArray[count].addClass(course[3], l);
						schedArray[count].addClass(course[4], m);
						//schedArray[count].displaySched(); //for testing purposes
						count++;
					}
	/*set preferences for testing abilities
	Preferences p = *new Preferences(12,16,false,5,6,"");*/
	Preferences pref = *new Preferences();
	cout << "\nSchedule Preferences" << endl;
	pref.getPrefs();

	//Schedules will be sorted according to the number of preferences met
	Schedule::sortSchedules(pref, schedArray);

	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BEST SCHEDULES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	int i = 0;
	Schedule::print3Sched(schedArray, i);
	i += 3; //update index for schedule Array after printing 3

			/* Andrew Chabab
			* Export and Display Schedule options and menu
			*/

	int exportC = 0; bool displayC = true; int schedC = 0; bool schedChoice = true; //bools and objects for export menu
	viewMenu();

	while (displayC)
	{
		schedChoice = true; // schedChoice set to true every time loop runs to ensure
		cout << "\nChoice: ";
		cin >> exportC;
		if (cin.fail()) // if input is not an int it goes for input again and clears rain
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error, not a valid choice." << endl;
			viewMenu();
		}
		else if (exportC != 1 && exportC != 2 && exportC != 3 && exportC != 4) // if choice is not one of the prompted then it breaks
		{
			cin.clear();
			cout << "Error, not a valid choice." << endl;
			viewMenu();
		}
		else if (exportC == 1) // runs export for csv file
		{
			cout << "Which schedule would you like to export? ";
			while (schedChoice)
			{
				cin >> schedC;
				if (cin.fail()) // if input is not an int then it breaks and loops again
				{
					cin.clear();
					cin.ignore(1000, '\n'); // clears input and ignores next 1000 characters
					cout << "Not a valid schedule choice, please try again.\nWhich schedule would you like to export? ";
				}
				//changed && to || *Edited by Kim
				else if (schedC<0 || schedC>243) // if they choice anything besides 1 and 243 then it breaks and asks for input again
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Not a valid schedule choice, please try again.\nWhich schedule would you like to export? ";
				}
				else // if all checks out then it breaks loop and goes to next step
					schedChoice = false;
			}
			cout << "Exporting to CSV (planner view)." << endl;
			schedArray[schedC - 1].saveCSV(); // prints to csv file
			viewMenu();
		}
		else if (exportC == 2)
		{
			cout << "\nWhich schedule would you like to export? "; // same checks as csv export
			while (schedChoice)
			{
				cin >> schedC;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Not a valid schedule choice, please try again.\nWhich schedule would you like to export? ";
				}
				else if (schedC<0 || schedC>243) //changed && to || *Edited by Kim
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Not a valid schedule choice, please try again.\nWhich schedule would you like to export? ";
				}
				else
					schedChoice = false;
			}
			cout << "Exporting to TXT (list view)." << endl;
			schedArray[schedC - 1].saveTXT(first_name, last_name, UFID);
			viewMenu();
		}
		else if (exportC == 3) {
			Schedule::print3Sched(schedArray, i);
			i += 3; //update index for schedule Array after printing 3
			viewMenu();
		}
		else if (exportC == 4) // else if 3 is chosen then whole program exits
			displayC = false;
	}

	/****************************>>  End Export and Display options  <<***********************(Andrew C.)*/

	return 0;
}
