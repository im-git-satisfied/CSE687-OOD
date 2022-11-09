#include "pch.h"
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
        if (!(token == ""))
        {
            fileExport(token,1);
        }
    }
}

// tokenizer that removes punctuation and make the word lower case
std::string Map::tokenize(std::string token)
{
    // remove any punctuation in the token
    int len = token.size();
    for (int i = 0; i < len; i++)
    {
        if (ispunct((unsigned char)token[i]))
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

std::vector<std::pair<std::string,std::vector<int>>> Map::getWordBuffer()
{
    return wordBuffer;
}

bool Map::checkIsFull()
{
    return isFull;
}
