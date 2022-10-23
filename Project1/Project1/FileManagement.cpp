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
	
	for (int i = 0; i < data.size(); i++) {
		std::pair<std::string, std::vector<int>> pair = data[i];
		std::string first = pair.first;
		std::vector<int> second = pair.second;

		newfile << "(\"" <<	first << "\", [" << second[0];
		for (int i = 1; i < second.size(); i++) {
			newfile << ", " << second[i];
		}
		newfile << "])" << std::endl;
	}

	return true;
}


/*************** REMOVE, for testing only *************************************************/
//#define Test_FileManagement 
/******************************************************************************************/
/*
#ifdef Test_FileManagement

int main()
{
	std::cout << std::endl << "Testing FileManagement";
	std::cout << std::endl << "-----------------------------------------------------------------------" << std::endl;

	std::string input_directory = "C:\\Users\\Brandon Lee\\Documents\\Syracuse - MS CS\\CIS 687\\CIS 687 Projects\\Project1\\Project1\\TestInput\\DirectoryA";
	std::string output_directory = "C:\\Users\\Brandon Lee\\Documents\\Syracuse - MS CS\\CIS 687\\CIS 687 Projects\\Project1\\Project1\\TestOutput\\";

	FileManagement f1;
	
	f1.setInputDirectory(input_directory);
	f1.setOutputDirectory(output_directory);
	std::cout << f1.getInputDirectory() << std::endl;
	std::cout << f1.getIntermediateDirectory() << std::endl;
	std::cout << f1.getOutputDirectory() << std::endl;

	std::cout << std::endl;

	bool is_dir = f1.verify_directory(input_directory);
	std::cout << is_dir << std::endl;
	is_dir = f1.verify_directory("im garbage and not a valid path");
	std::cout << is_dir << std::endl;

	std::vector<std::string> cur_dir = f1.list_files(input_directory);
	for(std::string entry : cur_dir)
	{
		std::cout << entry << std::endl;
	}

	// reads from a file
	int i = 0;
	std::vector<std::string> read_lines;
	while (!f1.EndOfFile("testA.txt")) {
		read_lines.push_back(f1.readFile(input_directory, "testA.txt"));
		std::cout <<  read_lines[i] << std::endl;
		i++;
	}

	// write to file
	std::vector<int> count_a;
	count_a.push_back(1);
	std::string word_a = "a";

	std::vector<int> count_b;
	count_b.push_back(1);
	count_b.push_back(1);
	count_b.push_back(1);
	count_b.push_back(1);
	count_b.push_back(1);
	count_b.push_back(1);
	std::string word_b = "b";

	std::vector<int> count_c;
	count_c.push_back(1);
	count_c.push_back(1);
	count_c.push_back(1);
	count_c.push_back(1);
	count_c.push_back(1);
	count_c.push_back(1);
	count_c.push_back(1);
	count_c.push_back(1);
	std::string word_c = "c";


	std::vector <std::pair<std::string, std::vector<int>>> output_lines;
	output_lines.push_back(std::pair<std::string, std::vector<int>>(word_a, count_a));
	output_lines.push_back(std::pair<std::string, std::vector<int>>(word_b, count_b));
	output_lines.push_back(std::pair<std::string, std::vector<int>>(word_c, count_c));
	bool success = f1.writeFile(output_lines, output_directory, "outputA.txt");


	std::cout << "\n\nEnd of Main\n\n";
}
#endif
*/


