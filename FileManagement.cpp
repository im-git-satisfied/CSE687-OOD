#include "FileManagement.h"

// FileManagement Constructor
FileManagement::FileManagement()
{
}

// reads in the contents of the file given
void FileManagement::readFile(std::string path)
{
    // ifstream class object to read the file
    ifstream file;
    string line;

    // read in the file
    file.open(path);
 
    // read the contents of the file until EOF
    while (file) {
 
        // read a Line from the file
        getline(file, line);
        
        // store the contents of the file
        setFileContent(line);
    }
 
    // close the file
    file.close();
}

// returns a vecotor of the contents of the file
vector<string> FileManagement::getFileContent()
{
    return fileContent;
}

// populates a vector with the contents of a file
void FileManagement::setFileContent(string fileLine)
{
    // ensures their exits contents in the line before adding to the vector
    if (fileLine.size() > 0)
    {
        fileContent.push_back(fileLine);
    }
}
