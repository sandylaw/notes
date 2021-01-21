#include <iostream>
using namespace std;
int main()
{
    int inval = 1.01;
    int count(const string &, char);

    int a[2][3] = { {1, 2, 3}, {4 ,5 ,6} };

int m, *p=&a[0][0];

m = (*p) * (*(p+2)) * (*(p+4));
cout << m<<endl;
    return  0;
}
