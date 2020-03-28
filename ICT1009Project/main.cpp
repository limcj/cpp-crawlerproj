//////////////////////THE MAIN portion of the app that will be executed when run/////////////////////////////


#include <stdio.h>
#include <iostream>
#include <istream>
#include <algorithm>
#include <cctype>
#include <string>
#include <regex>
#include <vector>
#include <iomanip>
#include "funcCaller.h"
#include "twitterCrawler.h"
#include "app_State.h"

//include libcurl header file
#include <libcurl/oauthlib.h>
#include <libcurl/twitcurl.h>
#include <json/json.h>

#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))

using namespace std;


int main() {	

	//prompt user to select a crawler
	funcCaller fc;
	cin >> fc;

}