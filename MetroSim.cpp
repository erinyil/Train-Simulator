/********************************************
* Comp 15 - Fall 2019
* Homework 3
* Erin Yilmaz
* 4 October 2019
* 
* MetroSim implementation
*********************************************/

#include <iostream>
#include <fstream>

#include "MetroSim.h"

using namespace std;

// Function: Parameterized Constructor
// Parameters: The name of the file containing the stations
// Returns: nothing
// Does: places the train at the first station going in the positive direction
// and reads in the stations from the input file and stores them in the vector
MetroSim::MetroSim(string filename) {
    train_location = 1;
    train_direction = 'p';
    ID_assign = 1;
    ifstream infile;
    infile.open(filename);
    if (! infile.is_open()) {
        cerr << "Your input file cannot be opened.\n";
        exit(1);
    }
    Station s;
    getline(infile, s.name);
    for (int i = 1; !infile.eof(); ++i) {
        s.num = i;
        station.push_back(s);
        getline(infile, s.name);
    }
    print_map();
}

// Function: add p
// Parameters: arrival and departure station numbers
// Returns: nothing
// Does: adds a passenger to the queue at a station
void MetroSim::add_p(int arrive, int end) {
	Passenger p;
	p.ID = ID_assign;
	p.start = arrive;
	p.destination = end;
	ID_assign++;
    station[arrive - 1].queue.push_back(p);
    print_map();
} 


// Function: Move Train
// Parameters: address to outfile
// Returns: void
// Does: calls the fncs that move the train and handles passengers
void MetroSim::move_train(ofstream &outfile) {
	board_passengers();
    update_location();
    unload_passengers(outfile);
    print_map();
}


// Function: Board Passengers
// Parameters: none
// Returns: void
// Does: boards the passengers at the station onto the train, emptying the
// line at the station
void MetroSim::board_passengers() {
    if (station.at(train_location - 1).queue.empty() == true) {
        return;
    }
    int line_length = station.at(train_location - 1).queue.size();
    for (int i = 0; i < line_length; ++i) {
    	train.push_back(station.at(train_location - 1).queue[i]);
    }
    station.at(train_location - 1).queue.clear();
} 

// Function: Unload Passengers
// Parameters: the outfile to print to
// Returns: void
// Does: unloads the passengers from the train and prints info about them
void MetroSim::unload_passengers(ofstream &outfile) { 
	for (unsigned int i = 0; i < train.size(); i++) {
		if (train[i].ID != -1 && train[i].destination == train_location) { 
		    outfile << "Passenger " << train[i].ID << " left train at station ";
		    outfile << station[train[i].destination - 1].name << endl;
            train[i].ID = -1;
		}
    }
}


// Function: Update Location
// Parameters: none
// Returns: void
// Does: moves the train to the next station
void MetroSim::update_location() {
    int num_stations = station.size();
	if (train_direction == 'p' && train_location < num_stations)
		train_location++;
    else if (train_direction == 'p' && train_location == num_stations) {
        train_direction = 'n';
        train_location--;
    }
    else if (train_direction == 'n' && train_location == 1) {
        train_direction = 'p';
        train_location++;
    }
    else if (train_direction == 'n' && train_location > 1)
    	train_location--;
}


// Function: Print map
// Parameters: none
// Returns: nothing
// Does: Prints the train, list of stations, and passengers at each station
void MetroSim::print_map() {
    cout << "Passengers on the train: ";
    print_passengers(train.size(), train);
    print_station(station.size());
}


// Function: Print Passengers
// Parameters: the number of passengers to be printed and the list from which
// to print them
// Returns: nothing
// Does: Prints the passengers in a list
void MetroSim::print_passengers(int size, vector<Passenger> list) {
	cout << "{";
	int j = 0;
	for (int i = size; i > 0; i--) {
		if (list[j].ID != -1) {
			cout << "[" << list[j].ID << ", ";
    	    cout << list[j].start << "->" << list[j].destination << "]";
		}
		j++;
    }
    cout << "}\n";
}

// Function: Print station
// Parameters: the number of stations to print
// Returns: nothing
// Does: prints the location of the train, the name of the station, and the
// line of passengers (if one exists) at that station
void MetroSim::print_station(int num_stations) {
    for (int i = 0; i < num_stations; i++) {
        if (train_location == i + 1)
            cout << "TRAIN: [" << i + 1 << "] ";
        else 
            cout << "       [" << i + 1 << "] ";
        cout << station[i].name << " ";
        int line_len = station[i].queue.size();
        print_passengers(line_len, station[i].queue);
    }
}
