#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

#define END -2

class FileManagement
{
private:
	std::string inputDir;
	std::string intermediateDir;
	std::string outputDir;
	std::unordered_map<std::string, int> inputFiles;

public:
	FileManagement(std::string input, std::string inter, std::string output);
	
	std::string getInputDirectory();
	std::string getIntermediateDirectory();
	std::string getOutputDirectory();	

	std::string readInputFile(std::string filename);
	void writeOutputFile(std::string filename, std::string input);
};

