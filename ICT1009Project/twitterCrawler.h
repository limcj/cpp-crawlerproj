#pragma once

//#include <iostream>

using namespace std;

class twitterCrawler {

    friend istream& operator>>(istream&, twitterCrawler&);

private:
    string input = "";

public:
    void viewCrawledData();
};
