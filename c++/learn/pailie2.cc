#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "pailie2.h"

int main()
{
    Solution solution1;
    vector<string> result;
    result=solution1.permutation("abc");
    for(auto i:result)
        cout<<i<<endl;
    return 0;
}
