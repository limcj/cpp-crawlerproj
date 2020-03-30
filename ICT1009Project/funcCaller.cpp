#pragma once
//the caller that will be init'd when application is opened
//this crawler will ask for user input on what functions user wants to use


#include <iostream>
#include <conio.h>
#include "funcCaller.h"
#include "twitterCrawler.h"
#include "TelegramCrawler.h"


using namespace std;


//prints when app is init'd
//general functions menu for main page
istream& operator>>(istream& in, funcCaller& fc) {
	fc.print_splash();
		std::cout << "\nWelcome to Group 4 crawler! \n";
		while (true) {
			std::cout << "\n******************MAIN MENU******************";
			std::cout << "\nPlease select which ID you wish to crawl :\n1) Crawl Twitter\n2) Crawl Telegram\n3) Show Analyses\n";
			std::cout << "To exit, please type \"exit\"\n";
			in >> fc.input;
			if (fc.input == "1") {
				twitterCrawler twitc;
				cin >> twitc;
				//cout << fc.input;
			}
			if (fc.input == "2") {

				//TO CALL TELEGRAM CLASSES HERE
				Telegramcrawler telec;
				telec.telecrawler();
				//cout << fc.input;
				//cout << "TELE CRAWL PLS\n";
				//The print will be done by TelegramCrawler.cpp
			}
			if (fc.input == "3") {

				//TO CALL ANALYSIS AND COMPARISON CLASSES HERE
				cout << "ANALYSIS PLS\n";
				/*return in;*/
			}
			if (fc.input == "exit" || fc.input == "ex") {
				fc.print_end();
				break;
			}
			else {
				continue;
			}

		}
	return in;
}

void funcCaller::print_splash() {
	char splash[14][50] = {
		{"  _____ _____ _______ __  ___   ___   ___  "},
		{" |_   _/ ____|__   __/_ |/ _ \\ / _ \\ /   \\ "},
		{"   | || |       | |   | | | | | | | | (_) |"},
		{"   | || |       | |   | | | | | | | |\\__, |"},
		{"  _| || |____   | |   | | |_| | |_| |  / / "},
		{" |_____\\_____|  |_|   |_|\\___/ \\___/  /_/  "},
		{"   _____                         _  _      "},
		{"  / ____|                       | || |     "},
		{" | |  __ _ __ ___  _   _ _ __   | || |_    "},
		{" | | |_ | '__/ _ \\| | | | '_ \\  |__   _|   "},
		{" | |__| | | | (_) | |_| | |_) |    | |     "},
		{"  \\_____|_|  \\___/ \\__,_| .__/     |_|     "},
		{"                        | |                "},
		{"                        |_|                "},
	};

	cout << "\n\n\n";
	for (int i = 0; i < 14; ++i) {
		cout << "\n" << "\t\t\t\t    " << splash[i];
	}
	cout << "\n\n\n";
	cout << "\t\t\t\t\tpress any button to proceed to app";
	getch();
	system("CLS");
}

void funcCaller::print_end() {
	char end[][47] = {
	{"   _____                 _ _                _ "},
	{"  / ____|               | | |              | |"},
	{" | |  __  ___   ___   __| | |__  _   _  ___| |"},
	{" | | |_ |/ _ \\ / _ \\ / _` | '_ \\| | | |/ _ \\ |"},
	{" | |__| | (_) | (_) | (_| | |_) | |_| |  __/_|"},
	{"  \\_____|\\___/ \\___/ \\__,_|_.__/ \\__, |\\___(_)"},
	{"                                  __/ |       "},
	{"                                 |___/        "},
	};

	system("CLS");
	cout << "\n\n\n";
	for (int i = 0; i < 8; ++i) {
		cout << "\n" << "\t\t\t\t    " << end[i];
	}
	cout << "\n\n\n";
	getch();

}

string funcCaller::getInput() {
	return input;
}



