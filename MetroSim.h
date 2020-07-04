/********************************************
* Comp 15 - Fall 2019
* Homework 3
* Erin Yilmaz
* 4 October 2019
* 
* MetroSim interface
*********************************************/
#ifndef _METROSIM_H_
#define _METROSIM_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Passenger
{   
	int ID;
	int start;
	int destination;
};

struct Station
{
	int num;
	string name;
    vector<Passenger> queue;
};


class MetroSim
{
public:
    MetroSim(string filename); //initializes private data members
    int located_at();  //returns the number of the station where train is

    //calls fncs that move train and handle passengers
    void move_train(ofstream &outfile); 

    void print_map(); //prints the map of the train with stations and passenger
    void add_p(int arrive, int end);  //adds a passenger to the queue at a stop


private:
    int train_location;      //holds the stop number where the train is located
    vector<Station> station; //holds the list of stations as station structs
    vector<Passenger> train; //holds the en route passenger list
    char train_direction; //holds p or n depending on direction of movement
    int ID_assign;          //tracks the last assigned ID number

    void print_passengers(int size, vector<Passenger> list); //prints passenger
    void print_station(int num_stations); //prints the stations
    void update_location(); //moves the train to the next station
    void board_passengers(); //loads the passengers from the station line
    void unload_passengers(ofstream &outfile); //unloads and prints the leavers
};

#endif

