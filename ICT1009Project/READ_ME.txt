IF HAVING ERROR: 
1. LNK1104	cannot open file 'include/telecurlx32/libcurl_a_debug.lib'	
Solutuon: 
	1. Go to project Project --> "Project_Name" properties --> Linker --> Input
	2. Ensure Configuration is Debug and Platform is Win32
	3. Additional Dependencies --> Add the path --> "FOLDER PLAT NAME"\libcurl_a_debug.lib
		e.g. C:\Users\alfred ng\source\repos\1009\ICT1009Project\include\telecurlx32\libcurl_a_debug.lib
	4. Ensure Configuration is Release and Platform is Win32
	5.  Additional Dependencies --> Add the path --> "FOLDER PLAT NAME"\libcurl_a.lib
		e.g. C:\Users\alfred ng\source\repos\1009\ICT1009Project\include\telecurlx32\libcurl_a.lib

