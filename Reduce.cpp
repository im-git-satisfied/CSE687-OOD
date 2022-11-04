#include "Reduce.h"

// Reduce Constuctor
Reduce::Reduce()
{}

// reduce function
std::vector<std::pair<std::string,std::vector<int>>> Reduce::reduce(std::string word, std::vector<int> counts)
{
    int reducedValue = 0;
    for (int i = 0; i < counts.size(); i++)
    {
        reducedValue++;
    }
    // calls the exportReduce function
    fileExport(word,reducedValue);
    return getBuffer();
}

// fileExport that creates the vector to pass to the file management
void Reduce::fileExport(std::string word, int reducedValue)
{
    clearBuffer();
    // create a vector to export out the file management
    std::vector<int> cVec;
    cVec.push_back(reducedValue);
    reduceBuffer.push_back(make_pair(word,cVec));
}

std::vector<std::pair<std::string,std::vector<int>>> Reduce::getBuffer()
{
    return reduceBuffer;
}

void Reduce::clearBuffer()
{
    reduceBuffer.clear();
}

