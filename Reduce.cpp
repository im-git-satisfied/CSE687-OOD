#include "Reduce.h"

// Reduce Constuctor
Reduce::Reduce()
{}

void Reduce::reduce(std::string word, std::vector<int> counts)
{
    int reducedValue = 0;
    for (int i = 0; i < counts.size(); i++)
    {
        reducedValue++;
    }

    exportReduce(word,reducedValue);
}

void Reduce::exportReduce(std::string word, int reducedValue)
{
    std::cout << "(" << word << "," << reducedValue << ")" << std::endl;
    // export out the file management
}