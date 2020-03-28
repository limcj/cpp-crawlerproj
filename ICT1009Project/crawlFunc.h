#pragma once

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>

//include libcurl header file
#include <libcurl/oauthlib.h>
#include <libcurl/twitcurl.h>
#include <json/json.h>

using namespace std;


class crawlFunc {
private:
    string tmpStr;
    string replyMsg;
    char tmpBuf[1024]; //the temp buffer
    twitCurl twitterObj;
    string input = "";
    string twitterID = "";
    int number;

    //twitter API auth and consumer keys
    string consumerKey = "CqVBtblqAHgoXyrnAZ2drgUaW";
    string consumerKeySecret = "nI1tVcHaZ8FBUCpdVDHKCNS9mi0QvVfg6q79gQCyf6SPOT1Cbv";
    string myOAuthAccessTokenKey = "1223859521325424641-y4NGB8P7ZRyRhDxuoy8HBi8aOygFQf";
    string myOAuthAccessTokenSecret = "GIMa6JVmslYvMDbAuWQ2fZifauvbzYWvizjdwYg2mkHfu";

public:
    crawlFunc(string, int);
    void doCrawl();
};



