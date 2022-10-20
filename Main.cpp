#include "Map.h"
#include "FileManagement.h"
#include "Reduce.h"


int main()
{
    std::string input_directory = "/Users/damiomitaomu/Documents/Git/CSE687-OOD/input1";
    FileManagement f1(input_directory,"/Users/damiomitaomu/Documents/Git/CSE687-OOD/test1","/Users/damiomitaomu/Documents/Git/CSE687-OOD/output1");
    Map m;

    std::vector<std::string> flist = f1.list_files(f1.getInputDirectory());
    for(std::string f : flist)
    {        
        std::cout << f << std::endl;
        // reads from a file
        int i = 0;
        std::vector<std::string> read_lines;
        while (!f1.EndOfFile(f)) {
            read_lines.push_back(f1.readFile(input_directory, f));
            // std::cout <<  read_lines[i] << std::endl;
            m.tokenMap(f,read_lines[i]);
            i++;

            if (m.isFull)
            {
                f1.writeFile(m.wordBuffer,f1.getIntermediateDirectory(),"test.txt");
                m.clearBuffer();
            }
        }
    }

}