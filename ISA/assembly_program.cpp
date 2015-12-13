#include <fstream>
#include <cassert>
#include <set>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "assembly_program.h"
using namespace std;
Program::Program()
{
    used_memory = 0;
    used_registers = 0;
    for(unsigned int i = 0; i < MEMORY_CAPACITY; i++)
    {
        pairMemory[i] = make_pair(true, 0);
    }
    for(unsigned int i = 0; i <REGISTER_CAPACITY; i++)
    {
        pairRegisters[i] = make_pair(true, 0);
    }
}

void Program::setMemo(int pos, int val)
{
    pairMemory[pos].second = val;
    pairMemory[pos].first = false;
}

int Program::convert(string s)
{
    int new_val;
    if(isdigit(s[0]))
    {
        new_val = atoi(s.c_str());
        return new_val;
    }
    else if(isalpha(s[0]))
    {
        string val = s.substr(1);
        new_val = atoi(val.c_str());
        return new_val;
    }
    // An error message can be added here...
    // "the value entered is invalid, + string s"
    //TODO: fix warning issue here
}
void Program::cacheFunctions()
{
    int number_of_addresses;
    int opcode_length, index;
    string new_line;
    string line, func_name, opcode, address1, address2, address3;
    fstream fin;
    fin.open("/Users/anitagarcia/CSS3_ISA/ISA/isa.txt");
    if(fin.fail())
        cout << "File is not valid " << endl;
    while(fin.good())
    {
        func_name = "";
        // Read in opcode
        getline(fin, line);
        if(line[0] != '#')
        {
             // Check if it's a function
             if(line[0] == '*')
             {
                // Parses function name from line (including the number after the func_name)
                for(int i = 1; i < line.length(); i++)
                {
                    if(!(isspace(line[i])))
                        func_name += line[i];
                    else
                        break;
                }
                //cout << "FUNC NAME: (with num): " << func_name << endl;
                // Number of vector length
                int vector_number = func_name[func_name.length() - 1] - '0';
                //cout << "VECTOR NUM: " << vector_number << endl;
               //  func_name without the vector number
                func_name = func_name.substr(0,func_name.length() - 1);
              //  cout << "FUNC_NAME: (w.o number) " << func_name << endl;
                vector<string> vec;
                // Add instructions into vector
                for(int i = 0; i < vector_number; i++)
                {
                    getline(fin, line);
                    vec.push_back(line);

                }
                // put function into hashtable
                pair< string, vector<string> > p;
                p.first = func_name;
                p.second = vec;

                functions.insert(p);

                vector<string>::iterator it;
                for(it = vec.begin(); it != vec.end(); it++)
                    cout << "VEC " << *it << endl;
             }
        }
    }
    fin.close();
    //cout << "HASH TABLE SIZE: " << functions.size() << endl;
}
void Program::execute()
{
    int number_of_addresses;
    int opcode_length, index;
    string new_line;
    string line, func_name, opcode, address1, address2, address3;
    fstream fin;
    fin.open("/Users/anitagarcia/CSS3_ISA/ISA/isa.txt");
    if(fin.fail())
        cout << "File is not valid " << endl;
    while(fin.good())
    {
        // Read in opcode
        getline(fin, line);
        if(line[0] != '#')
        {
             // Check if it's a function
             if(line[0] != '*')
             {
                // Skip functino and run next line
               // getline(fin, line);
               // cout << "Line (execute) " << line << endl;
                //cout << "Line Len (execute) " << line.length() << endl;
                cout << "##INSTRUCTION## " << line << endl;
                runLine(line);
                internalDisplay();
             }
        }
    }
}
void Program::runLine(string line)
{
       // cout << "+++LINE (runLine)" << line << endl;
       // cout << "+++LINE LEN" << line.length() << endl;
        string opcode, address1, address2, address3;
        int opcode_length = 0;
        int op_start_index = 0;
        int number_of_addresses = 0;

        // Find first alpha
        for(int i = 0; i < line.length(); i++)
        {
            if(isalpha(line[i]))
            {
                op_start_index = i;
                break;
            }
        }
        // Creates new line starting at op_start_index
        line = line.substr(op_start_index);
        for(int i = 0; i < line.length(); i++)
        {
            if((!isspace(line[i])))
                {
                    opcode += line[i];
                    opcode_length++;
                }
            else
                break;
        }
         // TODO: check to see if opcode is a function
                //cout << "OPCODE (runLine) " << opcode << endl;
                number_of_addresses = numberOfAddresses(opcode);
                //cout << "NUM OF ADD " << number_of_addresses << endl;
                switch(number_of_addresses)
                {
                    case 3:
                        //cout << "Line:(case) " << line << endl;
                        address1 = line.substr(opcode_length + 1, 3);
                        //cout << "Address 1: " << address1 << endl;
                        address2 = line.substr(opcode_length + 5, 3);
                        //cout << "Address 2: " << address2 << endl;
                        address3 = line.substr(opcode_length + 9, 3);
                        //cout << "Address 3: " << address3 << endl;
                        executeFunction(opcode, address1, address2, address3);
                        break;
                    case 2:
                        if(toLower(opcode) == "whif")
                        {
                            address1 = line.substr(opcode_length + 1, 3);
                            address2 = line.substr(opcode_length + 5);
                        }
                        else if(toLower(opcode) == "setr")
                        {
                            address1 = line.substr(opcode_length + 1, 3);
                            address2 = line.substr(opcode_length + 5);
                        }
                        else
                        {
                            address1 = line.substr(opcode_length + 1, 3);
                            address2 = line.substr(opcode_length + 5, 3);
                        }
                        executeFunction(opcode, address1, address2);

                        break;
                    case 1:
                        {
                           // cout << "CASE 1: " << opcode << endl;
                            address1 = line.substr(opcode_length + 1, 3);
                            executeFunction(opcode, address1);
                        }

                        break;
                    case 0:
                        executeFunction(opcode);
                        break;
                }
}
void Program::executeFunction(string opcode)
{
    if(toLower(opcode) == "halt")
       exit(0);
    else if(toLower(opcode) == "clearallr")
        clearallr();

}

void Program::executeFunction(string opcode, string address1)
{
    if(toLower(opcode) == "incr")
        incr(address1);
    else if(toLower(opcode)== "decr")
        decr(address1);
    else if(toLower(opcode) == "neg")
        neg(address1);
    else if(toLower(opcode) == "in")
        in(address1);
    else if(toLower(opcode) == "out")
        out(address1);
    else if(toLower(opcode) == "goto")
        goTo(address1);
    else if(toLower(opcode) == "peek")
        peek(address1);
    else if(toLower(opcode) == "clearr")
        clearr(address1);
    else if(toLower(opcode)== "clearm")
        clearm(address1);
}

void Program::executeFunction(string opcode, string address1, string address2)
{
    if(toLower(opcode) == "get")
        get(address1, address2);
    else if(toLower(opcode) == "set")
        set(address1, address2);
    else if(toLower(opcode) == "setr")
        setr(address1, address2);
    else if(toLower(opcode) == "swap")
        swap(address1, address2);
    else if(toLower(opcode) == "move")
        move(address1, address2);
    else if(toLower(opcode) == "whif")
    {
        cout << "EXECUTE FUNC WHIF " << endl;
          whif(address1, address2);
    }

    else if(toLower(opcode) == "sort")
        sort_array(address1, address2);
}
void Program::executeFunction(string opcode, string address1, string address2, string address3)
{
    if(toLower(opcode) == "addr")
        addr(address1, address2, address3);
    else if(toLower(opcode) == "addm")
        addm(address1, address2, address3);
    else if(toLower(opcode) == "subr")
        subr(address1, address2, address3);
    else if(toLower(opcode) == "subm")
        subm(address1, address2, address3);
    else if(toLower(opcode) == "multr")
       multr(address1, address2, address3);
    else if(toLower(opcode) == "multm")
        multm(address1, address2, address3);
    else if(toLower(opcode) == "divr")
        divr(address1, address2, address3);
    else if(toLower(opcode) == "divm")
        divm(address1, address2, address3);
    else if(toLower(opcode) == "less")
        less(address1, address2, address3);
    else if(toLower(opcode) == "great")
        great(address1, address2, address3);
    else if(toLower(opcode) == "equal")
        equal(address1, address2, address3);
}
int Program::numberOfAddresses(string opcode)
{
        // OPCODE w/ zero addresses
        if(toLower(opcode) == "halt")
           return 0;
        if(toLower(opcode) == "clearallr")
            return 0;

        // OPCODE w/ one addresses
        else if(toLower(opcode) == "incr")
                return 1;
        else if(toLower(opcode) == "decr")
                return 1;
        else if(toLower(opcode) == "neg")
                return 1;
        else if(toLower(opcode) == "in")
                return 1;
        else if(toLower(opcode) == "out")
                return 1;
        else if(toLower(opcode) == "goto")
                 return 1;
        else if(toLower(opcode) == "peek")
                 return 1;
        else if(toLower(opcode) == "clearr")
                 return 1;
        else if(toLower(opcode) == "clearm")
                 return 1;

        // OPCODE w/ two addresses
        if(toLower(opcode) == "get")
             return 2;
        else if(toLower(opcode) == "set")
            return 2;
        else if(toLower(opcode) == "setr")
            return 2;
        else if(toLower(opcode) == "swap")
             return 2;
        else if(toLower(opcode) == "move")
             return 2;
        else if(toLower(opcode) == "whif")
             return 2;
        else if(toLower(opcode) == "sort")
             return 2;
        // OPCODE w/ three addresses
        else if(toLower(opcode) == "addr")
            return 3;
        else if(toLower(opcode) == "addm")
            return 3;
        else if(toLower(opcode) == "subr")
            return 3;
        else if(toLower(opcode) == "subm")
            return 3;
        else if(toLower(opcode) == "multr")
            return 3;
        else if(toLower(opcode) == "multm")
            return 3;
        else if(toLower(opcode) == "divr")
            return 3;
        else if(toLower(opcode) == "divm")
            return 3;
        else if(toLower(opcode) == "less")
            return 3;
        else if(toLower(opcode) == "great")
            return 3;
        else if(toLower(opcode) == "equal")
            return 3;
}
// Data movement >>> add Program before every function
void Program::get(string r, string m)
{
  int reg = convert(r);
  int memo = convert(m);
  if(isValidRegister(reg) && isValidMemory(memo))
    {
        pairRegisters[reg].second = pairMemory[memo].second;
        pairRegisters[reg].first = false;
    }
}
void Program::setr(string r1,string entry) // new name "setR"
{
    int reg_index = convert(r1);
    int value = convert(entry);
    cout << "!!!VALUE!!" << value << endl;
    if(isValidRegister(reg_index))
    {
        pairRegisters[reg_index].second = value;
        pairRegisters[reg_index].first = false;
    }
}

void Program::set(string m, string r)
{
    int memory_index = convert(m);
    int reg_index = convert(r);
    if(isValidRegister(reg_index)
         && isValidMemory(memory_index))
    {
        pairMemory[memory_index].second = pairRegisters[reg_index].second;
        pairMemory[memory_index].first = false;
    }
}
void Program::swap(string r1, string r2) // <
{
  int reg1_index = convert(r1);  	 // At this moment we are storing integers in memory
  int reg2_index = convert(r2);  	 // that uses the integers stored in memory and translates
  if((isValidRegister(reg1_index) && (isValidRegister(reg2_index))))
    {
          // swap contents of second
      int temp_reg;
      temp_reg = pairRegisters[reg1_index].second;
      pairRegisters[reg1_index].second = pairRegisters[reg2_index].second;
      pairRegisters[reg2_index].second = temp_reg;

      // swap contents of first
      bool temp;
      temp = pairRegisters[reg1_index].first;
      pairRegisters[reg1_index].first = pairRegisters[reg2_index].first;
      pairRegisters[reg2_index].second = temp;
    }
}
void Program::move(string m2, string m1)
{
    int memory1_index = convert(m1);
    int memory2_index = convert(m2);

    if(isValidMemory(memory1_index) && isValidMemory(memory2_index))
    {
        pairMemory[memory2_index].second = pairMemory[memory1_index].second;
        pairMemory[memory2_index].first = false;
    }
}
void Program::addr(string r3, string r1, string r2)
{
  int reg1 = convert(r1);
  int reg2 = convert(r2);
  int reg3 = convert(r3);
  if(isValidRegister(reg3) && isValidRegister(reg2) && isValidRegister(reg1))
  {
        pairRegisters[reg3].second = pairRegisters[reg1].second + pairRegisters[reg2].second;
        pairRegisters[reg3].first = false;
  }
}

void Program::addm(string r1, string m1, string m2)
{
    int reg1 = convert(r1);
    int memo1 = convert(m1);// convert string
    int memo2 = convert(m2);// convert string
    if(isValidRegister(reg1) && isValidMemory(memo1) && isValidMemory(memo2))
    {
          pairRegisters[reg1].second = pairMemory[memo1].second + pairMemory[memo2].second;
          pairRegisters[reg1].first = false;
    }
}
void Program::subr(string r3, string r1, string r2)
{
    int reg1 = convert(r1);
    int reg2 = convert(r2);
    int reg3 = convert(r3);
    if(isValidRegister(reg1) && isValidRegister(reg2) && isValidRegister(reg3))
    {
        pairRegisters[reg3].second = pairRegisters[reg1].second - pairRegisters[reg2].second;
        pairRegisters[reg3].first = false;
    }
}
void Program::subm(string r1, string m1, string m2)
{
    // convert
    int reg1 = convert(r1);
    int memory1 = convert(m1);
    int memory2 = convert(m2);

    if(isValidMemory(memory1) && isValidMemory(memory2) && isValidRegister(reg1))
    {
        pairRegisters[reg1].second = pairMemory[memory1].second - pairMemory[memory2].second;
        pairRegisters[reg1].first = false;
     }
}
//arithmetic functions
void Program::multr(string r3, string r2, string r1)
{
    //convert r1 and r2
    int val1 = convert(r1);
    int val2 = convert(r2);
    int val3 = convert(r3);

    //makes sure that the register location is valid and available
    if(isValidRegister(val1) && isValidRegister(val2) && isValidRegister(val3))
	{
    		pairRegisters[val3].second = pairRegisters[val1].second * pairRegisters[val2].second;
    		pairRegisters[val3].first = false; //not available anymore
	}
	 else
        cout << "Not available Register: " << val3 << endl;
    cout << "Result: " << pairRegisters[val3].second ;
}
void Program::multm(string r3, string m1, string m2)
{
	//convert m1 and m2 to ints
	int val1 = convert(m1);
	int val2 = convert(m2);
	int val3 = convert(r3);

	//assert(isValidMemory(val3));
	//assert(isAvailableRegister(val3));
	if(isValidMemory(val3))
    {
        pairRegisters[val3].second = val1*val2;
        pairRegisters[val3].first = false; //not available anymore.
    }
    else
        cout << "Memory " << val3 << " not available or not valid" << endl;
}
void Program::divr(string r1, string r2, string r3)
{
	//convert r1 and r2 to ints
	int val1 = convert(r1);
	int val2 = convert(r2);
	int val3 = convert(r3);

	//assert(isValidRegister(val3));
	//assert(isAvailableRegister(val3));
	if(isValidMemory(val3))
    {
        pairRegisters[val3].second = val1 / val2;
        pairRegisters[val3].first = false; // not available anymore.
    }
    else
        cout << "Register location: " << val3 << " not available or not valid " << endl;

}
void Program::divm(string r1, string m1, string m2)
{
	//convert m1 and m2
	int val1 = convert(m1);
	int val2 = convert(m2);
	int val3 = convert(r1);

	//assert(isValidRegister(val3));
	//assert(isAvailableRegister(val3));
	if(isValidRegister(val3))
    {
        pairRegisters[val3].second = val1/val2;
        pairRegisters[val3].first = false; // not available anymore.
    }
    else
        cout << "Register location: " << val3 << " not available or not valid " << endl;
}

void Program::incr(string r1) //increment r1(index)
{
	//convert r1 to int;
	int val1 = convert(r1);
	if(isValidRegister(val1))
        pairRegisters[val1].second += 1;
    //you need to set it to no available anymore and make sure that you can still increment +1 whenever you want.
    else
        cout << "Register: " << val1 << " not available or valid " << endl;
}

void Program::decr(string r1)
{
	//convert r1 to int;
	int val1 = convert(r1);
	//assert(isAvailableRegister(val1));
	//assert(isValidRegister(val1));
	if(isValidRegister(val1))
        pairRegisters[val1].second -= 1;
    else
        cout << "Register: " << val1 << " not available or valid " << endl;
    //you need to set it to no available anymore and make sure that you can still increment +1 whenever you want.
}
void Program::neg(string r1) //negates all values in register
{
	//convert r1 to int
	int val1 = convert (r1);
	//assert(isAvailableRegister(val1));
	//assert(isValidRegister(val1));
	if(isValidRegister(val1))
        pairRegisters[val1].second *= -1;
    else
        cout << "Register: " << val1 << " not available or valid " << endl;
}
void Program::less(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
    int register_index = convert(r1);
    int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	//int register_index = convert(r1);
	//assert(isAvailableMemory(memory1_index));
	//assert(isValidMemory(memory1_index));
	//assert(isAvailableMemory(memory2_index));
	//assert(isValidMemory(memory2_index));
	if(isValidMemory(memory1_index) && isValidMemory(memory1_index))
    {
        if( pairMemory[memory1_index].second < pairMemory[memory2_index].second)
            pairRegisters[register_index].second = 1;
        else
            pairRegisters[register_index].second = 0;
    }
	//you need to ask  if you are storing the value here in this function or just returning a boolean.
	//assert(isAvailableRegister(register_index));
}
void Program::great(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
	int register_index = convert(r1);
	int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	//int register_index = convert(r1);

	//assert(isAvailableMemory(memory1_index));
	//assert(isValidMemory(memory1_index));
	//assert(isAvailableMemory(memory2_index));
	//assert(isValidMemory(memory2_index));
	if(isValidMemory(memory1_index) && isValidMemory(memory2_index))
    {
        if( pairMemory[memory1_index].second > pairMemory[memory2_index].second)
            pairRegisters[register_index].second = 1;
        else
            pairRegisters[register_index].second = 0;
    }
	//you need to ask  if you are storing the value here in this function or just returning a boolean.
	//assert(isAvailableRegister(register_index));
}

void Program::equal(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
    int register_index = convert(r1);
	int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	//assert(isAvailableMemory(memory1_index));
	//assert(isValidMemory(memory2_index));
	if(isAvailableMemory(memory1_index) && isValidMemory(memory2_index))
    {
        if( pairMemory[memory1_index].second == pairMemory[memory2_index].second)
            pairRegisters[register_index].second = 1;
        else
            pairRegisters[register_index].second = 0;
    }

}

// Transfer Control
void Program::in(string register_address)
{
    int register_index = convert(register_address);
    cout << "IN (REG_INDX) " << register_index << endl;
    // check if a register is available &&  if register index is valid && register isn't taken
    if(isValidRegister(register_index))
    {
        int input;
        cout << "Enter your input: " << endl;
        cin >> input;
        cout << "INPUT " << input << endl;
        pairRegisters[register_index].second = input;
        cout << "TEST +++ " <<  pairRegisters[register_index].second  << endl;
        pairRegisters[register_index].first = false;
        used_registers++;
    }
    else
        cout << "No more register space, invalid register entry, or register is already taken " << endl;
}
void Program::out(string register_address)
{
    int register_index = convert(register_address);
    // Check to see if index is valid and if anything is in it
    if(isValidRegister(register_index))
    {
        cout <<  "value at register " << register_index << " is: ";
        cout << pairRegisters[register_index].second << endl;
    }
    else
        cout << "No such register " << endl;
}
void Program::goTo(string func_name)
{
    cout << "GOTO " << endl;
    // Number of addresses in an instruction depending on OPCODE
    int number_of_addresses;
    // Opcode length
    int opcode_length = 0;
    // Stores the instruction from 'functions' vector
    string line;
    // Stores the instruction
    string opcode, address1, address2, address3;
    // Iterates through size of vector
    for(int i = 0; i < functions[func_name].size();i++)
    {
        opcode = "";
        opcode_length = 0;
        // Stores line of instruction from vector at element i
        line =  functions[func_name][i];
        // Parse line --> get opcode
        for(int i = 0; i < line.length(); i++)
        {
            if(!isspace(line[i]))
            {
                opcode += line[i];
                opcode_length++;
            }
            else
                break;
        }
         // TODO: check to see if opcode is a function
                number_of_addresses = numberOfAddresses(opcode);
                cout << "NUM OF ADD " << number_of_addresses << endl;
                 switch(number_of_addresses)
                {
                    case 3:
                        //cout << "Line:(case) " << line << endl;
                        address1 = line.substr(opcode_length + 1, 3);
                        //cout << "Address 1: " << address1 << endl;
                        address2 = line.substr(opcode_length + 5, 3);
                        //cout << "Address 2: " << address2 << endl;
                        address3 = line.substr(opcode_length + 9, 3);
                        //cout << "Address 3: " << address3 << endl;
                        executeFunction(opcode, address1, address2, address3);
                        break;
                    case 2:
                        if(toLower(opcode) == "whif")
                        {
                            address1 = line.substr(opcode_length + 1, 3);
                            address2 = line.substr(opcode_length + 5);
                        }
                        else if(toLower(opcode) == "setr")
                        {
                            address1 = line.substr(opcode_length + 1, 3);
                            address2 = line.substr(opcode_length + 5);
                        }
                        else
                        {
                            address1 = line.substr(opcode_length + 1, 3);
                            address2 = line.substr(opcode_length + 5, 3);
                        }
                        executeFunction(opcode, address1, address2);

                        break;
                    case 1:
                        {
                           // cout << "CASE 1: " << opcode << endl;
                            address1 = line.substr(opcode_length + 1, 3);
                            executeFunction(opcode, address1);
                        }

                        break;
                    case 0:
                        executeFunction(opcode);
                        break;
                }

              /*  switch(number_of_addresses)
                {
                    case 3:
                        cout << "Line:(case) " << line << endl;
                        address1 = line.substr(opcode_length + 1, 3);
                        cout << "Address 1: " << address1 << endl;
                        address2 = line.substr(opcode_length + 5, 3);
                        cout << "Address 2: " << address2 << endl;
                        address3 = line.substr(opcode_length + 9, 3);
                        cout << "Address 3: " << address3 << endl;
                        executeFunction(opcode, address1, address2, address3);
                        break;
                    case 2:
                        address1 = line.substr(opcode_length + 1, 3);
                        address2 = line.substr(opcode_length + 5, 3);
                        executeFunction(opcode, address1, address2);
                        break;
                    case 1:
                        address1 = line.substr(opcode_length + 1, 3);
                        executeFunction(opcode, address1);
                        break;
                    case 0:
                        executeFunction(opcode);
                        break;
                }*/
    }
}
void Program::whif(string reg, string func_name)
{
    cout << "WHIF (whif)" << endl;
    cout << "REG (being passed in)" << reg << endl;
    int register_index = convert(reg);
    cout << "REG_INDEX (whif)" << register_index << endl;
    // If it's zero, it will proceed with the .txt file
    // If it's one, it will locate function and print
    if(pairRegisters[register_index].second == 1)
    {
         cout << "whif goTo" << endl;
         goTo(func_name);
    }
    else
        cout << "PROBLEM" << endl;
}
// Special Opcode
void Program::peek(string memory_address)
{
	int memory_index = convert(memory_address);
	// Checks if memory address is valid and that that memory address is filled
	if(memory_index < MEMORY_CAPACITY && pairMemory[memory_index].first == 0)
    {
        cout << pairMemory[memory_index].second << endl;
    }
    else
        cout << "Nothing to display " << endl;

}
void Program::sort_array(string m1, string num)
{
    // converts m1 to int
    int memory_index = convert(m1);
    int number = convert(num);
    // checks if it is valid
    if(memory_index< MEMORY_CAPACITY && number < MEMORY_CAPACITY)
    {
        std::set<int> sortedl;
        std::set<int>::iterator it = sortedl.begin();
        // Sorts numbers by putting them into a set
        for(int i = memory_index; i < number; i++)
            sortedl.insert(pairMemory[i].second);
        // Reassigns array with sorted values
        int index = memory_index;
        for(it; it != sortedl.end(); it++)
        {
            pairMemory[index].second = *it;
            index++;
        }
    }
}
void Program::clearallr()
{
    cout << "CLEARALL" << endl;
    for(unsigned int i = 0; i <REGISTER_CAPACITY; i++)
    {
        pairRegisters[i] = make_pair(true, 0);
    }
}
void Program::clearr(string r1)
{
    // convert r1 to int
	unsigned int register_index = convert(r1);
    // check if r1 is present
    if(register_index < REGISTER_CAPACITY)
    {   // clear item at
        pairRegisters[register_index].second = 0;
        pairRegisters[register_index].first = 1;
    }
}
void Program::clearm(string m1)
{
    // convert m1 to int
    unsigned int memory_index = convert(m1);
    // check if m1 is present
    assert(memory_index < MEMORY_CAPACITY);
    pairMemory[memory_index].second = 0;
    pairRegisters[memory_index].first = true;
}

void Program::halt()
{
    exit(0);
}
string Program::toLower(string str)
{
            string result;
    for(int i = 0; i < str.length(); i++)
    {
        result += std::tolower(str[i]);
    }
    return result;
}
bool Program::isValidMemory(unsigned int val)
{
    if(val < MEMORY_CAPACITY)
        return true;
    else
        return false;
}
bool Program::isValidRegister(unsigned int val)
{
    if(val < REGISTER_CAPACITY)
        return true;
    else
        return false;
}
bool Program::isAvailableMemory(unsigned int val)
{
    if (pairMemory[val].first == true)
        return true;
    else
        return false;
}
bool Program::isAvailableRegister(unsigned int val)
{
    if(pairRegisters[val].first == true)
        return true;
    else
        return false;
}
void Program::setReg(int pos, int val)
{
    pairRegisters[pos].second = val;
    pairRegisters[pos].first = false;
}

pair<bool, int> Program::retPairM(int pos)
{
    pair<bool, int> aPair;
    aPair = pairMemory[pos];
    return aPair;
}

pair<bool, int> Program::retPairR(int pos)
{
    pair<bool, int> aPair;
    aPair = pairRegisters[pos];
    return aPair;
}
void Program::internalDisplay()
{
    cout << "= = = = REG = = = = " << endl;
    for (int i = 0; i < 16; i++)
    {
        cout << "REG @ " << i << " :"<< pairRegisters[i].second << endl;
     }
         cout << "= = = = MEM = = = = " << endl;
    for (int i = 0; i < 32; i++)
    {
        cout << "MEM @ " << i << " :"<< pairMemory[i].second << endl;
     }
}
