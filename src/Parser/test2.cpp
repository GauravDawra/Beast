// #include "test2.h"
#include <iostream>
using namespace std;
// namespace X
// {
    // extern int xx;
    // static int xx = 908;
    int xx = 1067;
    int* foo()
    {
        cout << &xx<<'h' << endl;
        return &xx;
    }
// }