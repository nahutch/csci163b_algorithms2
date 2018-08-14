#include <iostream>
#include <fstream>
#include "graph.h"
#include "wgraph.h"
#include "ds.h"

using namespace std;

int main(int argc, char *argv[])
{

    vector<string> names {"wire1.txt", "wire2.txt", "wire3.txt", "wire4.txt"};

    for (auto s: names)
    {
        ifstream is(s);
        if (is.fail())
        {
            cout << "Can't open file!" << endl;
            is.close();
            return 1;
        }

        wgraph D;
        is >> D;


        D.Kruskal().print_connections();

        cout << endl << endl;
        is.close();
    }

    return 0;
}
