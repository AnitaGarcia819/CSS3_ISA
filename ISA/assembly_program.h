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
        static const size_t REGISTER_CAPACITY = 16;
        static const size_t MEMORY_CAPACITY = 32;
        unsigned int used_memory;
        unsigned int used_register;
        pair<bool,int> pairRegisters[REGISTER_CAPACITY];
        pair<bool,int> pairMemory[MEMORY_CAPACITY];

        set<int> so;

    public:
        unordered_map<string, vector<string> > functions;
        Program();
        int convert(string s);
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
        void whif(string func_name, string r1);

        // Special Opcode
        void peek(string memory_address);
        void sort_array(string m1, string num);
        void clearr(string r1);
        void clearm(string m1);
        void halt();


        string toLower(string str);
};



#endif // ASSEMBLY_PROGRAM_H
