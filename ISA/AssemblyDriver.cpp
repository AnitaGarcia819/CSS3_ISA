/*
    Authors: Anita Garcia, Ana Perez, Eduardo
    Created: December 17th, 2015
    Summary: Driver file that tests
             simulator for the 'JAM' Instruction
             Set Architecture.
*/
#include "assembly_program.h"
#include <vector>
#include <unordered_map>
using namespace std;
int main()
{
    Program program;

    program.cacheFunctions();
    program.execute();

    return 0;
}

