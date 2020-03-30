#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "analysis.h"

//global variables for MRT station names
std::string Circle[] = { "Dhoby Ghaut","Bras Basah","Esplanade","Promenade","Nicoll Highway","Stadium","Mountbatten","Dakota","Paya Lebar","MacPherson","Tai Seng","Bartley","Serangoon","Lorong Chuan","Bishan","Marymount","Caldecott","Bukit Brown","Botanic Gardens","Farrer Road","Holland Village","Buona Vista","One-North","Kent Ridge","Haw Par Villa","Pasir Panjang","Labrador Park","Telok Blangah","HabourFront","Bayfront","Marina Bay" };
std::string Downtown[] = { "Bukit Panjang","Cashew","Hillview","Hume","Beauty World","King Albert Park","Sixth Avenue","Tan Kah Kee","Botanic Gardens","Stevens","Newton","Little India","Rochor","Bugis","Promenade","Bayfront","Downtown","Telok Ayer","Chinatown","Fort Canning","Bencoolen","Jalan Besar","Bendemeer","Geylang Bahru","Mattar","MacPherson","Ubi","Kaki Bukit","Bedok North","Bedok Resevoir","Tampines West","Tampines","Tampines East","Upper Changi","Expo","Xilin","Sungei Bedok" };
std::string EastWest[] = { "Pasir Ris","Tampines","Simei","Tanah Merah","Bedok","Kembangan","Eunos","Paya Lebar","Aljunied","Kallang","Lavender","Bugis","City Hall","Raffles Place","Tanjong Pagar","Outram Park","Tiong Bahru","Redhill","Queenstown","Commonwealth","Buona Vista","Dover","Clementi","Jurong East","Chinese Garden","Lakeside","Boon lay", "Pioneer","Joo Koon","Gul Circle","Tuas Crescent","Tuas West Road","Tuas Link", "Expo","Changi Airport" };
std::string NorthEast[] = { "HabourFront","Reserved","Outram Park","Chinatown","Clarke Quay","Dhoby Ghaut","Little India","Farrer Park","Boon Keng","Potong Pasir","Woodleigh","Serangoon","Kovan","Hougang","Buangkok","Sengkang","Punggol","Punggol Coast" };
std::string NorthSouth[] = { "Jurong East","Bukit Batok","Bukit Gombak","Chua Chu Kang","Yew Tee","Sugei Kadut","Kranji","Marsiling","Woodlands","Admiralty","Sembawang","Canberra","Yishun","Khatib","Yio Chu Kang","Ang Mo Kio","Bishan","Braddell","Toa Payoh","Novena","Newton","Orchard","Somerset","Dhoby Ghaut","City Hall","Raffles Place","Marina Bay","Marina South Pier","Brickland" };
std::string Thomson[] = { "Woodlands North", "Woodlands","Woodlands South","Springleaf","Lentor","Mayflower","Bright Hill","Upper Thomson","Caldecott","Mount Pleasant","Stevens","Napier","Orchard Boulevard","Orchard","Great World","Havelock","Outram Park","Maxwell","Shenton Way","Marina Bay","Marina South","Gardens by the Bay","Tanjong Rhu","Katong Park","Tanjong Katong","Marine Parade","Marine Terrace","Siglap","Bayshore","Bedok South","Sungei Bedok","Founders' Memorial" };

//Main class for stations
class Stationbase
{
private:
	std::string stationname;
	std::string stationline;
	//array of faults, e.g. fault[0] = train fault, [1] = power fault etc...
	int twitterfault[6];
	int telegramfault[6];
	int twittertotalfault;
	int telegramtotalfault;
public:
	//Default constructor for array of stations, and constructor with parameters for initializing individual stations
	Stationbase();
	Stationbase(std::string, std::string);
	//Allows addition of faults of stations
	void operator+(Stationbase);
	//Adding faults individually e.g. add 10 counts to power fault, used corresponding to data crawled
	void addTwitterFault(std::string, int);
	void addTelegramFault(std::string, int);
	//output overwrite to print object in desired format
	friend std::ostream& operator<<(std::ostream&, const Stationbase&);
	//Adds a line into stationline, for when station is a junction, e.g. tampines being part of East West and Downtown line
	void addLine(std::string);
	//sets values to 0 for faults
	void setToZero();
	//Return variable functions for encapsulation
	std::string getName();
	std::string getLine();
};

//Default initializes all elements in faults to 0
Stationbase::Stationbase()
{
	stationname = "";
	twittertotalfault = 0;
	telegramtotalfault = 0;
	for (int i = 0; i < 6; i++)
	{
		twitterfault[i] = 0;
		telegramfault[i] = 0;
	}
}

//Same as above, but with parameters for variables
Stationbase::Stationbase(std::string name, std::string line)
{
	stationname = name;
	stationline = line;
	twittertotalfault = 0;
	telegramtotalfault = 0;
	for (int i = 0; i < 6; i++)
	{
		twitterfault[i] = 0;
		telegramfault[i] = 0;
	}
}

//For each index in faults, add correspondingly the input station object faults
void Stationbase::operator+(Stationbase station)
{
	for (int i = 0; i < 6; i++)
	{
		twitterfault[i] += station.twitterfault[i];
		telegramfault[i] += station.telegramfault[i];
		twittertotalfault += station.twitterfault[i];
		telegramtotalfault += station.telegramfault[i];
	}
}

//Adds number of faults for specified type by taking in parameter for conditional statements. Update total faults accordingly
void Stationbase::addTwitterFault(std::string faulttype, int numberoffault)
{
	if (faulttype == "maintenance")
	{
		twitterfault[0] += numberoffault;
	}
	else if (faulttype == "trackfault")
	{
		twitterfault[1] += numberoffault;
	}
	else if (faulttype == "powerfault")
	{
		twitterfault[2] += numberoffault;
	}
	else if (faulttype == "doorfault")
	{
		twitterfault[3] += numberoffault;
	}
	else if (faulttype == "trainfault")
	{
		twitterfault[4] += numberoffault;
	}
	else if (faulttype == "signalfault")
	{
		twitterfault[5] += numberoffault;
	}
	twittertotalfault += numberoffault;
}

void Stationbase::addTelegramFault(std::string faulttype, int numberoffault)
{
	if (faulttype == "maintenance")
	{
		telegramfault[0] += numberoffault;
	}
	else if (faulttype == "trackfault")
	{
		telegramfault[1] += numberoffault;
	}
	else if (faulttype == "powerfault")
	{
		telegramfault[2] += numberoffault;
	}
	else if (faulttype == "doorfault")
	{
		telegramfault[3] += numberoffault;
	}
	else if (faulttype == "trainfault")
	{
		telegramfault[4] += numberoffault;
	}
	else if (faulttype == "signalfault")
	{
		telegramfault[5] += numberoffault;
	}
	telegramtotalfault += numberoffault;
}

//Outputs in format of block of text
std::ostream& operator<<(std::ostream& out, const Stationbase& station)
{
	out << std::endl << "Station: " << station.stationline << ", " << station.stationname << std::endl << std::endl;
	out << "Maintenance, Twitter: " << station.twitterfault[0] << ", Telegram: " << station.telegramfault[0] << std::endl;
	out << "Track faults, Twitter: " << station.twitterfault[1] << ", Telegram: " << station.telegramfault[1] << std::endl;
	out << "Power faults, Twitter: " << station.twitterfault[2] << ", Telegram: " << station.telegramfault[2] << std::endl;
	out << "Door faults, Twitter: " << station.twitterfault[3] << ", Telegram: " << station.telegramfault[3] << std::endl;
	out << "Train faults, Twitter: " << station.twitterfault[4] << ", Telegram: " << station.telegramfault[4] << std::endl;
	out << "Signal faults, Twitter: " << station.twitterfault[5] << ", Telegram: " << station.telegramfault[5] << std::endl << std::endl;
	out << "Total number of faults, Twitter: " << station.twittertotalfault << ", Telegram: " << station.telegramtotalfault << std::endl;
	return out;
}

//Appends additional station lines to current string
void Stationbase::addLine(std::string line)
{
	stationline = stationline + ", " + line;
}

//sets all fault values to 0
void Stationbase::setToZero()
{
	for (int i = 0; i < 6; i++)
	{
		twitterfault[i] = 0;
		telegramfault[i] = 0;
	}
	twittertotalfault = 0;
	telegramtotalfault = 0;
}

//return variables
std::string Stationbase::getName()
{
	return stationname;
}

std::string Stationbase::getLine()
{
	return stationline;
}


void analysis()
{
	//integer to maintain infinite loop until user specified exit
	int loop = 1;
	//string userinput to hold each input for manipulation and identification, vector holds each input 
	std::string userinput;
	std::vector<std::string> userinputvector;
	std::string userinputbuffer;
	//for calculation of range functions, and validation
	int rangestart, rangeend, rangetemp, valid = 0;
	//Initializes total station for calculations of user functions
	Stationbase total("Culmination of Stations", "N/A");
	//variables for csv manipulation
	std::vector<std::string> tweetcrawl;
	std::vector<int> tweetcrawlindex;
	std::string search;
	std::string searchtemp;

	//Initializes the number of stations needed via size of array of strings / size of string allocation to get number
	const int circle = (sizeof(Circle) / sizeof(Circle[0]));
	const int downtown = (sizeof(Downtown) / sizeof(Downtown[0]));
	const int eastwest = (sizeof(EastWest) / sizeof(EastWest[0]));
	const int northeast = (sizeof(NorthEast) / sizeof(NorthEast[0]));
	const int northsouth = (sizeof(NorthSouth) / sizeof(NorthSouth[0]));
	const int thomson = (sizeof(Thomson) / sizeof(Thomson[0]));

	//Array of Stations with total of all stations, so a complete array of all stations. 
	//Created in the form of pointers so memory locations can be manipulated e.g. stations that occur multiple times (Tampines in East west, in downtown) to share same location
	Stationbase* Lines[circle + downtown + eastwest + northeast + northsouth + thomson];

	//Initializes all individual stations based on interable counter, limited by each line's limits as conditions 
	for (int counter = 0; counter < circle + downtown + eastwest + northeast + northsouth + thomson; counter++)
	{
		//initializes circle line objects
		if (counter < circle - 2)
		{
			Lines[counter] = new Stationbase(Circle[counter], "CC" + std::to_string(counter + 1));
		}
		//last 2 stations in circle line with different station number
		else if (counter < circle)
		{
			Lines[counter] = new Stationbase(Circle[counter], "CE" + std::to_string(counter - 28));
		}
		//initializes downtown line objects
		else if (counter < circle + downtown)
		{
			Lines[counter] = new Stationbase(Downtown[counter - circle], "DT" + std::to_string(counter - circle + 1));
		}
		//initializes eastwest line objects, last 2 stations with different number
		else if (counter < circle + downtown + eastwest)
		{
			if (counter < circle + downtown + eastwest - 2)
			{
				Lines[counter] = new Stationbase(EastWest[counter - circle - downtown], "EW" + std::to_string(counter - circle - downtown + 1));
			}
			else
			{
				Lines[counter] = new Stationbase(EastWest[counter - circle - downtown], "CG" + std::to_string(counter - 32 - circle - downtown));
			}
		}
		//Initializes northeast line objects
		else if (counter < circle + downtown + eastwest + northeast)
		{
			Lines[counter] = new Stationbase(NorthEast[counter - circle - downtown - eastwest], "NE" + std::to_string(counter - circle - downtown - eastwest + 1));
		}
		//Initializes northsouth line objects
		else if (counter < circle + downtown + eastwest + northeast + northsouth)
		{
			Lines[counter] = new Stationbase(NorthSouth[counter - circle - downtown - eastwest - northeast], "NS" + std::to_string(counter - circle - downtown - eastwest - northeast + 1));
		}
		//Initializes Thomson line objects
		else if (counter < circle + downtown + eastwest + northeast + northsouth + thomson)
		{
			Lines[counter] = new Stationbase(Thomson[counter - circle - downtown - eastwest - northeast - northsouth], "TE" + std::to_string(counter - circle - downtown - eastwest - northeast - northsouth + 1));
		}
	}

	//For completed array, check each index to all indexes, it same name, but different memory location, converge in a cascading pattern, so multiple occurances now are one object with multiple station lines
	for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
	{
		//Check current index with all indexes after it
		for (int j = i; j < sizeof(Lines) / sizeof(Lines[i]); j++)
		{
			//if they have the same name (via getname finction)
			if ((*Lines[i]).getName() == (*Lines[j]).getName())
			{
				//if different memory location
				if (Lines[i] != Lines[j])
				{
					//Adds second object line to the first object, and points second object index to first object memory location.
					//Now first and second are merged. If there are more occurances, they will merge with either previous indexes as they are all the same location now.
					(*Lines[i]).addLine((*Lines[j]).getLine());
					Lines[j] = Lines[i];
				}
			}
		}
	}

	//get twitter data from loaded csv
	std::ifstream ip("twitterdata.csv");

	//error catching if not loaded
	if (!ip.is_open()) std::cout << "ERROR: Please crawl data first" << '\n';

	//reference for each line of tweet
	std::string tweets;

	//while not end of file
	while (ip.good())
	{
		//clear temp variables for manipulation
		tweetcrawl.clear();
		tweetcrawlindex.clear();
		searchtemp == "";
		search = "";
		std::getline(ip, tweets, '\n');
		//count the number of each fault, enter each loop if keyword fault is found
		if (tweets.find("maintenance") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (tweets.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTwitterFault("maintenance", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTwitterFault("maintenance", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTwitterFault("maintenance", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTwitterFault("maintenance", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}
		if (tweets.find("track") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (tweets.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTwitterFault("trackfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTwitterFault("trackfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTwitterFault("trackfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTwitterFault("trackfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}

		if (tweets.find("power") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (tweets.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTwitterFault("powerfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTwitterFault("powerfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTwitterFault("powerfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTwitterFault("powerfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}

		if (tweets.find("door") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (tweets.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTwitterFault("doorfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTwitterFault("doorfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTwitterFault("doorfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTwitterFault("doorfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}

		if ((tweets.find("train fault") != std::string::npos) || (tweets.find("signalling") != std::string::npos))
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (tweets.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTwitterFault("trainfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTwitterFault("trainfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTwitterFault("trainfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTwitterFault("trainfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}

		if (tweets.find("signal") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (tweets.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTwitterFault("signalfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTwitterFault("signalfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTwitterFault("signalfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}
	}

	//get telegram data from loaded csv
	std::ifstream kp("TeleDataSet.csv");

	//error catching if not loaded
	if (!kp.is_open()) std::cout << "ERROR: Please crawl data first" << '\n';

	//reference for each line of tweet
	std::string telegrams;

	//while not end of file
	while (kp.good())
	{
		//clear temp variables for manipulation
		tweetcrawl.clear();
		tweetcrawlindex.clear();
		searchtemp == "";
		search = "";
		std::getline(kp, telegrams, '\n');
		for (int i = 0; i < telegrams.size(); i++)
		{
			telegrams[i] = (char)tolower(telegrams[i]);
		}
		//count the number of each fault, enter each loop if keyword fault is found
		if (telegrams.find("maintenance") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (telegrams.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTelegramFault("maintenance", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTelegramFault("maintenance", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTelegramFault("maintenance", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTelegramFault("maintenance", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}
		if (telegrams.find("track") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (telegrams.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTelegramFault("trackfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTelegramFault("trackfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTelegramFault("trackfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTelegramFault("trackfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}

		if (telegrams.find("power") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (telegrams.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTelegramFault("powerfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTelegramFault("powerfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTelegramFault("powerfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTelegramFault("powerfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}

		if (telegrams.find("door") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (telegrams.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTelegramFault("doorfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTelegramFault("doorfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTelegramFault("doorfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTelegramFault("doorfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}

		if ((telegrams.find("train fault") != std::string::npos) || (tweets.find("signalling") != std::string::npos))
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (telegrams.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTelegramFault("trainfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTelegramFault("trainfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTelegramFault("trainfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTelegramFault("trainfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}

		if (telegrams.find("signal") != std::string::npos)
		{
			//for every station, get station name, decapitalize and remove spaces to search data string
			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
			{
				search = "";
				searchtemp = (*Lines[i]).getName();
				for (int j = 0; j < searchtemp.size(); j++)
				{
					if (searchtemp[j] != ' ')
					{
						search = search + (char)tolower(searchtemp[j]);
					}
				}
				//if station is found in string, push to vector, and push index where it is found
				if (telegrams.find(search) != std::string::npos)
				{
					tweetcrawl.push_back((*Lines[i]).getName());
					tweetcrawlindex.push_back(i);
				}
			}
			//if a singular station is mentioned, increment fault as per keyword for station
			if (tweetcrawl.size() == 1)
			{
				(*Lines[tweetcrawlindex[0]]).addTelegramFault("signalfault", 1);
			}
			//if more than one station is mentioned, i.e. a range Bishan to Yio Chu Kang... get first and last index of vector as stations could be repeated due to multiple occuraances of stations i.e. Tampines in both DT and EW sections
			else if (tweetcrawl.size() > 1)
			{
				//check index values to ensure array runs in sequence i.e. must be Pasir Ris -> Tampines, not the other way around
				if (tweetcrawl[0] == tweetcrawl[tweetcrawl.size() - 1])
				{
					(*Lines[tweetcrawlindex[0]]).addTelegramFault("signalfault", 1);
				}
				else if (tweetcrawlindex[0] > tweetcrawlindex[tweetcrawlindex.size() - 1])
				{
					for (int i = tweetcrawlindex[tweetcrawlindex.size() - 1]; i <= tweetcrawlindex[0]; i++)
					{
						(*Lines[i]).addTelegramFault("signalfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[0])
						{
							break;
						}
					}
				}
				else
				{
					for (int i = tweetcrawlindex[0]; i <= tweetcrawlindex[tweetcrawlindex.size() - 1]; i++)
					{
						(*Lines[i]).addTelegramFault("signalfault", 1);
						if ((*Lines[i]).getName() == tweetcrawl[tweetcrawlindex.size() - 1])
						{
							break;
						}
					}
				}
			}
		}
	}

	//Infinite loop for user input untill command to exit
	while (loop == 1)
	{
		//Clears temporary values (e.g. user input fields, total value stations)
		userinput = "";
		userinputbuffer = "";
		userinputvector.clear();
		total.setToZero();
		valid = 0;
		rangestart = 0;
		rangeend = 0;
		rangetemp = 0;
		//Prompts user and gets line of input
		std::cout << "Please enter a command. To see a list of available commands, please enter <help> without chevrons (<>): ";
		std::getline(std::cin, userinput);

		//waits for user input
		while (userinput.length() == 0) {
			getline(std::cin, userinput);
		}

		//manipulates the input into a vector, by using space ' ' as a delimiter to split the strings
		for (int i = 0; i < userinput.size(); i++)
		{
			if (i == userinput.size() - 1)
			{
				userinputbuffer += userinput[i];
				userinputvector.push_back(userinputbuffer);
			}
			if (userinput[i] != ' ')
			{
				userinputbuffer += userinput[i];
			}
			else
			{
				userinputvector.push_back(userinputbuffer);
				userinputbuffer = "";
			}
		}
		//implements the functions via checking size of the vector, and the keyword. If size == 1, checks keyword for all one word functions e.g. exit, help.
		if (userinputvector.size() == 1)
		{
			//exits loop and program
			if (userinputvector[0] == "b")
			{
				loop = 0;
			}
			//display list of available functions
			else if (userinputvector[0] == "help")
			{
				std::cout << "<help> : Displays list of user commands." << std::endl << "<b> : Exits the Analysis Menu." << std::endl << "<print all> : prints all stations available." << std::endl << "<print (station)> : prints the specified station." << std::endl << "<print range (station 1) (station 2)> : prints all stations from station 1 to station 2." << std::endl << "<count all> : Tallies up all faults of all stations." << std::endl << "<count (station 1) (station 2)> : Tallies up all faults from staion 1 to station 2." << std::endl;
			}
			else
			{
				std::cout << "Please enter a valid command." << std::endl;
			}
		}
		//if size == 2, checks 2 word functions
		else if (userinputvector.size() == 2)
		{
			//with print a a keywork
			if (userinputvector[0] == "print")
			{
				//prints all stations
				if (userinputvector[1] == "all")
				{
					for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
					{
						std::cout << *Lines[i];
					}
				}
				//tries to search for the second keyword as a station, returning an error message if station can not be found
				else
				{
					for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
					{
						if (userinputvector[1] == (*Lines[i]).getName())
						{
							std::cout << *Lines[i];
							valid = 1;
							break;
						}
					}
					if (valid == 0)
					{
						std::cout << userinputvector[1] << " is not a valid station." << std::endl;
					}
				}
			}
			//with count as a keyword
			else if (userinputvector[0] == "count")
			{
				//tallies up all station faults
				if (userinputvector[1] == "all")
				{
					for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
					{
						total + *Lines[i];
					}
					std::cout << total;
				}
				else
				{
					std::cout << "Please enter a valid command." << std::endl;
				}
			}
		}
		//at size == 3
		else if (userinputvector.size() == 3)
		{
			//if user specifies to print a specific station, but with spaces in between e.g. Pasir Ris
			if (userinputvector[0] == "print" && userinputvector[1] != "range")
			{
				for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
				{
					if (userinputvector[1] + " " + userinputvector[2] == (*Lines[i]).getName())
					{
						std::cout << *Lines[i];
						valid = 1;
						break;
					}
				}
				if (valid == 0)
				{
					std::cout << "The listed station " << userinputvector[1] + " " + userinputvector[2] << " is invalid." << std::endl;;
				}
			}
			//if user wants to count, by 3rd input should have entered both start and bound for range to count. This is done by matching start and bound to names in the array of objects
			else if (userinputvector[0] == "count")
			{
				rangestart = 0;
				rangeend = 0;
				for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
				{
					if (userinputvector[1] == (*Lines[i]).getName())
					{
						rangestart = i;
					}
					if (userinputvector[2] == (*Lines[i]).getName())
					{
						rangeend = i;
					}
				}
				//if both start and bound finds a match, proceed to do range function, otherwise, exits as it can't be found
				if (rangestart != 0 && rangeend != 0)
				{
					//if user input in opposite order e.g. Bedok, then Pasir Ris when Pasir Ris should start first as EW1
					if (rangeend < rangestart)
					{
						rangetemp = rangeend;
						rangeend = rangestart;
						rangestart = rangetemp;
					}
					for (int i = rangestart; i < rangeend + 1; i++)
					{
						total + *Lines[i];
					}
					std::cout << total;
				}
				else
				{
					std::cout << "The chosen stations are invalid" << std::endl;
				}
			}
		}
		//at size == 4
		else if (userinputvector.size() == 4)
		{
			//count function here applies to when there is one station with 2 indexes, e.g. with space such as Pasir Ris
			if (userinputvector[0] == "count")
			{
				rangestart = 0;
				rangeend = 0;
				for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
				{
					//conditions to check for double index stations, which can happen as the first station input or second
					if (userinputvector[1] == (*Lines[i]).getName())
					{
						rangestart = i;
					}
					else if (userinputvector[1] + " " + userinputvector[2] == (*Lines[i]).getName())
					{
						std::cout << "here";
						rangestart = i;
					}
					if (userinputvector[3] == (*Lines[i]).getName())
					{
						std::cout << "here";
						rangeend = i;
					}
					else if (userinputvector[2] + " " + userinputvector[3] == (*Lines[i]).getName())
					{
						rangeend = i;
					}
				}
				if (rangestart != 0 && rangeend != 0)
				{
					if (rangeend < rangestart)
					{
						rangetemp = rangeend;
						rangeend = rangestart;
						rangestart = rangetemp;
					}
					for (int i = rangestart; i < rangeend + 1; i++)
					{
						total + *Lines[i];
					}
					std::cout << total;
				}
				else
				{
					std::cout << "The chosen stations are invalid" << std::endl;
				}
			}
			if (userinputvector[0] == "print" && userinputvector[1] != "range")
			{
				for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
				{
					if (userinputvector[1] + " " + userinputvector[2] + " " + userinputvector[3] == (*Lines[i]).getName())
					{
						std::cout << *Lines[i];
						valid = 1;
						break;
					}
				}
				if (valid == 0)
				{
					std::cout << "The listed station " << userinputvector[1] + " " + userinputvector[2] + " " + userinputvector[3] << " is invalid." << std::endl;;
				}
			}
			//tries to find a range of stations, and print them, similarly to count range function
			if (userinputvector[0] == "print" && userinputvector[1] == "range")
			{
				rangestart = 0;
				rangeend = 0;
				for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
				{
					if (userinputvector[2] == (*Lines[i]).getName())
					{
						rangestart = i;
					}
					if (userinputvector[3] == (*Lines[i]).getName())
					{
						rangeend = i;
					}
				}
				if (rangestart != 0 && rangeend != 0)
				{
					if (rangeend < rangestart)
					{
						rangetemp = rangeend;
						rangeend = rangestart;
						rangestart = rangetemp;
					}
					for (int i = rangestart; i < rangeend + 1; i++)
					{
						std::cout << *Lines[i];
					}
				}
				else
				{
					std::cout << "The chosen stations are invalid" << std::endl;
				}
			}
		}
		//at size == 5
		else if (userinputvector.size() == 5)
		{
			//count function here applies for twhen both station inputs use double indexes, e.g. Pasir Ris -> Paya Lebar
			if (userinputvector[0] == "count")
			{
				rangestart = 0;
				rangeend = 0;
				for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
				{
					if (userinputvector[1] + " " + userinputvector[2] == (*Lines[i]).getName())
					{
						rangestart = i;
					}
					if (userinputvector[3] + " " + userinputvector[4] == (*Lines[i]).getName())
					{
						rangeend = i;
					}
				}
				if (rangestart != 0 && rangeend != 0)
				{
					if (rangeend < rangestart)
					{
						rangetemp = rangeend;
						rangeend = rangestart;
						rangestart = rangetemp;
					}
					for (int i = rangestart; i < rangeend + 1; i++)
					{
						total + *Lines[i];
					}
					std::cout << total;
				}
				std::cout << "The chosen stations are invalid" << std::endl;
			}
			//the print function here works like the count function with either station being double indexed
			if (userinputvector[0] == "print" && userinputvector[1] == "range")
			{
				rangestart = 0;
				rangeend = 0;
				for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
				{
					if (userinputvector[2] == (*Lines[i]).getName())
					{
						rangestart = i;
					}
					else if (userinputvector[2] + " " + userinputvector[3] == (*Lines[i]).getName())
					{
						rangestart = i;
					}
					if (userinputvector[4] == (*Lines[i]).getName())
					{
						rangeend = i;
					}
					else if (userinputvector[3] + " " + userinputvector[4] == (*Lines[i]).getName())
					{
						rangeend = i;
					}
				}
				if (rangestart != 0 && rangeend != 0)
				{
					if (rangeend < rangestart)
					{
						rangetemp = rangeend;
						rangeend = rangestart;
						rangestart = rangetemp;
					}
					for (int i = rangestart; i < rangeend + 1; i++)
					{
						std::cout << *Lines[i];
					}
				}
				else
				{
					std::cout << "The chosen stations are invalid" << std::endl;
				}
			}
		}
		//at size == 6
		else if (userinputvector.size() == 6)
		{
			//print function here applies for when both stations are double indexed
			if (userinputvector[0] == "print" && userinputvector[1] == "range")
			{
				rangestart = 0;
				rangeend = 0;
				for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
				{
					if (userinputvector[2] + " " + userinputvector[3] == (*Lines[i]).getName())
					{
						rangestart = i;
					}
					if (userinputvector[4] + " " + userinputvector[5] == (*Lines[i]).getName())
					{
						rangeend = i;
					}
				}
				if (rangestart != 0 && rangeend != 0)
				{
					if (rangeend < rangestart)
					{
						rangetemp = rangeend;
						rangeend = rangestart;
						rangestart = rangetemp;
					}
					for (int i = rangestart; i < rangeend + 1; i++)
					{
						std::cout << *Lines[i];
					}
				}
				std::cout << "The chosen stations are invalid" << std::endl;
			}
		}
	}
}