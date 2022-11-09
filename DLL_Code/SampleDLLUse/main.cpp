

#include <iostream>
#include <string>
#include "MapInterface.h"
#include "ReduceInterface.h"

					//general interface
					/* 
					* Create an interface of Map that has all virtual functions, possible future extensibility
					* Create an interface of Reduce that has all virtual functions, possibel future extensibility
					* Have Map in its own DLL	
					* Have Reduce in its own DLL
					* Wrap Map in a Factory so it can be extern C
					* Wrap Reduce in a Factory so it can be extern C					
					* LoadLibrary of Map dll
					* LoadLibrary of Reduce dll
					* typedef pointer to Map base class
					* typedef pointer to Reduce base class
					* 
					* https://neutrofoton.github.io/blog/2017/09/14/create-and-consume-c-plus-plus-class-dll-on-windows/
					*/

#include <Windows.h>

//Function* is the type to our interface class
typedef MapInterface* (__cdecl *MapFactory)();
typedef ReduceInterface* (__cdecl* ReduceFactory)();

int testMap(HINSTANCE dll);
int testReduce(HINSTANCE dll);

int testMap(HINSTANCE map_dll) {

	MapFactory mapfactory = (MapFactory)GetProcAddress(map_dll, "CreateMap");

	if (NULL != mapfactory) {
		std::cout << "Yay map DLL ";

		//Testing BuildTokenMap----------------
		std::string fileName = "test";
		std::string line = "this is a test";
		MapInterface* map_instance = mapfactory();
		map_instance->tokenMap(fileName, line);

		std::cout << "size 4 = " << map_instance->getWordBuffer().size() << " ";
		//-------------------------------------

		map_instance->Destroy();
		return 1;
	}
	else {
		std::cout << "Nay map DLL ";
		return 0;
	}
}

int testReduce(HINSTANCE reduce_dll) {

	ReduceFactory reducefactory = (ReduceFactory)GetProcAddress(reduce_dll, "CreateReduce");

	if (NULL != reducefactory) {
		std::cout << "Yay reduce DLL ";

		ReduceInterface* reduce_instance = reducefactory();
		std::string word = "test";
		std::vector<int> counts;
		counts.push_back(1);
		counts.push_back(1);
		counts.push_back(1);
		counts.push_back(1);
		counts.push_back(1);
		counts.push_back(1);
		counts.push_back(1);
		counts.push_back(1);
		std::vector<std::pair<std::string, std::vector<int>>> tVec;

		tVec = reduce_instance->reduce(word, counts);
		std::cout << "size 1 = " << tVec.size() << ", test = " << tVec[0].first << ", count of 8 = " << tVec[0].second[0] << ", ";

		reduce_instance->Destroy();
		return 1;
	}
	else {
		std::cout << "Nay reduce DLL ";
		return 0;
	}
}

int main() {
	
	std::cout << "Program starting up" << std::endl;

	HINSTANCE map_dll;
	HINSTANCE reduce_dll;

	map_dll = LoadLibrary(L"..\\..\\MapDLL\\x64\\Debug\\MapDLL.dll");
	reduce_dll = LoadLibrary(L"..\\..\\ReduceDLL\\x64\\Debug\\ReduceDLL.dll");

	if (!map_dll) {
		std::cout << "Failed to load map library" << std::endl;
		exit(1);
	}

	if (!reduce_dll) {
		std::cout << "Failed to load map library" << std::endl;
		exit(1);
	}

	std::cout << "Result: " << testMap(map_dll) << std::endl;

	std::cout << "Result: " << testReduce(reduce_dll) << std::endl;

	FreeLibrary(reduce_dll);
	FreeLibrary(map_dll);

	std::cout << "Closing..." << std::endl;

	return 0;
}