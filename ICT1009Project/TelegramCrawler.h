#ifndef PLAYER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PLAYER_H

#define CURL_STATICLIB

#include <iostream>
#include <string>
#include <fstream>
//#include "telegram/x32 Debug/include/curl.h"
#include <fstream>
#include "include/telecurlx32/curl.h"

#ifdef _DEBUG
#pragma comment (lib, "include/telecurlx32/libcurl_a_debug.lib")
#else
#pragma comment (lib, "include/telecurl/libcurl_a.lib")
#endif

class Telegramcrawler {
private:

public:
	void telecrawler();
};

#endif