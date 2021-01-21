#include <iostream>
#include <string>

using namespace std;

int main()
{
    int num = 10;
    cout << &num << endl;
    
    int *pnum = &num;
    cout << pnum << endl;
    cout << *pnum << endl;

    return 0;
}
