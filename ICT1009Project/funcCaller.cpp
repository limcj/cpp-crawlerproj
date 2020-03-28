#pragma once
//the caller that will be init'd when application is opened
//this crawler will ask for user input on what functions user wants to use


#include <iostream>
#include "funcCaller.h"
#include "twitterCrawler.h"


using namespace std;


//prints when app is init'd
//general functions menu for main page
istream& operator>>(istream& in, funcCaller& fc) {
	std::cout << "Welcome to Group 4 crawler! \n";
	while (true) {
		std::cout << "\nPlease select which ID you wish to crawl :\n1) Crawl Twitter\n2) Crawl Telegram\n";
		in >> fc.input;
		if (fc.input == "1") {
			twitterCrawler twitc;
			cin >> twitc;
			//cout << fc.input;
			return in;
		}
		else if (fc.input == "2") {
			/*teleCrawler telec;
			cin >> telec;*/
			//cout << fc.input;
			return in;
		}
		else {
			continue;
		}

	}
}

string funcCaller::getInput() {
	return input;
}



