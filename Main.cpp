#include "Executive.h"
#include <typeinfo>
#include <string>
#include <iostream>


int main(int argc, char *argv[]) {

    Executive *exec = new Executive(argc, argv);
    exec->DEBUG = true;
    exec->start();

}
