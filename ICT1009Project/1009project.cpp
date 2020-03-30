//#include <iostream>
//#include <string>
//
////global variables for MRT station names
//std::string Circle[] = { "Dhoby Ghaut","Bras Basah","Esplanade","Promenade","Nicoll Highway","Stadium","Mountbatten","Dakota","Paya Lebar","MacPherson","Tai Seng","Bartley","Serangoon","Lorong Chuan","Bishan","Marymount","Caldecott","Bukit Brown","Botanic Gardens","Farrer Road","Holland Village","Buona Vista","One-North","Kent Ridge","Haw Par Villa","Pasir Panjang","Labrador Park","Telok Blangah","HabourFront","Bayfront","Marina Bay" };
//std::string Downtown[] = { "Bukit Panjang","Cashew","Hillview","Hume","Beauty World","King Albert Park","Sixth Avenue","Tan Kah Kee","Botanic Gardens","Stevens","Newton","Little India","Rochor","Bugis","Promenade","Bayfront","Downtown","Telok Ayer","Chinatown","Fort Canning","Bencoolen","Jalan Besar","Bendemeer","Geylang Bahru","Mattar","MacPherson","Ubi","Kaki Bukit","Bedok North","Bedok Resevoir","Tampines West","Tampines","Tampines East","Upper Changi","Expo","Xilin","Sungei Bedok" };
//std::string EastWest[] = { "Pasir Ris","Tampines","Simei","Tanah Merah","Bedok","Kembangan","Eunos","Paya Lebar","Aljunied","Kallang","Lavender","Bugis","City Hall","Raffles Place","Tanjong Pagar","Outram Park","Tiong Bahru","Redhill","Queenstown","Commonwealth","Buona Vista","Dover","Clementi","Jurong East","Chinese Garden","Lakeside","Boon lay", "Pioneer","Joo Koon","Gul Circle","Tuas Crescent","Tuas West Road","Tuas Link", "Expo","Changi Airport" };
//std::string NorthEast[] = { "HabourFront","Reserved","Outram Park","Chinatown","Clarke Quay","Dhoby Ghaut","Little India","Farrer Park","Boon Keng","Potong Pasir","Woodleigh","Serangoon","Kovan","Hougang","Buangkok","Sengkang","Punggol","Punggol Coast" };
//std::string NorthSouth[] = { "Jurong East","Bukit Batok","Bukit Gombak","Chua Chu Kang","Yew Tee","Sugei Kadut","Kranji","Marsiling","Woodlands","Admiralty","Sembawang","Canberra","Yishun","Khatib","Yio Chu Kang","Ang Mo Kio","Bishan","Braddell","Toa Payoh","Novena","Newton","Orchard","Somerset","Dhoby Ghaut","City Hall","Raffles Place","Marina Bay","Marina South Pier","Brickland" };
//std::string Thomson[] = { "Woodlands North", "Woodlands","Woodlands South","Springleaf","Lentor","Mayflower","Bright Hill","Upper Thomson","Caldecott","Mount Pleasant","Stevens","Napier","Orchard Boulevard","Orchard","Great World","Havelock","Outram Park","Maxwell","Shenton Way","Marina Bay","Marina South","Gardens by the Bay","Tanjong Rhu","Katong Park","Tanjong Katong","Marine Parade","Marine Terrace","Siglap","Bayshore","Bedok South","Sungei Bedok","Founders' Memorial" };
//
////Main class for stations
//class Stationbase
//{
//private:
//	std::string stationname;
//	std::string stationline;
//	//array of faults, e.g. fault[0] = train fault, [1] = power fault etc...
//	int fault[5];
//	int totalfault;
//public:
//	//Default constructor for array of stations, and constructor with parameters for initializing individual stations
//	Stationbase();
//	Stationbase(std::string, std::string);
//	//Allows addition of faults of stations
//	void operator+(Stationbase);
//	//Adding faults individually e.g. add 10 counts to power fault, used corresponding to data crawled
//	void addFault(std::string, int);
//	//output overwrite to print object in desired format
//	friend std::ostream& operator<<(std::ostream&, const Stationbase&);
//	//Adds a line into stationline, for when station is a junction, e.g. tampines being part of East West and Downtown line
//	void addLine(std::string);
//	//Return variable functions for encapsulation
//	std::string getName();
//	std::string getLine();
//};
//
////Default initializes all elements in faults to 0
//Stationbase::Stationbase()
//{
//	totalfault = 0;
//	for (int i = 0; i < 5; i++)
//	{
//		fault[i] = 0;
//	}
//}
//
////Same as above, but with parameters for variables
//Stationbase::Stationbase(std::string name, std::string line)
//{
//	stationname = name;
//	stationline = line;
//	totalfault = 0;
//	for (int i = 0; i < 5; i++)
//	{
//		fault[i] = 0;
//	}
//}
//
////For each index in faults, add correspondingly the input station object faults
//void Stationbase::operator+(Stationbase station)
//{
//	for (int i = 0; i < 5; i++)
//	{
//		fault[i] += station.fault[i];
//		totalfault += station.fault[i];
//	}
//}
//
////Adds number of faults for specified type by taking in parameter for conditional statements. Update total faults accordingly
//void Stationbase::addFault(std::string faulttype, int numberoffault)
//{
//	if (faulttype == "earlyclosure")
//	{
//		fault[0] += numberoffault;
//	}
//	else if (faulttype == "powerfault")
//	{
//		fault[1] += numberoffault;
//	}
//	else if (faulttype == "signalfault")
//	{
//		fault[2] += numberoffault;
//	}
//	else if (faulttype == "maintenance")
//	{
//		fault[3] += numberoffault;
//	}
//	else
//	{
//		fault[4] += numberoffault;
//	}
//	totalfault += numberoffault;
//}
//
////Outputs in format of block of text
//std::ostream& operator<<(std::ostream& out, const Stationbase& station)
//{
//	out << "Station: " << station.stationline << ", " << station.stationname << std::endl << "Early closures: " << station.fault[0] << std::endl << "Power faults: " << station.fault[1] << std::endl << "Signal faults: " << station.fault[2] << std::endl << "Maintenance: " << station.fault[3] << std::endl << "Others: " << station.fault[4] << std::endl << "Total number of faults: " << station.totalfault << std::endl << std::endl;
//	return out;
//}
//
////Appends additional station lines to current string
//void Stationbase::addLine(std::string line)
//{
//	stationline = stationline + ", " + line;
//}
//
////return variables
//std::string Stationbase::getName()
//{
//	return stationname;
//}
//
//std::string Stationbase::getLine()
//{
//	return stationline;
//}
//
//
//
//int main()
//{
//	int loop = 1;
//	std::string userinput = "";
//	//Initializes total station for calculations of user functions
//	Stationbase total("Culmination of Stations", "N/A");
//
//	//Initializes the number of stations needed via size of array of strings / size of string allocation to get number
//	const int circle = (sizeof(Circle) / sizeof(Circle[0]));
//	const int downtown = (sizeof(Downtown) / sizeof(Downtown[0]));
//	const int eastwest = (sizeof(EastWest) / sizeof(EastWest[0]));
//	const int northeast = (sizeof(NorthEast) / sizeof(NorthEast[0]));
//	const int northsouth = (sizeof(NorthSouth) / sizeof(NorthSouth[0]));
//	const int thomson = (sizeof(Thomson) / sizeof(Thomson[0]));
//
//	//Array of Stations with total of all stations, so a complete array of all stations. 
//	//Created in the form of pointers so memory locations can be manipulated e.g. stations that occur multiple times (Tampines in East west, in downtown) to share same location
//	Stationbase *Lines[circle + downtown + eastwest + northeast + northsouth + thomson];
//
//	//Initializes all individual stations based on interable counter, limited by each line's limits as conditions 
//	for (int counter = 0; counter < circle + downtown + eastwest + northeast + northsouth + thomson; counter++)
//	{
//		//initializes circle line objects
//		if (counter < circle - 2)
//		{
//			Lines[counter] = new Stationbase(Circle[counter], "CC" + std::to_string(counter + 1));
//		}
//		//last 2 stations in circle line with different station number
//		else if (counter < circle)
//		{
//			Lines[counter] = new Stationbase(Circle[counter], "CE" + std::to_string(counter - 28));
//		}
//		//initializes downtown line objects
//		else if (counter < circle + downtown)
//		{
//			Lines[counter] = new Stationbase(Downtown[counter - circle], "DT" + std::to_string(counter - circle + 1));
//		}
//		//initializes eastwest line objects, last 2 stations with different number
//		else if (counter < circle + downtown + eastwest)
//		{
//			if (counter < circle + downtown + eastwest - 2)
//			{
//				Lines[counter] = new Stationbase(EastWest[counter - circle - downtown], "EW" + std::to_string(counter - circle - downtown + 1));
//			}
//			else
//			{
//				Lines[counter] = new Stationbase(EastWest[counter - circle - downtown], "CG" + std::to_string(counter - 32 - circle - downtown));
//			}
//		}
//		//Initializes northeast line objects
//		else if (counter < circle + downtown + eastwest + northeast)
//		{
//			Lines[counter] = new Stationbase(NorthEast[counter - circle - downtown - eastwest], "NE" + std::to_string(counter - circle - downtown - eastwest + 1));
//		}
//		//Initializes northsouth line objects
//		else if (counter < circle + downtown + eastwest + northeast + northsouth)
//		{
//			Lines[counter] = new Stationbase(NorthSouth[counter - circle - downtown - eastwest - northeast], "NS" + std::to_string(counter - circle - downtown - eastwest - northeast + 1));
//		}
//		//Initializes Thomson line objects
//		else if (counter < circle + downtown + eastwest + northeast + northsouth + thomson)
//		{
//			Lines[counter] = new Stationbase(Thomson[counter - circle - downtown - eastwest - northeast - northsouth], "TE" + std::to_string(counter - circle - downtown - eastwest - northeast - northsouth + 1));
//		}
//	}
//
//	//For completed array, check each index to all indexes, it same name, but different memory location, converge in a cascading pattern, so multiple occurances now are one object with multiple station lines
//	for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
//	{
//		//Check current index with all indexes after it
//		for (int j = i; j < sizeof(Lines) / sizeof(Lines[i]); j++)
//		{
//			//if they have the same name (via getname finction)
//			if ((*Lines[i]).getName() == (*Lines[j]).getName())
//			{
//				//if different memory location
//				if (Lines[i] != Lines[j])
//				{
//					//Adds second object line to the first object, and points second object index to first object memory location.
//					//Now first and second are merged. If there are more occurances, they will merge with either previous indexes as they are all the same location now.
//					(*Lines[i]).addLine((*Lines[j]).getLine());
//					Lines[j] = Lines[i];
//				}
//			}
//		}
//	}
//
//	//Infinite loop for user input untill command to exit
//	while (loop == 1)
//	{
//		userinput = "";
//		std::cout << "Please enter a command. To see a list of available commands, please enter <help> without chevrons (<>): ";
//		std::cin >> userinput;
//
//		//display list of available functions
//		if (userinput == "help")
//		{
//			std::cout << "<help> : Displays list of user commands." << std::endl << "<exit> : Exits the program." << std::endl << "<showall> : prints all stations available." << std::endl;
//		}
//		//exits the program
//		if (userinput == "exit")
//		{
//			loop = 0;
//		}
//		//prints all stations
//		if (userinput == "showall")
//		{
//			for (int i = 0; i < sizeof(Lines) / sizeof(Lines[0]); i++)
//			{
//				std::cout << *Lines[i];
//			}
//		}
//	}
//}
