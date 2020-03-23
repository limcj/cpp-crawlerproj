#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <regex>

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

int main() {
    string tmpStr;
    string replyMsg;
    char tmpBuf[1024];
    twitCurl twitterObj;
    

    string consumerKey = "CqVBtblqAHgoXyrnAZ2drgUaW";
    string consumerKeySecret = "nI1tVcHaZ8FBUCpdVDHKCNS9mi0QvVfg6q79gQCyf6SPOT1Cbv";
    string myOAuthAccessTokenKey = "1223859521325424641-y4NGB8P7ZRyRhDxuoy8HBi8aOygFQf";
    string myOAuthAccessTokenSecret = "GIMa6JVmslYvMDbAuWQ2fZifauvbzYWvizjdwYg2mkHfu";

    twitterObj.getOAuth().setConsumerKey(consumerKey);
    twitterObj.getOAuth().setConsumerSecret(consumerKeySecret);
    twitterObj.getOAuth().setOAuthTokenKey(myOAuthAccessTokenKey);
    twitterObj.getOAuth().setOAuthTokenSecret(myOAuthAccessTokenSecret);

    string input = "";
    int number;

    cout << "Welcome to Twitter crawler!\nPlease key in the TwitterID you wish to crawl from: \n";
    getline(cin, input);

    cout << "Please enter number of data you wish to crawl : \n";
    cin >> number;

    replyMsg = "";
    printf("\nCrawling in progress, please wait...\n");
    if (twitterObj.timelineUserGet(false, false, number, input))
    {
        twitterObj.getLastWebResponse(replyMsg);

        regex reg("[^\\x00-\\x7F]+");

        Json::Value jsonRecord;
        Json::Reader jsonReader;
        Json::Value jsonCreatedAt;
        
        std::ofstream myfile;

        bool b = jsonReader.parse(replyMsg, jsonRecord);
        myfile.open("example.csv");

        for (int i = 0; i < number; i++) {

            //string the data lines that are to be recorded into the .csv file
            std::string created_at = jsonRecord[i]["created_at"].asString();
            std::string created_text = jsonRecord[i]["text"].asString();

            //remove commas in the inputs as they will need to be used for columning
            created_at.erase(std::remove(created_at.begin(), created_at.end(), ','), created_at.end());
            created_text.erase(std::remove(created_text.begin(), created_text.end(), ','), created_text.end());

            //lower case the string
            transform(created_text.begin(), created_text.end(), created_text.begin(),
                [](unsigned char c) {return std::tolower(c); });

            //replace special character ampersand with ""
            created_text = regex_replace(created_text, reg, "");


            if (((created_text.find("fault") != std::string::npos) || (created_text.find("Fault") != std::string::npos) || (created_text.find("maintenance") != std::string::npos) || (created_text.find("Maintenance") != std::string::npos)) && ((created_text.find("update") == std::string::npos) && (created_text.find("cleared") == std::string::npos) && (created_text.find("bplrt") == std::string::npos) && (created_text.find("@") == std::string::npos))){
                myfile << created_at << "," << created_text << "\n";
            }
        }
      
        myfile.close();

        /*cout << jsonRecord << endl;
        cout << "Record 1" << endl;
        cout << jsonRecord[0]["created_at"] <<endl;
        cout << jsonRecord[0]["text"] << endl;
        cout << "Record 2" << endl;
        cout << jsonRecord[1]["created_at"]<<endl;
        cout << jsonRecord[1]["text"] << endl;*/
    }
    else
    {
        twitterObj.getLastCurlError(replyMsg);
        printf("\ntwitterClient:: twitCurl::timelinePublicGet error:\n%s\n", replyMsg.c_str());
    }
}