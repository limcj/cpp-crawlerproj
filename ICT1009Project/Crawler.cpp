#include <stdio.h>
#include <iostream>
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
        //printf("\ntwitterClient:: twitCurl::timelinePublicGet web response:\n%s\n", replyMsg.c_str());

        Json::Value jsonRecord;
        Json::Reader jsonReader;
        Json::Value jsonCreatedAt;

        bool b = jsonReader.parse(replyMsg, jsonRecord);


        jsonCreatedAt[0] = jsonRecord[0]["created_at"].asString();

        cout << jsonRecord << endl;
        cout << "Record 1" << endl;
        cout << jsonRecord[0]["created_at"] <<endl;
        cout << jsonRecord[0]["text"] << endl;
        cout << "Record 2" << endl;
        cout << jsonRecord[1]["created_at"]<<endl;
        cout << jsonRecord[1]["text"] << endl;
    }
    else
    {
        twitterObj.getLastCurlError(replyMsg);
        printf("\ntwitterClient:: twitCurl::timelinePublicGet error:\n%s\n", replyMsg.c_str());
    }
}