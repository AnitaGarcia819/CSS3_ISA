#include "assembly_program.h"
#include <vector>
#include <unordered_map>
using namespace std;
int main()
{
    Program program;

    program.cacheFunctions();
    program.execute();

    /*
    program.setr("R01", "5");
    program.setr("R02", "4");
    vector<string> vec;
    vec.push_back("MULTR R03 R01 R02");
    vec.push_back("ADDR R02 R01 R03");

   // cout << vec[0] << endl;
    //cout << vec[1] << endl;

    pair<string, vector<string> > p;
    p.first = "LOOP";
    p.second = vec;

    program.functions.insert(p);
    program.goTo("LOOP");
   // cout << "MULTR " << program.pairRegisters[1].second << endl;


    for(int i = 0; i < program.functions["LOOP"].size();i++)
        cout << program.functions["LOOP"][i] << endl;
    for(int i = 0; i < program.functions["LOOK"].size();i++)
        cout << program.functions["LOOK"][i] << endl;
    */
    return 0;
}

