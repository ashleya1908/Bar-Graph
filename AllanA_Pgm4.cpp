// Ashley Allan, 2228 CS 2010 Section 1004, MOWeFri 11:30am-12:20pm

//Program 4: Bar Graph, File:AllanA_Pgm4, Due:10/19/2022

/*
Purpose: To produce a bar graph based on data values contained in various data files
Input: The user's choice of which data file will be read and interpreted into a graph
Processing: Opens file based on user choice, reads file, counts invalid values and correcly formats them, finds three max 
and three min values, adds all invalid values, changes color of bar based on type of invalid value, formats an x and y axis. 
Output: Bar graph with "X", colored bars for invalid values, x and y axis, three min values, three max values, and invalid values 

Reflection: This program was extremely difficult for me. It took me a while to figure out where to start, and there was a lot of incrementing
that I had to do in order to be successful. I ran into an abundance of problems while writing this program, but trial and error finally led me 
to the correct solution. I found out that there are indeed multiple ways to write the same solution, but some ways work better and are more convenient
with others. It is very stressful to read the instructions because this is a very large program and there are so many requirements that need to be met.
By doing it step by step and adding in little details as I went, I finally was able to come up with this solution.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

int main()
{
	int choice; //Variable for user input 
	
	int magicNum = 9999; //Declaration of sentinel number
	int fileContents; //Variable for file content
	int y_axis = 1; //Axis variables 
	int x_axis;
	
	int invalid; //Variables for invalid values
	int negCounter = 0;
	int maxLengthCounter = 0;

	int maxVal = 0; //Variables for max and min values 
	int minVal = 115;
	int maxVal_2 = 0;
	int maxVal_3 = 0;
	int minVal_2 = 115;
	int minVal_3 = 115;

	HANDLE hConsole; //For colors 
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int WHITE = 7;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ifstream inFS;
	
	do { //Erases console and prompts input again if the input is invalid 
		system("cls"); //Erases menu and re-outputs 
		cout << "Select file to process: " << '\n'
		    << "1. mixed.txt" << '\n'
			<< "2. valid.txt" << '\n'
			<< "3. three.txt" << '\n'
			<< "4. missing.txt" << '\n'
			<< '\n' << "Choice: " << '\n';
		cin >> choice;
	} while ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4)); //Conditions for invalid input 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	switch (choice) { //Cases for opening and processing files based on choice 
	case 1:
		cout << "Opening mixed.txt." << '\n' << '\n';
		inFS.open("mixed.txt");
		break;

	case 2:
		cout << "Opening valid.txt." << '\n' << '\n';
		inFS.open("valid.txt");
		break;

	case 3:
		cout << "Opening three.txt." << '\n' << '\n';
		inFS.open("three.txt");
		break;

	default: //Outputs error message for choice 4
		cout << "ERROR: Data file not found." << '\n';
		return 1;
		break;
	} 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inFS >> fileContents; //Reads file contents
		if (inFS.fail()) { //Makes sure file is successfully opened
			inFS.close();
		}
	while (fileContents != magicNum) { //Loop that reads the file until it reaches the magic number (9999)
		if (fileContents > maxVal) { //Finds max value
			maxVal_3 = maxVal_2;
			maxVal_2 = maxVal;
			maxVal = fileContents;
		}
		else if ((fileContents < maxVal) && (fileContents > maxVal_2)) { //Finds second max value
			maxVal_3 = maxVal_2;
			maxVal_2 = fileContents;
		}
		else if ((fileContents < maxVal_2) && (fileContents > maxVal_3)) { //Finds third max value
			maxVal_3 = fileContents;
		}
		if (fileContents < minVal) { //Finds min value
			minVal_3 = minVal_2;
			minVal_2 = minVal;
			minVal = fileContents;
		}
		else if ((fileContents > minVal) && (fileContents < minVal_2)) { //Finds second min value
			minVal_3 = maxVal_2;
			minVal_2 = fileContents;
		}
		else if ((fileContents > minVal_2) && (fileContents < minVal_3)) { //Finds third min value
			minVal_3 = fileContents;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (fileContents < 0) { //Takes absolute value of negative numbers 
			fileContents = abs(fileContents);
			SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE); //Changes background color 
			++negCounter; //Counts negatives as invalid
		}
		if (fileContents > 120) { //Parses values that are too large for the console window
			fileContents = 115;
			SetConsoleTextAttribute(hConsole, BACKGROUND_RED); //Changes background color
			++maxLengthCounter; //Counts these values as invalid 
		}
		if (y_axis < 10) { //Formats numbers and spaces on y-axis
			cout << y_axis << "  | ";
		}
		if (y_axis >= 10) { //Formats numbers and spaces on y-axis
			cout << y_axis << " | ";
		}
		for (int i = 0; i < fileContents; ++i) { //Outputs bars in the graph
			cout << "X";
		}
		cout << '\n';
		SetConsoleTextAttribute(hConsole, WHITE); //Sets background color of valid values 
		++y_axis;
		inFS >> fileContents;

	}
	inFS.close(); 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << setfill('-') << setw(120) << "" << '\n'; //Formatting for x-axis 
	cout << "     1        ";
	for (x_axis = 10; x_axis < 100; x_axis += 10) {
		cout << x_axis << "        ";
	}
	cout << '\n'; //Formatting for X axis 

	//Outputs Smallest 3 values:
	cout << '\n';
	cout << "SMALLEST" << '\n' << "--------" << '\n';
	cout << "The smallest value: " << minVal << '\n'
		<< "The 2nd smallest value: " << minVal_2 << '\n'
		<< "The 3rd smallest value: " << minVal_3 << '\n';
	//Outputs Largest 3 values:
	cout << '\n';
	cout << "LARGEST" << '\n' << "-------" << '\n';
	cout << "The largest value: " << maxVal << '\n'
		<< "The 2nd largest value: " << maxVal_2 << '\n'
		<< "The 3rd largest value: " << maxVal_3 << '\n';
	//Outputs invalid values:
	cout << '\n';
	invalid = negCounter + maxLengthCounter;
	cout << "INVALID" << '\n' << "-------" << '\n';
	cout << "There are " << invalid << " invalid values in the data." << '\n';

	return 0;
}

