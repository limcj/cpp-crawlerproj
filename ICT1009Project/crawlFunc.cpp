#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "crawlFunc.h"

//include libcurl header file
#include <libcurl/oauthlib.h>
#include <libcurl/twitcurl.h>
#include <json/json.h>


using namespace std;

crawlFunc::crawlFunc(string twID, int qty) {

    //init twitcurl obj with auth and consumer keys
    twitterObj.getOAuth().setConsumerKey(consumerKey);
    twitterObj.getOAuth().setConsumerSecret(consumerKeySecret);
    twitterObj.getOAuth().setOAuthTokenKey(myOAuthAccessTokenKey);
    twitterObj.getOAuth().setOAuthTokenSecret(myOAuthAccessTokenSecret);

    //set the twitterID and qty of data to crawl that were parsed by user
    twitterID = twID;
    number = qty;
}

void crawlFunc::doCrawl() {
    if (twitterObj.timelineUserGet(false, false, number, twitterID))
    {
        twitterObj.getLastWebResponse(replyMsg);

        //regex to remove ampersand
        regex reg("[^\\x00-\\x7F]+");

        //init json objects
        Json::Value jsonRecord;
        Json::Reader jsonReader;
        Json::Value jsonCreatedAt;

        //file
        std::ofstream myfile;

        //drill down to only required keys and corr. data
        bool b = jsonReader.parse(replyMsg, jsonRecord);

        //create and write to .csv file
        myfile.open("twitterdata.csv");

        //loop to write data for into .csv file for crawler
        for (int i = 0; i < number; i++) {

            //string the data lines that are to be recorded into the .csv file
            std::string created_at = jsonRecord[i]["created_at"].asString();
            std::string created_text = jsonRecord[i]["text"].asString();

            //remove commas in the inputs as they will need to be used for columning
            created_text.erase(std::remove(created_text.begin(), created_text.end(), ','), created_text.end());

            //lower case the string
            std::transform(created_text.begin(), created_text.end(), created_text.begin(),
                [](unsigned char c) {return std::tolower(c); });

            //replace special character ampersand with ""
            created_text = regex_replace(created_text, reg, "");


            //filter according to keywords
            if (((created_text.find("fault") != std::string::npos) || (created_text.find("maintenance") != std::string::npos)) && (created_text.find("update") == std::string::npos) && (created_text.find("cleared") == std::string::npos) && (created_text.find("bplrt") == std::string::npos) && (created_text.find("@") == std::string::npos)) {
                myfile << created_at << "," << created_text << "\n";
            }
        }
        cout << "Crawl success! Output is twitterdata.csv file in local folder.\n\n";
    }
    else
    {
        twitterObj.getLastCurlError(replyMsg);
        std::cout << "\ntwitterClient:: twitCurl::timelinePublicGet error:\n%s\n", replyMsg.c_str();
    }
}