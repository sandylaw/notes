#include <iostream>
#include <string>

using namespace std;

int main()
{
    char myGrade = 'A';
    switch(myGrade){
        case 'A':
            cout << "You pass" << endl;
            break;
        case 'F':
            cout << "You fail" << endl;
            break;
        default:
            cout << "Invalid grade" << endl;
    }
    return 0;
}
