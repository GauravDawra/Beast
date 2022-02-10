#include <iostream>
using namespace std;

extern int x;
/*
build A.o: obj A.cpp

build B.o: obj B.cpp

build main: cc A.o B.o
*/
int main() {
    cout << x << endl;
    
    return 0;
}