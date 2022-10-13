#include "Map.h"

// Map Constructor
Map::Map()
{
}

// map function
void Map::tokenMap(string fileName, string line)
{
    string buffer;
    string token;

    stringstream ss(line);

    while (ss >> buffer)
    {
        token = tokenize(buffer);
        // iterates through the map to see if the distinct token exists
        map<string,int>::iterator it = wordCount.find(token);
        if (it != wordCount.end())
        {
            // increments the count of a unique token
            it->second++;
        }
        else
        {
            // add the unique token to the map
            wordCount.insert(make_pair(token,1));
        }
    }
    
    // prints the contents of the map
    for ( map<string,int>::iterator it = wordCount.begin(); it != wordCount.end(); it++)
    {
        cout << "(" << it->first << "," << it->second << ")" << endl;
    }

}

// tokenizer that removes punctuation and make the word lower case
string Map::tokenize(string token)
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

// export function???
void Map::fileExport()
{

}

