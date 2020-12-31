#include <iostream>
#include <string>
#include <set>
using namespace std;
#include "pailie2.h"

int main()
{
    Solution solution1;
    set<string> result;
    result=solution1.permutation("qew");
    for(auto i:result)
        cout<<i<<endl;
    return 0;
}
