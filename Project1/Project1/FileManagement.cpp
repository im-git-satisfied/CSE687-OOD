#include "FileManagement.h"
#include <filesystem>
#include <iomanip>

// Constructor that takes 3 arguments (input, intermediate, and output) directory paths
FileManagement::FileManagement(std::string input, std::string inter, std::string output)
	: inputDir(input), intermediateDir(inter), outputDir(output)
{
	std::cout << "Creating FileManagement Class" << std::endl;

	//need to add filesystem check for valid directory paths from user input?????
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

// reads a line from the specified input file
std::string FileManagement::readInputFile(std::string filename)
{
	std::string cur_file = inputDir + filename;

	// Check if valid file
	if (!std::filesystem::is_regular_file(cur_file)) {
		return "Error: Not valid file.";
	}

	std::ifstream newfile;
	int position = 0;
	auto result = inputFiles.find(filename);
	
	//file has been read, find position and continue
	if (result != inputFiles.end()) {		
		position = inputFiles[filename];
		if (position == END) {
			return "Error: File has been read.";
		}
	}

	//reads a line from the input file
	std::string line;
	newfile.open(cur_file);
	newfile.seekg(position);
	if (!getline(newfile, line)) {
		inputFiles[filename] = END;
		return "Error: End of File.";
	}

	//store the position in the unorderd map
	inputFiles[filename] = newfile.tellg();

	return line;
}

// writes input to given output file
void FileManagement::writeOutputFile(std::string filename, std::string input)
{

}

/*----< entry point simply invokes its own self-test >-------------*/
#define Test_FileManagement
#ifdef Test_FileManagement

int main()
{
	std::cout << std::endl << "Testing FileManagement";
	std::cout << std::endl << "-----------------------------------------------------------------------" << std::endl;

	std::string input_directory = "C:\\Users\\Brandon Lee\\Documents\\Syracuse - MS CS\\CIS 687\\CIS 687 Projects\\Project1\\Project1\\TestInput\\";
								  
	FileManagement f1(input_directory, "intermediatedirectory", "outputdirectory");
	
	std::cout << f1.getInputDirectory() << std::endl;
	std::cout << f1.getIntermediateDirectory() << std::endl;
	std::cout << f1.getOutputDirectory() << std::endl;

	std::cout << std::endl;
	std::cout << std::setw(30) << "hello this is file A" << std::setw(30) << f1.readInputFile("fileA.txt") << std::endl;
	std::cout << std::setw(30) << "this" << std::setw(30) << f1.readInputFile("fileA.txt") << std::endl;
	std::cout << std::setw(30) << "The best of the best" << std::setw(30) << f1.readInputFile("fileB.txt") << std::endl;
	std::cout << std::setw(30) << "bees knees" << std::setw(30) << f1.readInputFile("fileB.txt") << std::endl;
	std::cout << std::setw(30) << "is a test" << std::setw(30) << f1.readInputFile("fileA.txt") << std::endl;
	std::cout << std::setw(30) << "file for reading" << std::setw(30) << f1.readInputFile("fileA.txt") << std::endl;
	std::cout << std::setw(30) << "End of File" << std::setw(30) << f1.readInputFile("fileA.txt") << std::endl;
	std::cout << std::setw(30) << "Error File has been read" << std::setw(30) << f1.readInputFile("fileA.txt") << std::endl;
	std::cout << std::setw(30) << "bellowing birds beach ball" << std::setw(30) << f1.readInputFile("fileB.txt") << std::endl;
	std::cout << std::setw(30) << "End of File" << std::setw(30) << f1.readInputFile("fileB.txt") << std::endl;
	std::cout << std::setw(30) << "Error File has been read" << std::setw(30) << f1.readInputFile("fileB.txt") << std::endl;



	std::cout << "\n\n";
}
#endif


