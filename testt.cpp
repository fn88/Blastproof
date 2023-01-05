#include <math.h>
#include <iostream>
#include <vector>
using namespace std;


void doubling(int x)
{
    x = x*2;
}

int main()
{
    int n = 4;

    doubling(n);
    cout << n << endl;

    return 0;
}