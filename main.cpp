#include <iostream>
#include "BigRational.h"

using namespace std;

int main()
{
    BigRational h;
    cin >> h;
    h.reduce();
    cout << h;
    return 0;
}
