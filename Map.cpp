#include "Map.h"

// Map Constructor
Map::Map()
{
    isFull = false;
}

// map function
void Map::tokenMap(std::string fileName, std::string line)
{
    std::string buffer;
    std::string token;

    std::stringstream ss(line);

    while (ss >> buffer)
    {
        token = tokenize(buffer);
        fileExport(token,1);
    }
}

// tokenizer that removes punctuation and make the word lower case
std::string Map::tokenize(std::string token)
{
    // remove any punctuation in the token
    int len = token.size();
    for (int i = 0; i < len; i++)
    {
        if (ispunct(token[i]))
        {
            token.erase(i--,1);
            len = token.size();
        }
    }

    // convert the token to all lowercase
    transform(token.begin(),token.end(),token.begin(),::tolower);

    return token;
}

// export function
void Map::fileExport(std::string word, int count)
{
    std::vector<int> cVec;
    cVec.push_back(count);
    // add the unique token to the word buffer
    wordBuffer.push_back(make_pair(word,cVec));
    if (wordBuffer.size() == 20)
    {
        // write out to file when the buffer is full
        isFull = true;
    }
}

void Map::clearBuffer()
{
    wordBuffer.clear();
    isFull = false;
}

// /*----< entry point simply invokes its own self-test >-------------*/
// #define Test_MapClass
// #ifdef Test_MapClass

// int main()
// {
// 	std::cout << std::endl << "Testing the Map Class";
// 	std::cout << std::endl << "-----------------------------------------------------------------------" << std::endl;
								  
// 	Map mClass;
	
// 	std::string line = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Nec nam aliquam sem et tortor consequat. Tristique senectus et netus et. Amet porttitor eget dolor morbi.";
//     mClass.tokenMap("sample.txt",line);

//     std::cout << "\n\n";
// }
// #endif

