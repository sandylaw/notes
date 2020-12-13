#include <string>
#include <iostream>
int main(){
using namespace std;

string myString = "Hello";
string myOtherString = " World\n";

cout << myString + myOtherString;
cout << myString + " You\n";
myString.append(" Dog");
cout << myString + "\n";

}

