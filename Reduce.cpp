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

/*----< entry point simply invokes its own self-test >-------------*/
//#define Test_ReduceClass
#ifdef Test_ReduceClass

int main()
{
	std::cout << std::endl << "Testing the Reduce Class";
	std::cout << std::endl << "-----------------------------------------------------------------------" << std::endl;
								  
	Reduce rClass;
    std::string word = "apple";
    std::vector<int> temp;

    temp.push_back(1);
    temp.push_back(1);
    temp.push_back(1);
    temp.push_back(1);
    temp.push_back(1);

    rClass.reduce(word,temp);
	
    std::cout << "\n\n";
}
#endif