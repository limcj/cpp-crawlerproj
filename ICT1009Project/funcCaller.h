#pragma once
//the caller that will be init'd when application is opened
//this crawler will ask for user input on what functions user wants to use


#include <iostream>


using namespace std;


class funcCaller {

	friend istream& operator>>(istream&, funcCaller&);

private:

	string input;


public:
	//gets what user has input
	string getInput();

	//prints the splash screen
	void print_splash();

	//prints the end screen
	void print_end();
};

