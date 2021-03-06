/*
    Authors: Anita Garcia, Ana Perez, Eduardo
    Created: December 17th, 2015
    Summary: Creates a class that provides
             the functionality for the simulator
             for the 'JAM' Instruction Set Architecture
*/
#ifndef ASSEMBLY_PROGRAM_H
#define ASSEMBLY_PROGRAM_H
#include <iostream>
#include <cstddef>
#include <unordered_map>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>
using namespace std;

class Program{

    private:
        // array sizes
        static const size_t REGISTER_CAPACITY = 16;
        static const size_t MEMORY_CAPACITY = 32;
        //keeps track of amount used memory and registers
        unsigned int used_memory;
        unsigned int used_registers;


    public:
        pair<bool, int> pairMemory[MEMORY_CAPACITY];
        pair<bool, int> pairRegisters[REGISTER_CAPACITY];

        unordered_map<string, vector<string> > functions;
        Program();
        void setMemo(int pos, int val);
        void setReg(int pos, int val);
        pair<bool, int> retPairM(int pos);
        pair<bool, int> retPairR(int pos);
        void getu(int pos, int val);
        void receive(string r, int val);
        int convert(string s);
        void runLine(string line);
        void cacheFunctions();
        void execute();
        void executeFunction(string opcode);
        void executeFunction(string opcode, string address1);
        void executeFunction(string opcode, string address1, string address2);
        void executeFunction(string opcode, string address1, string address2, string address3);
        void locateFunctionToExecute(string opcode);
        int numberOfAddresses(string opcode);
        // Data Movement
        void get ( string r, string m );    // may be changed to bool for error tracking
        void set ( string m, string r );
        void setr (string r1,string entry);
        //Summary: sets value from regsiter into memory address;
        void swap ( string r1, string r2 );

        // Arithmetic
        void move ( string m2, string m1 );
        void addr ( string r3, string r1, string r2 );
        void addm ( string r1, string m1, string m2 );
        void subr ( string r3, string r1, string r2 );
        void subm ( string r1, string m1, string m2 );
        void multr(string r3, string r2, string r1);
        void multm(string r3, string m1, string m2);
        void divr(string r1, string r2, string r3);
        void divm(string r1, string m1, string m2);
        void incr(string r1); //increment r1(index);
        void decr(string r1);
        void neg(string r1); //negates all values in register
        void less(string r1, string m1, string r2);
        void great(string r1, string m1, string r2);
        void equal(string r1, string m1, string r2);

        // Transfer Control
        void in(string register_address);
        void out(string register_address);
        void goTo(string func_name);
        void whif(string r1, string func_name);

        // Special Opcode
        void peek(string memory_address);
        void sort_array(string m1, string num);
        void clearallr();
        void clearr(string r1);
        void clearm(string m1);
        void halt();

        string toLower(string str);

        bool isValidMemory(unsigned int val);
        // Precondition: Val represents an index location.
        // Summary: checking to see if that memory exists
        // Postcondition: returns true or false depending if its valid.
        bool isValidRegister(unsigned int val);
        // Precondition: Val represents an index location.
        // Summary: checking to see if that register exists
        // Postcondition: returns true or false depending if its valid.

        bool isAvailableMemory(unsigned int val);
        // Precondition: val represents an index location.
        // Summary: Checks to see if pair.first is available (true)
        // Postcondition: returns true or false depending if its available or not.

        bool isAvailableRegister(unsigned int val);
        // Precondition: val represents an index location.
        // Summary: checks to see if pair.first is available(true)
        // Postcondition: returns true or false depending if its available or not.
        void internalDisplay();

};


#endif // ASSEMBLY_PROGRAM_H
