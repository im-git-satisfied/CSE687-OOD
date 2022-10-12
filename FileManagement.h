#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Creation of the FileManagement Class
class FileManagement
{
    public:
        explicit FileManagement();
        void readFile(string path);
        vector<string> getFileContent();
        void setFileContent(string fileLine);
    
    private:
        vector<string> fileContent;

};