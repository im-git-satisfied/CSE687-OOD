#include "FileManagement.h"
#include "Map.h"

int main()
{
    FileManagement fileManagement;
    Map wordMap;

    // reads in the file from the given path
    fileManagement.readFile("sample.txt");

    // stored vector of the file content
    vector<string> fileContent = fileManagement.getFileContent();

    // prints out the contents of the populated vector
    for (int i = 0; i < fileContent.size(); i++)
    {
        wordMap.tokenMap("sample.txt",fileContent[i]);
    }

}