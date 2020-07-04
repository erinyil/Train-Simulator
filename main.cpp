/********************************************
* Comp 15 - Fall 2019
* Homework 3
* Erin Yilmaz
* 4 October 2019
* 
* Main.cpp
*********************************************/
#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std; 

void cin_command(MetroSim myTrain, ofstream &outfile);
void commandsFile_func(MetroSim myTrain, ofstream &outfile, ifstream &infile);


// Function: Main
// Parameters: the stations file, output file, and sometimes commands file
// Returns: int 0 on success
// Does: Opens files, calls functions according to number of inputs
int main(int argc, char *argv[])
{
	if (argc > 4 || argc < 3) {
        cerr << "Usage: MetroSim stationsFile outputFile [commandsFile]\n";
        exit(1);
	}
	MetroSim myTrain = MetroSim(argv[1]);

	ofstream outfile;
    outfile.open(argv[2]);
	if (! outfile.is_open()) {
	    cerr << "Your output file cannot be opened.\n";
	    exit(1);
	}

	if (argc == 4) {
		ifstream commandsFile;
        commandsFile.open(argv[3]);
        if (! commandsFile.is_open()) {
        	cerr << "Your commands file cannot be opened.\n";
        	exit(1);
        }
		commandsFile_func(myTrain, outfile, commandsFile);
	}
	else
		cin_command(myTrain, outfile);
    outfile.close();
	return 0;
}

// Function: Cin command
// Parameters: the instance of the MetroSim class and address to the outputfile
// Returns: nothing
// Does: Gets and processes commands from cin, calling functions accordingly
void cin_command(MetroSim myTrain, ofstream &outfile) {
	ofstream new_outfile;
    string command1 = "";
    string command2 = "";
    int start, end;
    bool f_has_been_called = false;
    cout << "Command? ";
    cin >> command1;
    if (command1 == "m")
        cin >> command2;
    while (command2 != "f") {
        if (command1 == "p") {
            cin >> start >> end;
            myTrain.add_p(start, end); }
        else if (command1 == "m" && command2 == "m") {
        	if (!f_has_been_called)
        		myTrain.move_train(outfile);
        	else if (f_has_been_called)
        		myTrain.move_train(new_outfile); }
        else if (command1 == "f") {
            cin >> command2;
            outfile.close();
        	f_has_been_called = true;
            new_outfile.open(command2);
	        if (! new_outfile.is_open()) {
	            cerr << "Your output file cannot be opened.\n";
	            exit(1); } }
        cout << "Command? ";
        cin >> command1;
        if (command1 == "m")
            cin >> command2; }
    cout << "Thanks for playing MetroSim. Have a nice day!\n";
    new_outfile.close();
}


// Function: CommandsFile func
// Parameters: instance of the MetroSim class and the filename
// Returns: nothing
// Does: Gets and processes commands from the inputted
// commandsFile (infile) and calls functions accordingly
void commandsFile_func(MetroSim myTrain, ofstream &outfile, ifstream &infile){
	ofstream new_outfile;
    string command1 = "";
    string command2 = "";
    int start, end;
    bool f_has_been_called = false;
    cout << "Command? ";
    infile >> command1;
    if (command1 == "m")
        infile >> command2;
    while (command2 != "f") {
        if (command1 == "p") {
            infile >> start >> end;
            myTrain.add_p(start, end); }
        else if (command1 == "m" && command2 == "m") {
            if (!f_has_been_called)
                myTrain.move_train(outfile);
            else if (f_has_been_called)
                myTrain.move_train(new_outfile); }
        else if (command1 == "f") {
            infile >> command2;
            f_has_been_called = true;
            new_outfile.open(command2);
            if (! new_outfile.is_open()) {
                cerr << "Your output file cannot be opened.\n";
                exit(1); } }
        cout << "Command? ";
        infile >> command1;
        if (command1 == "m")
            infile >> command2; }
    cout << "Thanks for playing MetroSim. Have a nice day!\n";
    new_outfile.close();
}
