#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

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

        Json::Value jsonRecord;
        Json::Reader jsonReader;
        Json::Value jsonCreatedAt;

        std::ofstream myfile;

        bool b = jsonReader.parse(replyMsg, jsonRecord);
        myfile.open("example.csv");

        for (int i = 0; i < number; i++) {

            std::string created_as = jsonRecord[i]["created_at"].asString();
            std::string created_text = jsonRecord[i]["text"].asString();

            created_as.erase(std::remove(created_as.begin(), created_as.end(), ','), created_as.end());

            created_text.erase(std::remove(created_text.begin(), created_text.end(), ','), created_text.end());

            if ((created_text.find("fault") != std::string::npos) || (created_text.find("maintenance") != std::string::npos)) {
                myfile << created_as << "," << created_text << "\n";
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