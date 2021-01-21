#include <iostream>
#include <string>
#include <set>
using namespace std;
#include "pailie.h"
int main()
{
    Solution solution1;
    set<string> result;
    result=solution1.permutation("pewa");
    for(auto i:result)
    {
        cout<<i<<endl;
    }
    return 0;
}
