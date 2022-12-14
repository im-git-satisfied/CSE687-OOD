#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <vector>
#include <iterator>

class FileManagement
{
private:
	std::string inputDir = "";
	std::string intermediateDir = "";
	std::string outputDir = "";
	std::unordered_map<std::string, int> inputFiles;
	
public:
	FileManagement();
	FileManagement(std::string input, std::string inter, std::string output);
	
	std::string getInputDirectory();
	std::string getIntermediateDirectory();
	std::string getOutputDirectory();	

	void setInputDirectory(std::string name);
	void setIntermediateDirectory(std::string name);
	void setOutputDirectory(std::string name);

	bool verify_directory(std::string directory_name);
	bool verify_file(std::string file_name);
	std::vector<std::string> list_files(std::string directory_name);
	bool create_directory(std::string directory_name);

	bool EndOfFile(std::string file_name);
	bool writeFile(std::vector <std::pair<std::string, std::vector<int>>> data, std::string directory_name, std::string file_name);
	bool writeFileSuccess(std::string directory_name, std::string file_name);
	std::string readFile(std::string directory_name, std::string file_name);
};

