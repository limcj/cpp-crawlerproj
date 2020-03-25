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

    string twitterID = "";
    int number;
    int fault = 0;
    int maintenance = 0;
    int track = 0;
    int power = 0;
    int door = 0;
    int signal = 0;
    int train = 0;

    std::cout << "Welcome to Group 4 crawler! \n";
    while (true) {

        std::cout << "\nPlease select which ID you wish to crawl :\n1) Twitter SMRT Breakdowns\n2) Twitter Traffic Acccidents\n3) View Twitter SMRT Breakdown\n4) View Twitter Traffic Accidents\n5) View Chart\n";
        std::cin >> twitterID;

        if ((twitterID == "1") || (twitterID == "2")) {
            if (twitterID == "1") {
                twitterID = "SMRT_Singapore";
            }
            if (twitterID == "2") {
                twitterID = "LTAtrafficnews";
            }
            std::cout << "Please enter number of data you wish to crawl : \n";
            std::cin >> number;

            std::cout << "\nCrawling in progress, this may take a few seconds...\n\n";
            replyMsg = "";
            
            if (twitterObj.timelineUserGet(false, false, number, twitterID))
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
                    created_text.erase(std::remove(created_text.begin(), created_text.end(), ','), created_text.end());

                    //lower case the string
                    std::transform(created_text.begin(), created_text.end(), created_text.begin(),
                        [](unsigned char c) {return std::tolower(c); });

                    //replace special character ampersand with ""
                    created_text = regex_replace(created_text, reg, "");

                    if (twitterID == "SMRT_Singapore") {
                        if (((created_text.find("fault") != std::string::npos) || (created_text.find("maintenance") != std::string::npos)) && (created_text.find("update") == std::string::npos) && (created_text.find("cleared") == std::string::npos) && (created_text.find("bplrt") == std::string::npos) && (created_text.find("@") == std::string::npos)) {
                            myfile << created_at << "," << created_text << "\n";

                        }
                    }
                    if (twitterID == "LTAtrafficnews") {
                        myfile << created_at << "," << created_text << "\n";
                    }
                }
                myfile.close();
            }
            else
            {
                twitterObj.getLastCurlError(replyMsg);
                std::cout << "\ntwitterClient:: twitCurl::timelinePublicGet error:\n%s\n", replyMsg.c_str();
            }
        }
      
        if ((twitterID == "3") || (twitterID == "4")) {
            ifstream ip("example.csv");

            if (!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

            string tweets;

            while (ip.good()) {

                getline(ip, tweets, '\n');

                std::cout << tweets << "\n" << endl;

            }
            ip.close();
            
        }
        
        if (twitterID == "5") {
            ifstream ip("example.csv");

            if (!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

            string tweets;

            while (ip.good()) {

                getline(ip, tweets, '\n');

                //std::cout << tweets << "\n" << endl;

                if (tweets.find("fault") != std::string::npos) {
                    fault++;
                }

                if (tweets.find("maintenance") != std::string::npos) {
                    maintenance++;
                }

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
            std::cout << "Fault: " << fault << "\n";
            std::cout << "Maintenance: " << maintenance << "\n";
            std::cout << "Track: " << track << "\n";
            std::cout << "Power: " << power << "\n";
            std::cout << "Door: " << door << "\n";
            std::cout << "Train: " << train << "\n";
            std::cout << "Signal: " << signal << "\n\n";

            ip.close();

            vector<int> vector1 = { fault, maintenance, track, power, door, train, signal };

            string graph = "      ";
            for (int i = 0; i < vector1.size(); i++) {
                graph.append(to_string(1900 + 20 * i));
                graph.append("  ");
            }

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

            return 0;
        }
        else
        {
            continue;
        }
    }
}