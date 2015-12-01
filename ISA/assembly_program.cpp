#include <iostream>
#include <cassert>
#include "assembly_program.h"
using namespace std;
Program::Program()
{

}
/*void Program::convert(string s)
{
  string val = s.substr(1);
  int new_val = atoi(val.c_str());
  //return new_val;
}
void Program::execute()
{

}
// Data movement >>> add Program before every function
void Program::get(string r, string m)
{
  string reg; // = // convert string
  string memo; //= // convert string
  assert(reg >= 0 && reg < REGISTER_CAPACITY);
  assert(memo >= 0 && memo < MEMORY_CAPACITY);
  registers[reg] = memo[m];
}
void Program::set(string m, string r);
{
 // string reg = // convert string
 // string memo = // convert string
  assert(reg >= 0 && reg < REGISTER_CAPACITY);
  assert(memo >= 0 && memo < MEMORY_CAPACITY);
  memory[memo] = register[reg];
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
void Program::addm(string r1, string m1, string m2)
{

}
void Program::subr(string r3, string r1, string r2)
{

}
void Program::subm(string r1, string m1, string m2)
{

}

//arithmetic functions
void Program::multr(string r3, string r2, string r1)
{
	//convert r1 and r2
	//r3 = r1* r2;
}
void Program::multm(string r3, string m1, string m2)
{
	//convert m1 and m2 to ints
//r3 = m1 * m2;
}
void Program::divr(string r1, string r2, string r3)
{
	//convert r1 and r2 to ints
	// r3 = r1/r2;
}
void Program::divm(string r1, string m1, string m2)
{
	//convert m1 and m2
	//r1 = m1/m2;
}

void Program::incr(string r1) //increment r1(index)
{
	//convert r1 to int;
	//registers[r1]+=1;
}

void Program::decr(string r1)
{
	//convert r1 to int;
	//register[r1] -=1;
}
void Program::neg(string r1) //negates all values in register
{
	//convert r1 to int
	// r1 *= -1;
}
bool Program::less(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
//	int memory1_index = convert( m1);
	int memory2_index = convert(m2);
	if( memory[memory1_index] < memory[memory2_index])
		return true;
	else
		return false;
}
bool Program::great(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
	//int memory1_index = convert( m1);
	//int memory2_index = convert(m2);
	if( memory[memory1_index] > memory[memory2_index])
		return true;
	else
		return false;
}

bool Program::equal(string r1, string m1, string m2)
{
	//convert m1, and m2 to ints
	//int memory1_index = convert( m1);
	//int memory2_index = convert(m2);
	if( memory[memory1_index] == memory[memory2_index])
		return true;
	else
		return false;
}
// Transfer Control
void Program::in(string register_address)
{
    // check if register is available
    if(used_register < REGISTER_CAPACITY)
    {
        int register_index = convert(register_address);
        int input;
        cout << "Enter your input: " << endl;
        cin >> input;
        registers[register_address] = input;
    }
    else
        cout << "No more register space" << endl;
}

void out(string register_address)
{
    assert(register_address < REGISTER_CAPACITY);  // Checks user input
    int register_index = convert(register_address);
    cout <<  "value at register " << register_address << " is: ";
    cout << registers[register_index];
}
void Program::goto(string func_name)
{

}
void Program::whif(string func_name)
{

}
// Special Opcode
void Program::peek(string memory_address)
{
	int memory_index = convert(memory_address);
	assert(memory_address < MEMORY_CAPACITY);
	cout << memory[memory_index] << endl;
}
void Program::sort(string m1, string num)
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
}
void Program::clearr(string r1)
{
    // convert r1 to int
	int register_index = convert(r1);
    // check if r1 is present
    assert(register_index < REGISTER_CAPACITY);
    // clear item at
    registers[register_index] = 0;
}
void Program::clearm(string m1)
{
    // convert m1 to int
    int memory_index = convert(m1);
    // check if m1 is present
    assert(memory_index < MEMORY_CAPACITY);
    memory[memory_index] = 0;
}
void Program::halt()
{
    exit(0);
}
*/
