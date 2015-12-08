#include <fstream>
#include <cassert>
#include <set>
#include <string>
#include <cctype>
#include <cstring>
#include <cstdlib>
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
}

void Program::execute()
{
    int number_of_addresses;
    string opcode, address_one, address_two, address_three;
    fstream fin;
    fin.open("isa.txt");
    if(fin.fail())
        cout << "File is not valid " << endl;
    while(fin.good())
    {
        // Check if it's a function

        // Read in opcode
        fin >> opcode;
          number_of_addresses = numberOfAddresses(opcode);

}
}
void Program::executeFunction(string opcode)
{
    halt();
}

void Program::executeFunction(string opcode, string address1)
{
    if(opcode == "incr")
        incr(address1);
    else if(opcode == "decr")
        decr(address1);
    else if(opcode == "neg")
        neg(address1);
    else if(opcode == "in")
        in(address1);
    else if(opcode == "out")
        out(address1);
    else if(toLower(opcode) == "goto")
        goTo(address1);
    else if(opcode == "peek")
        peek(address1);
    else if(opcode == "clearr")
        clearr(address1);
    else if(opcode == "clearm")
        clearm(address1);
}

void Program::executeFunction(string opcode, string address1, string address2)
{
    if(toLower(opcode) == "get")
        get(address1, address2);
    else if(toLower(opcode) == "set")
        set(address1, address2);
    else if(toLower(opcode) == "swap")
        swap(address1, address2);
    else if(toLower(opcode) == "move")
        move(address1, address2);
    else if(toLower(opcode) == "whif")
        whif(address1, address2);
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
  if((isValidRegister(reg) && isAvailableRegister(reg)) && (isValidMemory(memo) && isAvailableMemory(memo))
    {
        pairRegisters[reg].second = pairMemory[memo].second;
        pairRegisters[reg].first = false;
    }
}
void Program::getu(int pos, int val) // new name "setR"
{
    pairRegisters[pos].second = val;
    pairRegisters[pos].first = false;
}

void Program::set(string m, string r)
{
 // string reg = convert(r);
 // string memo = convert(m);
  //assert(isValidRegister());
  //assert(isValidMemory());
//  pairRegisters[memo].second = register[reg];
}
/*
void Program::swap(string r1, string r2)
{
  //string reg1 = // convert string   		 // At this moment we are storing integers in memory
  assert(reg1 >= 0 && reg1 < REGISTER_CAPACITY);    // if we want to output characters we can make a function
  string reg2 = // convert string   		 // that uses the integers stored in memory and translates
  assert(reg2 >= 0 && reg2 < REGISTER_CAPACITY);    // the numbers into ascii characters

  int tem_reg;
  temp_reg = registers[reg1];
  registers[reg1] = registers[reg2];
  registers[reg2] = registers[temp_reg];
}
void Program::move(string m2, string m1)
{
  int memo2 = // convert string
  assert(memo2 >= 0 && memo2 < MEMORY_CAPACITY);
  int memo1 = // convert string
  assert(memo1 >= 0 && memo1 < MEMORY_CAPACITY);

  int temp;
  temp = memory[memo2];
  memory[memo2] = memory[memo1];
  memory[memo1] = temp;
}

void Program::addr(string r3, string r1, string r2)
{
  int reg1 = // convert string
  assert(reg1 >= 0 && reg1 < REGISTER_CAPACITY);
  int reg2 = // convert string
  assert(reg2 >= 0 && reg2 < REGISTER_CAPACITY);
  int reg3 = // convert string
  assert(reg3 >= 0 && reg3 < REGISTER_CAPACITY);

  register[reg3] = register[reg1] + register[reg2];
}
*/
void Program::addm(string r1, string m1, string m2)
{
  int reg1 = convert(r1);
  //assert(reg1 >= 0 && reg1 < REGISTER_CAPACITY);
  int memo1 = convert(m1);// convert string
//  assert(memo1 >= 0 && memo1 < MEMORY_CAPACITY);
  int memo2 = convert(m2);// convert string
 // assert(memo2 >= 0 && memo2 < MEMORY_CAPACITY);

  pairRegisters[reg1].second = pairMemory[memo1].second + pairMemory[memo2].second;
}
/*
void Program::subr(string r3, string r1, string r2)
{
  int reg1 = // convert string
  assert(reg1 >= 0 && reg1 < REGISTER_CAPACITY);
  int reg2 = // convert string
  assert(reg2 >= 0 && reg2 < REGISTER_CAPACITY);
  int reg3 = // convert string
  assert(reg3 >= 0 && reg3 < REGISTER_CAPACITY);

  register[reg3] = register[reg1] - register[reg2];
}

void Program::subm(string r1, string m1, string m2)
{
  int reg1 = // convert string
  assert(reg1 >= 0 && reg1 < REGISTER_CAPACITY);
  int memo1 = // convert string
  assert(memo1 >= 0 && memo1 < MEMORY_CAPACITY);
  int memo2 = // convert string
  assert(memo2 >= 0 && memo2 < MEMORY_CAPACITY);

  registers[reg1] = memory[memo1] - memory[memo2];
}
//arithmetic functions
void Program::multr(string r3, string r2, string r1)
{
	//convert r1 and r2
	int val1 = convert(r1);
	int val2 = convert(r2);
	int val3 = convert(r3);

	//makes sure that the register location is valid and available
	assert(isValidRegister(val3));
	assert(isAvailableRegister(val3));
	pairRegisters[val3].second = val1 * val2;
	pairRegisters[val3].first = false; //not available anymore
}
void Program::multm(string r3, string m1, string m2)
{
	//convert m1 and m2 to ints
	int val1 = convert(m1);
	int val2 = convert(m2);
	int val3 = convert(r3);

	assert(isValidMemory(val3));
	assert(isAvailableRegister(val3));
    pairRegisters[val3].second = m1 * m2;
    pairRegisters[val3].first = false; //not available anymore.
}
void Program::divr(string r1, string r2, string r3)
{
	//convert r1 and r2 to ints
	int val1 = convert(r1);
	int val2 = convert(r2);
	int val3 = convert(r3);

	assert(isValidRegister(val3));
	assert(isAvailableRegister(val3));
	pairRegisters[val3].second = val1 / val2;
	pairRegisters[val3].first = false; // not available anymore.

}
void Program::divm(string r1, string m1, string m2)
{
	//convert m1 and m2
	int val1 = convert(m1);
	int val2 = convert(m2);
	int val3 = convert(r1);

	//r1 = m1/m2;
	assert(isValidRegsiter(val3));
	assert(isAvailableRegister(val3));
	pairRegisters[val3].second = val1/val2;
	pairRegisters[val3].first = false; // not available anymore.
}

void Program::incr(string r1) //increment r1(index)
{
	//convert r1 to int;
	int val1 = convert(r1);
	assert(isAvailableRegister(val1));
	assert(isValidRegister(val1));
	pairRegisters[val1].second += 1;
    //you need to set it to no available anymore and make sure that you can still increment +1 whenever you want.
}

void Program::decr(string r1)
{
	//convert r1 to int;
	int val1 = convert(r1);
	assert(isAvailableRegister(val1));
	assert(isValidRegister(val1));
	pairRegisters[val1].second -= 1;
    //you need to set it to no available anymore and make sure that you can still increment +1 whenever you want.
}
*/
void Program::neg(string r1) //negates all values in register
{
	//convert r1 to int
	int val1 = convert (r1);
	//assert(isAvailable(val1));
//	assert(isValid(val1));
	pairRegisters[val1].second = pairRegisters[val1].second * -1 ;
}/*
bool Program::less(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
    int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	//int register_index = convert(r1);
	assert(isAvailableMemory(memory1_index));
	assert(isValidMemory(memory1_index));
	assert(isAvailableMemory(memory2_index));
	assert(isValidMemory(memory2_index));
	//you need to ask  if you are storing the value here in this function or just returning a boolean.
	//assert(isAvailableRegister(register_index));
	if( pairMemory[memory1_index].second < pairMemory[memory2_index].second)
		return true;
	else
		return false;
}
bool Program::great(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
	int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	//int register_index = convert(r1);

	assert(isAvailableMemory(memory1_index));
	assert(isValidMemory(memory1_index));
	assert(isAvailableMemory(memory2_index));
	assert(isValidMemory(memory2_index));
	//you need to ask  if you are storing the value here in this function or just returning a boolean.
	//assert(isAvailableRegister(register_index));

	if( pairMemory[memory1_index].second > pairMemory[memory2_index].second)
		return true;
	else
		return false;
}

bool Program::equal(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
	int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	assert(isAvailableMemory(memory1_index));
	assert(isValidMemory(memory2_index));
	if( memory[memory1_index].second == memory[memory2_index].second)
		return true;
	else
		return false;
}
*/
// Transfer Control
void Program::in(string register_address)
{
    int register_index = convert(register_address);
    // check if a register is available &&  if register index is valid && register isn't taken
    if(used_registers < REGISTER_CAPACITY && register_index < REGISTER_CAPACITY&&  pairRegisters[register_index].first == 1)
    {
        int input;
        cout << "Enter your input: " << endl;
        cin >> input;
        pairRegisters[register_index].second = input;
        used_registers++;
    }
    else
        cout << "No more register space, invalid register entry, or register is already taken " << endl;
}

void Program::out(string register_address)
{
    int register_index = convert(register_address);
    // Check to see if index is valid and if anything is in it
    if(register_index < REGISTER_CAPACITY && pairRegisters[register_index].first == 0)
    {
        cout <<  "value at register " << register_index << " is: ";
        cout << pairRegisters[register_index].second << endl;
    }
    else
        cout << "No such register " << endl;
}

void Program::goTo(string func_name)
{
    int number_of_addresses;
    int opcode_length = 0;
    string line;
    string opcode, address1, address2, address3;
    for(int i = 0; i < functions[func_name].size();i++)
    {
        line =  functions[func_name][i];
        // parse line --> get opcode
        for(int i = 0; i < line.length(); i++)
        {
            if(!isspace(line[i]))
            {
                opcode += line[i];
                opcode_length++;
            }

            else
                break; // consider how to do this w/o break
        }

        number_of_addresses = numberOfAddresses(opcode);
        switch(number_of_addresses)
        {
            case 3:
                address1 = line.substr(opcode_length + 1, 3);
                address2 = line.substr(opcode_length + 4, 3);
                address3 = line.substr(opcode_length + 8, 3);
               // executeFunction(opcode, address1, address2, address3);
                break;
            case 2:
                address1 = line.substr(opcode_length + 1, 3);
                address2 = line.substr(opcode_length + 4, 3);
               // executeFunction(opcode, address1, address2);
                break;
            case 1:
                address1 = line.substr(opcode_length + 1, 3);
                executeFunction(opcode, address1);
                break;
            case 0:
              //  executeFunction(opcode);
                break;
        }
    }

}
void Program::whif(string func_name, string reg)
{
    int register_index = convert(reg);
    // If it's zero, it will proceed with the .txt file
    // If it's one, it will locate function and print
    if(pairRegisters[register_index].second == 1)
         goTo(func_name);
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
void Program::clearr(string r1)
{
    // convert r1 to int
	int register_index = convert(r1);
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
    int memory_index = convert(m1);
    // check if m1 is present
    assert(memory_index < MEMORY_CAPACITY);
    pairMemory[memory_index].second = 0;
    // sets first value to is available
    pairMemory[memory_index].first = 1;
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
bool Program::isValidMemory(int val)
{
    if(val < used_memory)
        return true;
    else
        return false;
}
bool Program::isValidRegister(int val)
{
    if(val < used_registers)
        return true;
    else
        return false;
}
bool Program::isAvailableMemory(int val)
{
    if (pairMemory[val].first == true)
        return true;
    else
        return false;
}
bool Program::isAvailableRegister(int val)
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
