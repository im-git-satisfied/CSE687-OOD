#include "FileManagement.h"

int main()
{
    FileManagement fileManagement;

    // reads in the file from the given path
    fileManagement.readFile("sample.txt");

    // stored vector of the file content
    vector<string> file = fileManagement.getFileContent();

    // prints out the contents of the populated vector
    for (int i = 0; i < file.size(); i++)
    {
        cout << file[i] << endl;
    }
}