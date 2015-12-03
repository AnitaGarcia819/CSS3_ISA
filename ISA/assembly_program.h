#ifndef ASSEMBLY_PROGRAM_H
#define ASSEMBLY_PROGRAM_H
#include <iostream>
#include <cstddef>
using namespace std;
class Program{

    private:
        // array sizes
        static const size_t REGISTER_CAPACITY = 16;
        static const size_t MEMORY_CAPACITY = 32;
        //keeps track of amount used memory and registers
        unsigned int used_memory;
        unsigned int used_registers;
        pair<bool, int> pairRegisters[REGISTER_CAPACITY];
        pair<bool, int> pairMemory[MEMORY_CAPACITY];

    public:
        Program();
        int convert(string s);
        void execute();
        // Data Movement
        void get ( string r, string m );    // may be changed to bool for error tracking
        void set ( string m, string r );
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
        bool less(string r1, string m1, string m2);
        bool great(string r1, string m1, string m2);
        bool equal(string r1, string m1, string m2);

        // Transfer Control
        void in(string register_address);
        void out(string register_address);
        void goTo(string func_name);
        void whif(string func_name);

        // Special Opcode
        void peek(string memory_address);
        void sort(string m1, string num);
        void clearr(string r1);
        void clearm(string m1);
        void halt();


        bool isValidMemory(int val);
        // Precondition: Val represents an index location.
        // Summary: checking to see if that memory exists
        // Postcondition: returns true or false depending if its valid.
        bool isValidRegisters(int val);
        // Precondition: Val represents an index location.
        // Summary: checking to see if that register exists
        // Postcondition: returns true or false depending if its valid.

        bool isAvailableMemory(int val);
        // Precondition: val represents an index location.
        // Summary: Checks to see if pair.first is available (true)
        // Postcondition: returns true or false depending if its available or not.

        bool isAvailableRegister(int val);
        // Precondition: val represents an index location.
        // Summary: checks to see if pair.first is available(true)
        // Postcondition: returns true or false depending if its available or not.

};
#endif // ASSEMBLY_PROGRAM_H
