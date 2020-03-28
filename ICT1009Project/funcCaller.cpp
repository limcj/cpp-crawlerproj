#pragma once
//the caller that will be init'd when application is opened
//this crawler will ask for user input on what functions user wants to use


#include <iostream>
#include "funcCaller.h"
#include "twitterCrawler.h"
#include "app_State.h"


using namespace std;


funcCaller::funcCaller() {
	//an enum for state of the app so that exiting to access other functions is possible
	APP_STATE app_state = APP_STATE::DefaultState;
}


//prints when app is init'd
//general functions menu for main page
istream& operator>>(istream& in, funcCaller& fc) {
	std::cout << "\nWelcome to Group 4 crawler! \n";
	while (true) {
		std::cout << "\nPlease select which ID you wish to crawl :\n1) Crawl Twitter\n2) Crawl Telegram\n3) Show Analyses\n";
		std::cout << "To exit, please type \"exit\"\n";
		in >> fc.input;
		if (fc.input == "1") {
			twitterCrawler twitc;
			cin >> twitc;
			//cout << fc.input;
			return in;
		}
		if (fc.input == "2") {

			//TO CALL TELEGRAM CLASSES HERE
			/*teleCrawler telec;
			cin >> telec;*/
			//cout << fc.input;
			cout << "TELE CRAWL PLS\n";
			/*return in;*/
		}
		if (fc.input == "3") {

			//TO CALL ANALYSIS AND COMPARISON CLASSES HERE
			cout << "ANALYSIS PLS\n";
			/*return in;*/
		}
		if (fc.input == "exit" || fc.input == "ex"){
			break;
		}
		else {
			continue;
		}

	}
}

string funcCaller::getInput() {
	return input;
}



