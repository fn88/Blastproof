#include <math.h>
#include <iostream>
using namespace std;


int main()
{
    float x = 5;
    float y = -5;

    float c = atan2(y, x) * (180/3.14);
    if (c < 0) c += 360.f;

    cout << c;

    return 0;
}