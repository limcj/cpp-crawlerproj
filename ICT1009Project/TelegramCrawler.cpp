//Alfred
#include "Telegramcrawler.h" 
#include "funcCaller.h"


#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")

using namespace std;

static size_t my_write(void* buffer, size_t size, size_t numb, void* param) {
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * numb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

string removeWord(string str, string word)
{
	// Check if the word is present in string 
	// If found, remove it using removeAll() 
	if (word == "word") {
		int start_point = 0;
		int end_point = 0;
		while ((str.find("<") != string::npos) && (str.find(">") != string::npos)) {
			for (int i = 0; i < str.length(); i++) {
				if (str[i] == '<') {
					start_point = i;
				}
				if (str[i] == '>') {
					end_point = i + 1 - start_point;
					break;
				}
			}
			str.erase(start_point, end_point);
		}
	}

	if (word == "date") {
		int start_point = 0;
		int end_point = 0;
		int date_point = 0;
		while ((str.find("<") != string::npos) && (str.find(">") != string::npos)) {

			for (int i = 0; i < str.length(); i++) {
				if (str[i] == '<') {
					start_point = i;
				}
				if (str[i] == '>') {
					end_point = i + 1 - start_point;
					break;
				}
			}
			string temp_word = str.substr(start_point, end_point);
			if (temp_word.find("datetime") != string::npos) {
				for (int i = 0; i < str.length(); i++) {
					if ((str[i] == '2') && (str[i + 1] == '0') && (str[i + 2] == '1')) {
						date_point = i;
						break;
					}
				}
				str = str.substr(date_point, 10);
				str = str.replace(4, 1, "-");
				str = str.replace(7, 1, "-");
				break;
			}
			else {
				str.erase(start_point, end_point);
			}
		}
	}
	word = ",";
	if (str.find(word) != string::npos)
	{
		size_t p = -1;

		// To cover the case 
		// if the word is at the 
		// beginning of the string 
		// or anywhere in the middle 
		string tempWord = word;
		while ((p = str.find(word)) != string::npos)
			str.replace(p, tempWord.length(), "");

	}

	// Return the resultant string 
	return str;
}

void Telegramcrawler::telecrawler()
{
	std::string result;
	std::string filter1;
	std::string URL;
	std::string final_URL;
	std::int64_t MAX;

	CURL* curl;
	CURLcode res;

	cout << "\n\nTELEGRAM CRAWL GOING TO BEGIN" << endl;
	cout << "THIS PLEASE TAKE A WHILE, PLEASE WAIT." << endl;

	Sleep(5000);

	MAX = 1000;
	URL = "https://t.me/s/sgmrt?before=";

	final_URL = URL + std::to_string(MAX);

	while (MAX >= 20) {
		final_URL = URL + std::to_string(MAX);
		curl_global_init(CURL_GLOBAL_DEFAULT);
		curl_global_cleanup();
		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, final_URL.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

			res = curl_easy_perform(curl);

			curl_easy_cleanup(curl);

			if (CURLE_OK != res) {
				std::cerr << " CURL error: " << res << '\n';
			}
		}
		MAX = MAX - 20;
		curl_global_cleanup();
	}

	std::ofstream myfile;
	myfile.open("example.txt");
	myfile << result;
	myfile.close();

	std::ifstream file("example.txt");
	std::string str;
	int sum = 0;
	string str4;
	while (std::getline(file, str))
	{

		string str2("tgme_widget_message_text js-message_text");
		string str3("time datetime=");

		if (str.find(str2) != string::npos) {
			if (((str.find("fault") != std::string::npos) || (str.find("Fault") != std::string::npos) || (str.find("maintenance") != std::string::npos) || (str.find("Maintenance") != std::string::npos))
				&& ((str.find("update") == std::string::npos) && (str.find("UPDATE") == std::string::npos) && (str.find("cleared") == std::string::npos)
					&& (str.find("bplrt") == std::string::npos) && (str.find("@") == std::string::npos) && (str.find("Reminder") == std::string::npos) && (str.find("rdeminder") == std::string::npos)
					&& (str.find("every") == std::string::npos) && (str.find("Every") == std::string::npos) && (str.find("conducting") == std::string::npos))) {
				//&& ((str.find("[") != std::string::npos) && (str.find("]") != std::string::npos)))
				//std::cout << str << "\n";
				str = removeWord(str, "word");
				str4 = (str + "\n");
			}
			else {
				str4 = ("0\n");
			}
		}

		if (str.find(str3) != string::npos) {
			//std::cout << str << "\n\n";
			if (str4 != "0\n") {
				str = removeWord(str, "date");
				filter1.append(str + "," + str4);
			}
		}
	}

	std::ofstream csvfile;
	csvfile.open("TeleDataSet.csv");
	csvfile << filter1;
	csvfile.close();

	system("CLS");
	cout << "\nTELEGRAM CRAWL FINISHED, exported TeleDataSet.csv\n" << endl;

	funcCaller fc;
	fc.getInput();

}

