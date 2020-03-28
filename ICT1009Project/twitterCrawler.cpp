#include <stdio.h>
#include <iostream>
#include <istream>
#include <algorithm>
#include <cctype>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "twitterCrawler.h"
#include "crawlFunc.h"
#include "graph.h"
#include "app_State.h"
#include "funcCaller.h"


//include libcurl header file
#include <libcurl/oauthlib.h>
#include <libcurl/twitcurl.h>
#include <json/json.h>

#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))

using namespace std;

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
extern "C" void __imp__set_output_format(void) {};

//view the crawled data from the output .csv file
void twitterCrawler::viewCrawledData() {
	
	//open the file twitterdata.csv
	ifstream ip("twitterdata.csv");

	//if file doesnt exist prompt user to crawl first
	if (!ip.is_open()) std::cout << "ERROR: Please crawl data first" << '\n';

	//tweet var
	string tweets;

	while (ip.good()) {

		getline(ip, tweets, '\n');

		std::cout << tweets << "\n" << endl;

	}
	ip.close();
}

istream& operator>>(istream& in, twitterCrawler& tc) {
	while (true) {
		std::cout << "\nPlease select the ID for the function you want to run :\n1) Crawl SMRT Breakdowns\n2) View Crawled Data\n3) Graph: Faults and Maintenance Summary\n4) Graph: Categorised Faults\n5) Graph: Faults by Line\n";
		std::cout << "\nTo get back to Main Menu, please type \"b\"\n";
		std::cout << "To exit, please type \"exit\"\n";
		in >> tc.input;
		if (tc.input == "1") {
			int data_qty;

			//ask for number of twitter data to crawl #max is 100
			cout << "Please enter number of data you wish to crawl (max 200): \n";

			cin >> data_qty;
			cout << "\nCrawling in progress, this may take a few seconds...\n\n";

			//calls the CrawlFunc Class that will init a twitcurl object to crawl twitter with the parsed TwitterID
			crawlFunc twitCF("SMRT_Singapore", data_qty);
			twitCF.doCrawl();
		}
		if (tc.input == "2") {

			//call method to show crawled data
			tc.viewCrawledData();
			//return in;
		}
		if (tc.input == "3") {
			//init a graph that shows faults by line
			graph faultsByLine;
			faultsByLine.renderGraph();

		}
		if (tc.input == "4") {
			//init a graph that shows total faults according to category
			graphTFT catFaults;
			catFaults.renderGraph();
		}
		if (tc.input == "5") {
			//init a graph that shows total faults according to category
			graphFBL catLines;
			catLines.renderGraph();
		}
		if (tc.input == "exit" || tc.input == "ex") {
			return in;
			break;
		}
		if (tc.input == "b") {
			funcCaller fc;
			in >> fc;
		}
		else {
			continue;
		}

	}
}



