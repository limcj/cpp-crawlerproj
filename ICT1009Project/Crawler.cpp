#include <stdio.h>
#include <iostream>
//include libcurl header file
#include <libcurl/oauthlib.h>
#include <libcurl/twitcurl.h>

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



    replyMsg = "";
    printf("\nGetting public timeline\n");
    if (twitterObj.timelinePublicGet())
    {
        twitterObj.getLastWebResponse(replyMsg);
        printf("\ntwitterClient:: twitCurl::timelinePublicGet web response:\n%s\n", replyMsg.c_str());
    }
    else
    {
        twitterObj.getLastCurlError(replyMsg);
        printf("\ntwitterClient:: twitCurl::timelinePublicGet error:\n%s\n", replyMsg.c_str());
    }
}