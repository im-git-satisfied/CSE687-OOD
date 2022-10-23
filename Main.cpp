#include "Executive.h"
#include <typeinfo>
#include <string>
#include <iostream>

const bool DEBUG = false;

int main(int argc, char *argv[]) {

    Executive *exec = new Executive(argc, argv, DEBUG);
    exec->start();

}
