#include <math.h>
#include <iostream>
#include <vector>
using namespace std;


int main()
{
    vector<int> a = {1, 3, 5, 7, 9};
    vector<int> b = {2, 4, 6, 8, 10};

    for (auto it1 = a.begin(); it1 < a.end(); it1++)
    {
        for (auto it2 = b.begin(); it2 < b.end(); it2++)
        {
            if ( (*it1)*(*it2) == 12 ) return 0;
            else cout << (*it1)*(*it2) << endl;
        }
        cout << endl;
    }

    return 0;
}