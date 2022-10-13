#include "FileManagement.h"

#include <iostream>

FileManagement::FileManagement()
{
	std::cout << "Creating FileManagement Class" << std::endl;
}

/*----< entry point simply invokes its own self-test >-------------*/
#ifdef Test_FileManagement

int main()
{
	std::cout << "\n  testing FileManagement";
	std::cout << "\n --------------------------------------------------------------------------------";

	FileManagement f1;
	
	std::cout << "\n\n";
}
#endif
