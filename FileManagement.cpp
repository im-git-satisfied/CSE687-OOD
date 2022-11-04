#include "FileManagement.h"

FileManagement::FileManagement() 
{
	std::cout << "Creating FileManagement Class" << std::endl;
}

// Constructor that takes 3 arguments (input, intermediate, and output) directory paths
FileManagement::FileManagement(std::string input, std::string inter, std::string output)
	: inputDir(input), intermediateDir(inter), outputDir(output)
{
	std::cout << "Creating FileManagement Class" << std::endl;
}

// return input directory path
std::string FileManagement::getInputDirectory()
{
	return inputDir;
}

// return intermediate directory path
std::string FileManagement::getIntermediateDirectory()
{
	return intermediateDir;
}

// return output directory path
std::string FileManagement::getOutputDirectory()
{
	return outputDir;
}

// sets the input directory
void FileManagement::setInputDirectory(std::string name) 
{
	inputDir = name;
}

// sets the intermediate put directory
void FileManagement::setIntermediateDirectory(std::string name)
{
	intermediateDir = name;
}

// sets the output directory
void FileManagement::setOutputDirectory(std::string name)
{
	outputDir = name;
}

// create directory as specified
bool FileManagement::create_directory(std::string directory_name) {
	return std::filesystem::create_directory(directory_name);
}

// Verify path is a valid directory
bool FileManagement::verify_directory(std::string directory_name) 
{
	return std::filesystem::is_directory(directory_name);
}

// Return vector of files/directories from the given directory path
std::vector<std::string> FileManagement::list_files(std::string directory_name) 
{
	std::vector<std::string> files;
	
	for (auto& entry : std::filesystem::directory_iterator(directory_name)) {
		files.push_back(entry.path().filename().string());
	}

	return files;
}

// Check if the file is at EOF
bool FileManagement::EndOfFile(std::string filename)
{
	if (inputFiles[filename] == -1) {
		inputFiles[filename] = 0;
		return true;
	}
	else {
		return false;
	}
	return (inputFiles[filename] == -1) ? true : false;
}

// reads a line from the specified directory and file name
std::string FileManagement::readFile(std::string directory, std::string filename)
{
	#ifdef _WIN64
		if (directory.back() != '\\') {
			directory = directory + '\\';
		}
	#elif _WIN32
		if (directory.back() != '\\') {
			directory = directory + '\\';
		}
	#elif __APPLE__
		if (directory.back() != '/') {
			directory = directory + '/';
		}
	#elif __linux
		if (directory.back() != '/') {
			directory = directory + '/';
		}
	#endif

	std::string cur_file = directory + filename;
	std::ifstream newfile;
	int position = 0;
	auto result = inputFiles.find(filename);
	
	//file has been read, find position and continue
	if (result != inputFiles.end()) {		
		position = inputFiles[filename];
	}

	//reads a line from the input file
	std::string line;
	newfile.open(cur_file);
	if (newfile.is_open()) {
		newfile.seekg(position);
		getline(newfile, line);
	}
	
	//store the position in the unorderd map, if seek position is end of file, tellg() returns -1
	inputFiles[filename] = newfile.tellg();

	return line;
}

// if file exists, it will append each input as its own row
// ("a", [1, 1, …])
// ("the", [1, 1, …])
// ("is", [1, …])
bool FileManagement::writeFile(std::vector <std::pair<std::string, std::vector<int>>> data, std::string directory, std::string filename)
{
	#ifdef _WIN64
		if (directory.back() != '\\') {
			directory = directory + '\\';
		}
	#elif _WIN32
		if (directory.back() != '\\') {
			directory = directory + '\\';
		}
	#elif __APPLE__
		if (directory.back() != '/') {
			directory = directory + '/';
		}
	#elif __linux
		if (directory.back() != '/') {
			directory = directory + '/';
		}
	#endif

	std::string cur_file = directory + filename;
	std::ofstream newfile;
	newfile.open(cur_file, std::ofstream::app);
	if (newfile.is_open()) {
		for (int i = 0; i < data.size(); i++) {
			std::pair<std::string, std::vector<int>> pair = data[i];
			std::string first = pair.first;
			std::vector<int> second = pair.second;

			newfile << "(\"" << first << "\", [" << second[0];
			for (int i = 1; i < second.size(); i++) {
				newfile << ", " << second[i];
			}
			newfile << "])" << std::endl;
		}
		return true;
	}
	
	return false;
}

bool FileManagement::writeFileSuccess(std::string directory, std::string filename)
{
	#ifdef _WIN64
		if (directory.back() != '\\') {
			directory = directory + '\\';
		}
	#elif _WIN32
		if (directory.back() != '\\') {
			directory = directory + '\\';
		}
	#elif __APPLE__
		if (directory.back() != '/') {
			directory = directory + '/';
		}
	#elif __linux
		if (directory.back() != '/') {
			directory = directory + '/';
		}
	#endif

	std::string cur_file = directory + filename;
	std::ofstream newfile;
	newfile.open(cur_file, std::ofstream::app);
	if (newfile.is_open()) {
		return true;
	}
	return false;
}

