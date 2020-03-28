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
	funcCaller();
	string getInput();
};

