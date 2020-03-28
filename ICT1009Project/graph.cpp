#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "graph.h"

//include libcurl header file
#include <libcurl/oauthlib.h>
#include <libcurl/twitcurl.h>
#include <json/json.h>

#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))

using namespace std;


//inits the parent graph class that will contain 2 int counts for "maint." and "fault"
graph::graph() {

    //get and open the twitter crawled data file to read
    ifstream ip("twitterdata.csv");

    if (!ip.is_open()) std::cout << "ERROR: Please crawl data first" << '\n';

    //reference for each line of tweet
    string tweets;

    while (ip.good()) {

        getline(ip, tweets, '\n');

        //count the no of fault and maintenance instances
        if (tweets.find("fault") != std::string::npos) {
            fault++;
        }
        if (tweets.find("maintenance") != std::string::npos) {
            maintenance++;
        }
    }
}

void graph::renderGraph() {

    //data that will be rendered
    vector<int> vector1 = { fault, maintenance };

    //x axis labels
    string graph = "      Fault Maint. ";


    auto max0 = vector1.size() * 6;
    for (int i = 0; i < max0; i += 2) {
        vector1.insert(vector1.begin() + i, vector1.at(i));
        i += 2;
        vector1.insert(vector1.begin() + i, 2, 0);
        i += 2;
        vector1.insert(vector1.begin() + i, 2, 0);
    }

    vector1.insert(vector1.begin(), 2, 0);

    int max1 = *max_element(vector1.begin(), vector1.end());
    int max2 = *max_element(vector1.begin(), vector1.end());

    for (int i = 0; i < max1; i++) {
        cout << right << setw(5) << (max1 * 1) - i * 1;
        for (int j = 0; j < vector1.size(); j++) {
            if (vector1.at(j) >= max2) {
                cout << '*';
            }
            else {
                cout << ' ';
            }
        }
        max2--;
        cout << endl;
    }
    //print the graph
    cout << graph << endl;
}

graphTFT::graphTFT() {

    //get and open the twitter crawled data file to read
    ifstream ip("twitterdata.csv");

    if (!ip.is_open()) std::cout << "ERROR: Please crawl data first" << '\n';

    //reference for each line of tweet
    string tweets;

    while (ip.good()) {

        getline(ip, tweets, '\n');

        //count the no of fault and maintenance instances
        if (tweets.find("track") != std::string::npos) {
            track++;
        }

        if (tweets.find("power") != std::string::npos) {
            power++;
        }

        if (tweets.find("door") != std::string::npos) {
            door++;
        }

        if ((tweets.find("train fault") != std::string::npos) || (tweets.find("signalling") != std::string::npos)) {
            train++;
        }

        if (tweets.find("signal") != std::string::npos) {
            signal++;
        }
    }
}

void graphTFT::renderGraph() {

    //data that will be rendered
    vector<int> vector1 = { fault, maintenance, track, power, door, train, signal };

    //x axis labels
    string graph = "     Fault Maint. Track Power Door Train Signal";
    auto max0 = vector1.size() * 6;
    for (int i = 0; i < max0; i += 2) {
        vector1.insert(vector1.begin() + i, vector1.at(i));
        i += 2;
        vector1.insert(vector1.begin() + i, 2, 0);
        i += 2;
        vector1.insert(vector1.begin() + i, 2, 0);
    }

    vector1.insert(vector1.begin(), 2, 0);

    int max1 = *max_element(vector1.begin(), vector1.end());
    int max2 = *max_element(vector1.begin(), vector1.end());
    for (int i = 0; i < max1; i++) {
        cout << right << setw(5) << (max1 * 1) - i * 1;
        for (int j = 0; j < vector1.size(); j++) {
            if (vector1.at(j) >= max2) {
                cout << '*';
            }
            else {
                cout << ' ';
            }
        }
        max2--;
        cout << endl;
    }

    cout << graph << endl;
}


graphFBL::graphFBL() {
    //get and open the twitter crawled data file to read
    ifstream ip("twitterdata.csv");

    if (!ip.is_open()) std::cout << "ERROR: Please crawl data first" << '\n';

    //reference for each line of tweet
    string tweets;

    while (ip.good()) {

        getline(ip, tweets, '\n');

        //count the no of fault and maintenance instances
        if (tweets.find("nsl") != std::string::npos) {
            nsl++;
        }

        if (tweets.find("nel") != std::string::npos) {
            nel++;
        }

        if (tweets.find("ewl") != std::string::npos) {
            ewl++;
        }

        if (tweets.find("ccl") != std::string::npos) {
            ccl++;
        }
    }
}


void graphFBL::renderGraph() {

    //data that will be rendered
    vector<int> vector1 = { fault, maintenance, nsl, nel, ewl, ccl };

    //x axis labels
    string graph = "     Fault Maint.  NSL   NEL   EWL   CCL";
    auto max0 = vector1.size() * 6;
    for (int i = 0; i < max0; i += 2) {
        vector1.insert(vector1.begin() + i, vector1.at(i));
        i += 2;
        vector1.insert(vector1.begin() + i, 2, 0);
        i += 2;
        vector1.insert(vector1.begin() + i, 2, 0);
    }

    vector1.insert(vector1.begin(), 2, 0);

    int max1 = *max_element(vector1.begin(), vector1.end());
    int max2 = *max_element(vector1.begin(), vector1.end());
    for (int i = 0; i < max1; i++) {
        cout << right << setw(5) << (max1 * 1) - i * 1;
        for (int j = 0; j < vector1.size(); j++) {
            if (vector1.at(j) >= max2) {
                cout << '*';
            }
            else {
                cout << ' ';
            }
        }
        max2--;
        cout << endl;
    }
    cout << graph << endl;
}