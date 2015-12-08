#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>
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
void Program::execute(){};

void Program::get(string r, string m)
{
  unsigned int reg = convert(r);
  unsigned int memo = convert(m);
  assert(isValidRegister(reg));
  assert(isValidMemory(memo));
  pairRegisters[reg].second = pairMemory[memo].second;
  pairRegisters[reg].first = pairMemory[memo].first;
}

void Program::getu(int pos, int val) // new name "setR"
{
    pairRegisters[pos].second = val;
    pairRegisters[pos].first = false;
}

/*
void Program::execute()
{

}


void Program::set(string m, string r);
{
 // string reg = convert(r);
 // string memo = convert(m);
  assert(isValidRegisters);
  assert(isValidMemory);
  pairRegisters[memo].second = register[reg];
}

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

void Program::addm(string r1, string m1, string m2)
{
  int reg1 = // convert string
  assert(reg1 >= 0 && reg1 < REGISTER_CAPACITY);
  int memo1 = // convert string
  assert(memo1 >= 0 && memo1 < MEMORY_CAPACITY);
  int memo2 = // convert string
  assert(memo2 >= 0 && memo2 < MEMORY_CAPACITY);

  registers[reg1] = memory[memo1] + memory[memo2];
}

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

void Program::move(string m2, string m1)
{

}
void Program::addr(string r3, string r1, string r2)
{

}

//ADDM R6, M1, M2
void Program::addm(string r1, string m1, string m2)
{
    //check that m1 and m2 are
}
void Program::subr(string r3, string r1, string r2)
{

}
void Program::subm(string r1, string m1, string m2)
{

}
*/
//arithmetic functions
void Program::multr(string r3, string r2, string r1)
{
	//convert r1 and r2
	int val1 = convert(r1);
	int val2 = convert(r2);
	int val3 = convert(r3);

	//makes sure that the register location is valid and available
	if(isValidRegister(val3) && isAvailableRegister(val3))
    {
        pairRegisters[val3].second = val1 * val2;
        pairRegisters[val3].first = false; //not available anymore
    }
    else
        cout << "Not available Register: " << val3 << endl;

}
void Program::multm(string r3, string m1, string m2)
{
	//convert m1 and m2 to ints
	int val1 = convert(m1);
	int val2 = convert(m2);
	int val3 = convert(r3);

	//assert(isValidMemory(val3));
	//assert(isAvailableRegister(val3));
	if(isValidMemory(val3) && isAvailableRegister(val3))
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
	if(isValidMemory(val3) && isAvailableRegister(val3))
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
	if(isValidRegister(val3) && isAvailableRegister(val3))
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
	if(isAvailableRegister(val1) && isValidRegister(val1))
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
	if(isAvailableRegister(val1) && isValidRegister(val1))
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
	if(isAvailableRegister(val1) && isValidRegister(val1))
        pairRegisters[val1].second *= -1;
    else
        cout << "Register: " << val1 << " not available or valid " << endl;
}
bool Program::less(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
	bool isLess;
    int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	//int register_index = convert(r1);
	//assert(isAvailableMemory(memory1_index));
	//assert(isValidMemory(memory1_index));
	//assert(isAvailableMemory(memory2_index));
	//assert(isValidMemory(memory2_index));
	if(isAvailableMemory(memory1_index) && isValidMemory(memory1_index) && isAvailableMemory(memory2_index) && isValidMemory(memory1_index))
    {
        if( pairMemory[memory1_index].second < pairMemory[memory2_index].second)
            isLess = true;
    }
	//you need to ask  if you are storing the value here in this function or just returning a boolean.
	//assert(isAvailableRegister(register_index));
	else
		isLess = false;
    return isLess;
}
bool Program::great(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
	bool isGreater;
	int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	//int register_index = convert(r1);

	//assert(isAvailableMemory(memory1_index));
	//assert(isValidMemory(memory1_index));
	//assert(isAvailableMemory(memory2_index));
	//assert(isValidMemory(memory2_index));
	if(isAvailableMemory(memory1_index) && isValidMemory(memory1_index) && isAvailableMemory(memory2_index) && isValidMemory(memory2_index))
    {
        if( pairMemory[memory1_index].second > pairMemory[memory2_index].second)
            isGreater = true;
    }
	//you need to ask  if you are storing the value here in this function or just returning a boolean.
	//assert(isAvailableRegister(register_index));

	else
		isGreater = false;
    return isGreater;
}

bool Program::equal(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
	bool isEqual;
	int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	//assert(isAvailableMemory(memory1_index));
	//assert(isValidMemory(memory2_index));
	if(isAvailableMemory(memory1_index) && isValidMemory(memory2_index))
    {
        if( pairMemory[memory1_index].second == pairMemory[memory2_index].second)
                isEqual = true;
    }
    else
        isEqual = false;
    return isEqual;
}
// Transfer Control
void Program::in(string register_address)
{
    // check if register is available
    if(used_registers < REGISTER_CAPACITY)
    {
        int register_index = convert(register_address);
        int input;
        cout << "Enter your input: " << endl;
        cin >> input;
        pairRegisters[register_index].second = input;
    }
    else
        cout << "No more register space" << endl;
}

void Program::out(string register_address)
{
    unsigned int register_index = convert(register_address);
    assert(register_index < REGISTER_CAPACITY);  // Checks user input
    cout <<  "value at register " << register_address << " is: ";
    cout << pairRegisters[register_index].second << endl;
}
void Program::goTo(string func_name)
{

}
void Program::whif(string func_name)
{

}
// Special Opcode
void Program::peek(string memory_address)
{
	unsigned int memory_index = convert(memory_address);
	assert(memory_index < MEMORY_CAPACITY);
	cout << pairMemory[memory_index].second << endl;
}
/*void Program::sort(string m1, string num)
{
    // converts m1 to int
    // checks if it is valid
    assert(memory_address < MEMORY_ADDRESS);
    set<int> sorted;
    set<int>::iterator it = sorted.begin();
    // Sorts numbers by putting them into a set
    for(int i = memory_address; i < num; i++)
        sorted.insert(memory[i]);
    // Reassigns array with sorted values
    for(int i = memory_address; i < num; i++)
    {
        memory[i] = *it;
        it++;
    }
} */
void Program::clearr(string r1)
{
    // convert r1 to int
	unsigned int register_index = convert(r1);
    // check if r1 is present
    assert(register_index < REGISTER_CAPACITY);
    // clear item at
    pairRegisters[register_index].second = 0;
    pairRegisters[register_index].first = true;
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

bool Program::isValidMemory(unsigned int val)
{
    if(val < used_memory)
        return true;
    else
        return false;
}
bool Program::isValidRegister(unsigned int val)
{
    if(val < used_registers)
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
