#include <iostream>
#include <string>

int main(){
    using namespace std;
    string foo = "I am foo";
    string bar = "I am bar";

    string& fooRef = foo;
    fooRef += ". Hi!";
    cout << fooRef + "\n";

    fooRef = bar;
    cout << fooRef + "\n";

    const string& barRef = bar;
    cout << barRef + "\n";
}
