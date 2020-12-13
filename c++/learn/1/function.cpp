/******************************************************************************
* File:             function.cpp
*
* Author:          Sandylaw   
* Created:          12/13/20 
* Description:     function 
*****************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int addNumbers(int num1, int num2)
{
    return num1 + num2;
}

int main()
{
    int sum = addNumbers(4,5);
    cout << sum << endl;
    return 0;
}
