#include <iostream>
#include <fstream>

#include <set>

#include "network.h"
#include "wedge.h"
#include "digraph.h"
#include "dary_heap.h"

using namespace std;

int main()
{
    vector<string> names {"test81.txt", "test82.txt", "test83.txt"};

    for (auto s: names)
    {
        ifstream is(s);
        if (is.fail())
        {
            cout << "Can't open file!" << endl;
            is.close();
            return 1;
        }

        network N;


        is >> N;

        cout<< N << endl;

        N.rankable();

        cout << endl << endl;
        is.close();
    }


}

